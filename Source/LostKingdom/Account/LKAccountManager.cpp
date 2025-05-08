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

void ULKAccountManager::Initialize(FSubsystemCollectionBase& Collection)
{
	Super::Initialize(Collection);

	// Initialize the server URL
	ServerURL = TEXT("https://localhost:7192");
}

ULKAccountManager* ULKAccountManager::Get(UWorld* WorldContext)
{
	if (WorldContext)
	{
		if (UGameInstance* GameInstance = WorldContext->GetGameInstance())
		{
			return GameInstance->GetSubsystem<ULKAccountManager>();
		}
	}
	return nullptr;
}

void ULKAccountManager::RequestLogin(ELKProviderType LoginProviderType, TFunction<void(bool, const FString&)> Callback)
{
	if (IsLoggedIn())
	{
		Callback(false, TEXT("이미 로그인 되어 있습니다"));
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

	FString Token = GetToken(LoginProviderType);
	Writer->WriteValue(TEXT("token"), Token);
	Writer->WriteObjectEnd();
	Writer->Close();
	Request->SetContentAsString(JsonString);

	Request->OnProcessRequestComplete().BindLambda([this, Callback](FHttpRequestPtr Request, FHttpResponsePtr Response, bool bSuccess)
		{
			if (!bSuccess || !Response.IsValid())
			{
				Callback(false, TEXT("서버 연결에 실패했습니다"));
				return;
			}

			// JSON 응답 파싱
			TSharedPtr<FJsonObject> JsonObject;
			TSharedRef<TJsonReader<>> Reader = TJsonReaderFactory<>::Create(Response->GetContentAsString());
			if (!FJsonSerializer::Deserialize(Reader, JsonObject))
			{
				Callback(false, TEXT("서버 응답을 처리할 수 없습니다"));
				return;
			}

			bool bLoginSuccess = JsonObject->GetBoolField(TEXT("success"));
			if (!bLoginSuccess)
			{
				FString ErrorMessage = JsonObject->GetStringField(TEXT("message"));
				Callback(false, ErrorMessage);
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
			Callback(true, TEXT("로그인 성공"));
		});

	// 요청 전송
	Request->ProcessRequest();
}

void ULKAccountManager::RequestLogout(TFunction<void(bool, const FString&)> Callback)
{
	if (IsLoggedIn() == false)
	{
		Callback(false, TEXT("현재 로그인 상태가 아닙니다."));
		return;
	}

	if (LoginSession.IsValid() == false)
	{
		Callback(false, TEXT("로그인 세션이 유효하지 않습니다."));
		return;
	}

	TSharedRef<IHttpRequest, ESPMode::ThreadSafe> Request = FHttpModule::Get().CreateRequest();
	Request->SetURL(FString::Printf(TEXT("%s/api/auth/logout"), *ServerURL));
	Request->SetVerb(TEXT("POST"));
	Request->SetHeader(TEXT("Authorization"), FString::Printf(TEXT("Bearer %s"), *LoginSession.AuthToken));

	Request->OnProcessRequestComplete().BindLambda([this, Callback](FHttpRequestPtr Request, FHttpResponsePtr Response, bool bSuccess)
		{
			if (!bSuccess || !Response.IsValid())
			{
				Callback(false, TEXT("서버 연결에 실패했습니다"));
				return;
			}

			if (Response->GetResponseCode() == 200)
			{
				ClearLoginSession();
				Callback(true, TEXT("로그아웃 완료"));
			}
			else
			{
				Callback(false, TEXT("로그아웃 실패"));
			}
		});

	Request->ProcessRequest();
}

void ULKAccountManager::TryAutoLogin(TFunction<void(bool)> Callback)
{
	if (LoadLoginSession() == false)
	{
		Callback(false);
		return;
	}

	TSharedRef<IHttpRequest, ESPMode::ThreadSafe> Request = FHttpModule::Get().CreateRequest();
	Request->SetURL(FString::Printf(TEXT("%s/api/auth/verify"), *ServerURL));
	Request->SetVerb(TEXT("GET"));
	Request->SetHeader(TEXT("Authorization"), FString::Printf(TEXT("Bearer %s"), *LoginSession.AuthToken));

	Request->OnProcessRequestComplete().BindLambda([this, Callback](FHttpRequestPtr Request, FHttpResponsePtr Response, bool bSuccess)
	{
		if (bSuccess && Response.IsValid() && Response->GetResponseCode() == 200)
		{
			Callback(true);
		}
		else
		{
			ClearLoginSession();
			Callback(false);
		}
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
