// Fill out your copyright notice in the Description page of Project Settings.


#include "Account/LKAccountManager.h"
#include "HttpModule.h"
#include "Interfaces/IHttpResponse.h"
#include "Http.h"
#include "Dom/JsonObject.h"
#include "Serialization/JsonWriter.h"
#include "Serialization/JsonSerializer.h"
#include "Tool/LKLog.h"

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

void ULKAccountManager::RequestLogin(const FString& ID, const FString& PW, TFunction<void(bool, const FString&)> Callback)
{
	TSharedRef<IHttpRequest> Request = FHttpModule::Get().CreateRequest();

	Request->SetURL(ServerURL + TEXT("/api/auth/login"));
	Request->SetVerb(TEXT("POST"));
	Request->SetHeader(TEXT("Content-Type"), TEXT("application/json"));

	// CREATE JSON
	FString JsonString;
	TSharedRef<TJsonWriter<>> Writer = TJsonWriterFactory<>::Create(&JsonString);
	Writer->WriteObjectStart();
	Writer->WriteValue(TEXT("username"), ID);
	Writer->WriteValue(TEXT("password"), PW);
	Writer->WriteObjectEnd();
	Writer->Close();

	Request->SetContentAsString(JsonString);

	// 응답 처리
	Request->OnProcessRequestComplete().BindLambda(
		[Callback](FHttpRequestPtr Req, FHttpResponsePtr Resp, bool bSuccess)
		{
			if (bSuccess == false || Resp.IsValid() == false)
			{
				Callback(false, TEXT("서버 응답 실패"));
				return;
			}

			TSharedPtr<FJsonObject> JsonObject;
			TSharedRef<TJsonReader<>> Reader = TJsonReaderFactory<>::Create(Resp->GetContentAsString());

			if (FJsonSerializer::Deserialize(Reader, JsonObject) && JsonObject.IsValid())
			{
				bool bLoginSuccess = JsonObject->GetBoolField("success");
				FString Message = JsonObject->GetStringField("message");
				Callback(bLoginSuccess, Message);
			}
			else
			{
				Callback(false, TEXT("응답 파싱 실패"));
			}
		});

	Request->ProcessRequest();
}

void ULKAccountManager::RequestRegister(const FString& ID, const FString& PW, TFunction<void(bool, const FString&)> Callback)
{
	TSharedRef<IHttpRequest> Request = FHttpModule::Get().CreateRequest();

	Request->SetURL(ServerURL + TEXT("/api/auth/register"));
	Request->SetVerb(TEXT("POST"));
	Request->SetHeader("Content-Type", TEXT("application/json"));

	FString JsonString;
	TSharedRef<TJsonWriter<>> Writer = TJsonWriterFactory<>::Create(&JsonString);
	Writer->WriteObjectStart();
	Writer->WriteValue("username", ID);
	Writer->WriteValue("password", PW);
	Writer->WriteObjectEnd();
	Writer->Close();

	Request->SetContentAsString(JsonString);

	Request->OnProcessRequestComplete().BindLambda(
		[Callback](FHttpRequestPtr Req, FHttpResponsePtr Resp, bool bSuccess)
		{
			if (bSuccess == false || Resp.IsValid() == false)
			{
				Callback(false, TEXT("서버 응답 실패"));
				return;
			}

			TSharedPtr<FJsonObject> JsonObject;
			TSharedRef<TJsonReader<>> Reader = TJsonReaderFactory<>::Create(Resp->GetContentAsString());

			if (FJsonSerializer::Deserialize(Reader, JsonObject) && JsonObject.IsValid())
			{
				bool bRegisterSuccess = JsonObject->GetBoolField("success");
				FString Message = JsonObject->GetStringField("message");
				Callback(bRegisterSuccess, Message);
			}
			else
			{
				Callback(false, TEXT("응답 파싱 실패"));
			}
		});

	Request->ProcessRequest();
}
