// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "Type/LKAccountType.h"
#include "Account/LKLoginSession.h"
#include "LKAccountManager.generated.h"

/**
 * 
 */
UCLASS()
class LOSTKINGDOM_API ULKAccountManager : public UGameInstanceSubsystem
{
	GENERATED_BODY()
	
protected:
	virtual void Initialize(FSubsystemCollectionBase& Collection) override;

public:
	static ULKAccountManager* Get(UWorld* WorldContext);

	void RequestLogin(ELKProviderType LoginProviderType, TFunction<void(bool, const FString&)> Callback);
	void RequestLogout(TFunction<void(bool, const FString&)> Callback);
	void TryAutoLogin(TFunction<void(bool)> Callback);

	void SaveLoginSession();
	bool LoadLoginSession();
	void ClearLoginSession();

	bool IsLoggedIn() const { return LoginSession.IsValid(); }
	const FLKLoginSession& GetSession() const { return LoginSession; }

private:
	void HandleLoginSuccess(const FString& Token, int32 AccountKey, const FGuid& UserKey);
	FString GetToken(ELKProviderType LoginProviderType);

private:
	UPROPERTY()
	FLKLoginSession LoginSession;

	FString ServerURL;
};
