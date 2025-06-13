// Fill out your copyright notice in the Description page of Project Settings.


#include "Account/LKAccountManager.h"
#include "Account/LKLoginSaveData.h"
#include "Kismet/GameplayStatics.h"
#include "HttpModule.h"
#include "Interfaces/IHttpResponse.h"
#include "Http.h"
#include "Dom/JsonObject.h"
#include "Serialization/JsonWriter.h"
#include "Serialization/JsonSerializer.h"
#include "OAuthTcpListener.h"

void ULKAccountManager::Initialize(FSubsystemCollectionBase& Collection)
{
	Super::Initialize(Collection);

	GConfig->GetString(
		TEXT("/Script/LostKingdom.LKAccountManager"),
		TEXT("ServerURL"),
		ServerURL,
		GGameIni
	);
}

void ULKAccountManager::RequestLogin(ELKProviderType LoginProviderType, const FString& InToken /*= TEXT("")*/)
{
	if (IsLoggedIn())
	{
		OnLoginRequestAck.Broadcast(false, TEXT("이미 로그인 되어 있습니다"));
		return;
	}

	// HTTP 요청 생성
	TSharedRef<IHttpRequest, ESPMode::ThreadSafe> Request = FHttpModule::Get().CreateRequest();
	Request->SetURL(FString::Printf(TEXT("%s/api/auth/login"), *ServerURL));
	Request->SetVerb(TEXT("POST"));
	Request->SetHeader(TEXT("Content-Type"), TEXT("application/json"));

	// 요청 본문 생성
	FString JsonString;
	TSharedRef<TJsonWriter<>> Writer = TJsonWriterFactory<>::Create(&JsonString);
	Writer->WriteObjectStart();
	Writer->WriteValue(TEXT("providerType"), static_cast<int32>(LoginProviderType));

	FString Token = InToken;
	if (Token.IsEmpty())
	{
		Token = GetToken(LoginProviderType);
	}

	Writer->WriteValue(TEXT("token"), Token);
	Writer->WriteObjectEnd();
	Writer->Close();
	Request->SetContentAsString(JsonString);

	Request->OnProcessRequestComplete().BindLambda([this](FHttpRequestPtr Request, FHttpResponsePtr Response, bool bSuccess)
		{
			if (!bSuccess || !Response.IsValid())
			{
				OnLoginRequestAck.Broadcast(false, TEXT("서버 연결에 실패했습니다"));
				return;
			}

			// JSON 응답 파싱
			TSharedPtr<FJsonObject> JsonObject;
			TSharedRef<TJsonReader<>> Reader = TJsonReaderFactory<>::Create(Response->GetContentAsString());
			if (!FJsonSerializer::Deserialize(Reader, JsonObject))
			{
				OnLoginRequestAck.Broadcast(false, TEXT("서버 응답을 파싱할 수 없습니다"));
				return;
			}

			bool bLoginSuccess = JsonObject->GetBoolField(TEXT("success"));
			if (!bLoginSuccess)
			{
				FString ErrorMessage = JsonObject->GetStringField(TEXT("message"));
				OnLoginRequestAck.Broadcast(false, ErrorMessage);
				return;
			}

			// 로그인 성공 시 데이터 처리
			TSharedPtr<FJsonObject> Data = JsonObject->GetObjectField(TEXT("data"));
			FString Token = Data->GetStringField(TEXT("token"));
			int32 AccountKey = Data->GetIntegerField(TEXT("accountKey"));
			FString UserKeyStr = Data->GetStringField(TEXT("userKey"));
			FGuid UserKey;
			FGuid::Parse(UserKeyStr, UserKey);

			HandleLoginSuccess(Token, AccountKey, UserKey);
			OnLoginRequestAck.Broadcast(true, TEXT("로그인 성공"));
		});

	// 요청 전송
	Request->ProcessRequest();
}

void ULKAccountManager::RequestLogout()
{
	if (IsLoggedIn() == false)
	{
		OnLoginRequestAck.Broadcast(false, TEXT("현재 로그인 상태가 아닙니다."));
		return;
	}

	if (LoginSession.IsValid() == false)
	{
		OnLoginRequestAck.Broadcast(false, TEXT("로그인 세션이 유효하지 않습니다."));
		return;
	}

	TSharedRef<IHttpRequest, ESPMode::ThreadSafe> Request = FHttpModule::Get().CreateRequest();
	Request->SetURL(FString::Printf(TEXT("%s/api/auth/logout"), *ServerURL));
	Request->SetVerb(TEXT("POST"));
	Request->SetHeader(TEXT("Authorization"), FString::Printf(TEXT("Bearer %s"), *LoginSession.AuthToken));

	Request->OnProcessRequestComplete().BindLambda([this](FHttpRequestPtr Request, FHttpResponsePtr Response, bool bSuccess)
		{
			if (!bSuccess || !Response.IsValid())
			{
				OnLoginRequestAck.Broadcast(true, TEXT("서버 연결에 실패했습니다"));
				return;
			}

			if (Response->GetResponseCode() == 200)
			{
				ClearLoginSession();
				OnLoginRequestAck.Broadcast(false, TEXT("로그아웃 성공"));
			}
			else
			{
				OnLoginRequestAck.Broadcast(true, TEXT("로그아웃 실패"));
			}
		});

	Request->ProcessRequest();
}

