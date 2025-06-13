// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "LKGameInstanceSubsystem.h"
#include "LKGameInstanceSubsystemTemplate.h"
#include "Type/LKAccountType.h"
#include "Account/LKLoginSession.h"
#include "LKAccountManager.generated.h"

DECLARE_MULTICAST_DELEGATE_TwoParams(FOnLoginRequestAckSignature, bool /* Is Login */, const FString& /* Message */);

/**
 * 
 */
UCLASS()
class LOSTKINGDOM_API ULKAccountManager : public ULKGameInstanceSubsystem, public TLKGameInstanceSubsystemBase<ULKAccountManager>
{
	GENERATED_BODY()
	
protected:
	virtual void Initialize(FSubsystemCollectionBase& Collection) override;

public:
	void RequestLogin(ELKProviderType LoginProviderType, const FString& InToken = TEXT(""));
	void RequestLogout();
	void TryAutoLogin();

	void RequestGoogleLoginWithAuthCode(const FString& AuthCode);

	void SaveLoginSession();
	bool LoadLoginSession();
	void ClearLoginSession();

	bool IsLoggedIn() const { return LoginSession.IsValid(); }
	const FLKLoginSession& GetSession() const { return LoginSession; }

public:
	FOnLoginRequestAckSignature OnLoginRequestAck;

private:
	void HandleLoginSuccess(const FString& Token, int32 AccountKey, const FGuid& UserKey);
	FString GetToken(ELKProviderType LoginProviderType);

private:
	UPROPERTY()
	FLKLoginSession LoginSession;

	FString ServerURL;

private:
	UPROPERTY()
	TObjectPtr<class UOAuthTcpListener> OAuthListener;

public:
	void StartOAuthListener();
	void StopOAuthListener();
};
