// Fill out your copyright notice in the Description page of Project Settings.


#include "OAuthTcpListener.h"
#include "TimerManager.h"
#include "Engine/World.h"
#include "Sockets.h"
#include "SocketSubsystem.h"
#include "Interfaces/IPv4/IPv4Address.h"
#include "Account/LKAccountManager.h"

bool UOAuthTcpListener::Start(uint16 Port, UWorld* InWorldContext)
{
	Stop();

	FIPv4Address Addr;
	FIPv4Address::Parse(TEXT("127.0.0.1"), Addr);
	TSharedRef<FInternetAddr> Endpoint = ISocketSubsystem::Get(PLATFORM_SOCKETSUBSYSTEM)->CreateInternetAddr();
	Endpoint->SetIp(Addr.Value);
	Endpoint->SetPort(Port);

	ListenerSocket = ISocketSubsystem::Get(PLATFORM_SOCKETSUBSYSTEM)->CreateSocket(NAME_Stream, TEXT("OAuthListener"), false);
	if (!ListenerSocket->Bind(*Endpoint) || !ListenerSocket->Listen(8))
	{
		UE_LOG(LogTemp, Error, TEXT("[OAuth] Failed to bind or listen on port %d"), Port);
		Stop();
		return false;
	}

	if (InWorldContext)
	{
		WorldContext = InWorldContext;
		WorldContext->GetTimerManager().SetTimer(AcceptTimerHandle, this, &UOAuthTcpListener::AcceptConnection, 0.5f, true);
	}

	UE_LOG(LogTemp, Log, TEXT("[OAuth] TCP Listener started on port %d"), Port);
	return true;
}

void UOAuthTcpListener::Stop()
{
	if (WorldContext)
	{
		WorldContext->GetTimerManager().ClearTimer(AcceptTimerHandle);
	}

	if (ListenerSocket)
	{
		ListenerSocket->Close();
		ISocketSubsystem::Get(PLATFORM_SOCKETSUBSYSTEM)->DestroySocket(ListenerSocket);
		ListenerSocket = nullptr;
	}
}

void UOAuthTcpListener::AcceptConnection()
{
	if (!ListenerSocket) return;

	bool Pending;
	if (ListenerSocket->HasPendingConnection(Pending) && Pending)
	{
		FSocket* ClientSocket = ListenerSocket->Accept(TEXT("OAuthClient"));
		if (ClientSocket)
		{
			// 클라이언트 연결 수신은 별도 쓰레드에서 처리
			Async(EAsyncExecution::ThreadPool, [this, ClientSocket]()
			{
				this->HandleClient(ClientSocket);
			});
		}
	}
}

void UOAuthTcpListener::HandleClient(FSocket* ClientSocket)
{
	if (!ClientSocket)
	{
		return;
	}

	// 데이터를 기다릴 때 최대 3초까지만 대기
	if (!ClientSocket->Wait(ESocketWaitConditions::WaitForRead, FTimespan::FromSeconds(3)))
	{
		UE_LOG(LogTemp, Warning, TEXT("[OAuth] Client connection timed out waiting for data."));
		ClientSocket->Close();
		ISocketSubsystem::Get(PLATFORM_SOCKETSUBSYSTEM)->DestroySocket(ClientSocket);
		return;
	}

	TArray<uint8> Buffer;
	Buffer.SetNum(4096);
	int32 BytesRead = 0;

	if (ClientSocket->Recv(Buffer.GetData(), Buffer.Num(), BytesRead))
	{
		FString RequestStr = FString(UTF8_TO_TCHAR((const char*)Buffer.GetData()));
		UE_LOG(LogTemp, Log, TEXT("[OAuth] Received Request:\n%s"), *RequestStr);

		if (RequestStr.Contains(TEXT("GET /oauth2callback")))
		{
			const FString AuthCode = ExtractAuthCodeFromRequest(RequestStr);
			if (!AuthCode.IsEmpty())
			{
				const FString HtmlContent = TEXT("<html><body><h2>로그인 완료! 게임으로 돌아가세요.</h2></body></html>");

				// UTF-8 변환
				FTCHARToUTF8 UTF8(*HtmlContent);
				int32 ContentLength = UTF8.Length();

				// 전체 HTTP 응답 구성 (Content-Length 기준은 UTF-8 바이트 수)
				FString HttpResponse = FString::Printf(TEXT(
					"HTTP/1.1 200 OK\r\n"
					"Content-Type: text/html; charset=UTF-8\r\n"
					"Content-Length: %d\r\n\r\n%s"),
					ContentLength, *HtmlContent);

				FTCHARToUTF8 FinalUTF8(*HttpResponse);
				ClientSocket->Send((uint8*)FinalUTF8.Get(), FinalUTF8.Length(), BytesRead);

				FString AuthCodeCopy = AuthCode;

				AsyncTask(ENamedThreads::GameThread, [this, AuthCodeCopy]()
					{
						UE_LOG(LogTemp, Log, TEXT("[OAuth] Entered AsyncTask"));

						if (ULKAccountManager* AM = ULKAccountManager::GetInstance(WorldContext))
						{
							UE_LOG(LogTemp, Log, TEXT("[OAuth] Calling RequestGoogleLoginWithAuthCode"));
							AM->RequestGoogleLoginWithAuthCode(AuthCodeCopy);
						}
						else
						{
							UE_LOG(LogTemp, Warning, TEXT("[OAuth] AccountManager is null"));
						}
					});
			}
			else
			{
				UE_LOG(LogTemp, Warning, TEXT("[OAuth] Failed to extract auth code."));
			}
		}
	}

	// 연결 종료 및 정리
	ClientSocket->Close();
	ISocketSubsystem::Get(PLATFORM_SOCKETSUBSYSTEM)->DestroySocket(ClientSocket);
}

FString UOAuthTcpListener::ExtractAuthCodeFromRequest(const FString& Request)
{
	const FString Prefix = TEXT("GET /oauth2callback?");
	int32 Start = Request.Find(Prefix);
	if (Start == INDEX_NONE) return TEXT("");

	int32 End = Request.Find(TEXT(" HTTP/"), ESearchCase::IgnoreCase, ESearchDir::FromStart, Start);
	if (End == INDEX_NONE) return TEXT("");

	const FString Query = Request.Mid(Start + Prefix.Len(), End - (Start + Prefix.Len()));

	FString AuthCode;
	FParse::Value(*Query, TEXT("code="), AuthCode);
	return AuthCode;
}