void ULKAccountManager::TryAutoLogin()
{
	if (LoadLoginSession() == false)
	{
		OnLoginRequestAck.Broadcast(false, TEXT(""));
		return;
	}

	TSharedRef<IHttpRequest, ESPMode::ThreadSafe> Request = FHttpModule::Get().CreateRequest();
	Request->SetURL(FString::Printf(TEXT("%s/api/auth/verify"), *ServerURL));
	Request->SetVerb(TEXT("GET"));
	Request->SetHeader(TEXT("Authorization"), FString::Printf(TEXT("Bearer %s"), *LoginSession.AuthToken));

	Request->OnProcessRequestComplete().BindLambda([this](FHttpRequestPtr Request, FHttpResponsePtr Response, bool bSuccess)
	{
		if (bSuccess && Response.IsValid() && Response->GetResponseCode() == 200)
		{
			OnLoginRequestAck.Broadcast(true, TEXT("자동 로그인 성공"));
		}
		else
		{
			ClearLoginSession();
			OnLoginRequestAck.Broadcast(false, TEXT("자동 로그인 실패"));
		}
	});

	Request->ProcessRequest();
}

void ULKAccountManager::RequestGoogleLoginWithAuthCode(const FString& AuthCode)
{
	TSharedRef<IHttpRequest, ESPMode::ThreadSafe> Request = FHttpModule::Get().CreateRequest();
	Request->SetURL(ServerURL + "/api/auth/google-login");
	Request->SetVerb(TEXT("POST"));
	Request->SetHeader(TEXT("Content-Type"), TEXT("application/json"));

	FString JsonString;
	TSharedRef<TJsonWriter<>> Writer = TJsonWriterFactory<>::Create(&JsonString);
	Writer->WriteObjectStart();
	Writer->WriteValue(TEXT("code"), AuthCode);
	Writer->WriteObjectEnd();
	Writer->Close();

	Request->SetContentAsString(JsonString);

	Request->OnProcessRequestComplete().BindLambda([this](FHttpRequestPtr Request, FHttpResponsePtr Response, bool bSuccess)
		{
			if (!bSuccess || !Response.IsValid())
			{
				OnLoginRequestAck.Broadcast(false, TEXT("서버 연결 실패"));
				return;
			}

			TSharedPtr<FJsonObject> JsonObject;
			TSharedRef<TJsonReader<>> Reader = TJsonReaderFactory<>::Create(Response->GetContentAsString());
			if (!FJsonSerializer::Deserialize(Reader, JsonObject))
			{
				OnLoginRequestAck.Broadcast(false, TEXT("응답 파싱 실패"));
				return;
			}

			if (!JsonObject->GetBoolField("success"))
			{
				OnLoginRequestAck.Broadcast(false, JsonObject->GetStringField("message"));
				return;
			}

			const TSharedPtr<FJsonObject> Data = JsonObject->GetObjectField("data");
			const FString Token = Data->GetStringField("token");
			const int32 AccountKey = Data->GetIntegerField("accountKey");
			const FString UserKeyStr = Data->GetStringField("userKey");

			FGuid UserKey;
			FGuid::Parse(UserKeyStr, UserKey);

			const double EndTime = FPlatformTime::Seconds();
			HandleLoginSuccess(Token, AccountKey, UserKey);
			OnLoginRequestAck.Broadcast(true, TEXT("로그인 성공"));
		});

	Request->ProcessRequest();
}

void ULKAccountManager::SaveLoginSession()
{
	ULKLoginSaveData* SaveData = NewObject<ULKLoginSaveData>();
	SaveData->SavedSession = LoginSession;
	UGameplayStatics::SaveGameToSlot(SaveData, TEXT("LoginData"), 0);
}

bool ULKAccountManager::LoadLoginSession()
{
	if (UGameplayStatics::DoesSaveGameExist(TEXT("LoginData"), 0))
	{
		ULKLoginSaveData* Loaded = Cast<ULKLoginSaveData>(UGameplayStatics::LoadGameFromSlot(TEXT("LoginData"), 0));
		if (Loaded)
		{
			LoginSession = Loaded->SavedSession;
			return LoginSession.IsValid();
		}
	}
	return false;
}

void ULKAccountManager::ClearLoginSession()
{
	LoginSession.Clear();
	UGameplayStatics::DeleteGameInSlot(TEXT("LoginData"), 0);
}

void ULKAccountManager::HandleLoginSuccess(const FString& Token, int32 AccountKey, const FGuid& UserKey)
{
	LoginSession.AuthToken = Token;
	LoginSession.AccountKey = AccountKey;
	LoginSession.UserKey = UserKey;

	SaveLoginSession();
}

FString ULKAccountManager::GetToken(ELKProviderType LoginProviderType)
{
	if (LoginProviderType == ELKProviderType::Guest)
	{
		return FGuid::NewGuid().ToString();
	}

	return TEXT("");
}

void ULKAccountManager::StartOAuthListener()
{
	if (OAuthListener == nullptr)
	{
		OAuthListener = NewObject<UOAuthTcpListener>();
		if (OAuthListener->Start(5005, GetWorld()))
		{
			UE_LOG(LogTemp, Log, TEXT("[OAuth] Listener started"));
		}
		else
		{
			UE_LOG(LogTemp, Error, TEXT("[OAuth] Failed to start listener"));
		}
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("[OAuth] Listener already started"));
	}
}

void ULKAccountManager::StopOAuthListener()
{
	if (OAuthListener)
	{
		OAuthListener->Stop();
		OAuthListener = nullptr;
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("[OAuth] Listener not started"));
	}
}
