// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/GameInstanceSubsystem.h"
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

	void RequestLogin(const FString& ID, const FString& PW, TFunction<void(bool, const FString&)> Callback);
	void RequestRegister(const FString& ID, const FString& PW, TFunction<void(bool, const FString&)> Callback);

private:
	FString ServerURL;
};
