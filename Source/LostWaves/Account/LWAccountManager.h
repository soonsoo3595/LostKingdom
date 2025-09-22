// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Game/LWGameInstanceSubsystem.h"
#include "Game/LWGameInstanceSubsystemTemplate.h"
#include "Type/LWAccountType.h"
#include "Account/LWLoginSession.h"
#include "LWAccountManager.generated.h"


DECLARE_MULTICAST_DELEGATE_TwoParams(FOnLoginRequestAckSignature, bool /* Is Login */, const FString& /* Message */);

/**
 * 
 */
UCLASS()
class LOSTWAVES_API ULWAccountManager : public ULWGameInstanceSubsystem, public TLWGameInstanceSubsystemBase<ULWAccountManager>
{
	GENERATED_BODY()
	
public:
	virtual bool ShouldCreateSubsystem(UObject* Outer) const override;

protected:
	virtual void Initialize(FSubsystemCollectionBase& Collection) override;

public:
	void RequestLogin(ELWProviderType LoginProviderType, const FString& InToken = TEXT(""));
	void RequestLogout();
	void TryAutoLogin();

	void RequestGoogleLoginWithAuthCode(const FString& AuthCode);

	void SaveLoginSession();
	bool LoadLoginSession();
	void ClearLoginSession();

	void ConnectToServer();

	bool IsLoggedIn() const { return LoginSession.IsValid(); }
	const FLWLoginSession& GetSession() const { return LoginSession; }

public:
	FOnLoginRequestAckSignature OnLoginRequestAck;

private:
	void HandleLoginSuccess(const FString& Token, int32 AccountKey, const FGuid& UserKey);
	FString GetToken(ELWProviderType LoginProviderType);

private:
	UPROPERTY()
	FLWLoginSession LoginSession;

	FString AuthServerURL;
	FString GameServerURL;

private:
	UPROPERTY()
	TObjectPtr<class UOAuthTcpListener> OAuthListener;

public:
	void StartOAuthListener();
	void StopOAuthListener();
};