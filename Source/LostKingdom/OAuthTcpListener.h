// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "OAuthTcpListener.generated.h"

/**
 * 
 */
UCLASS()
class LOSTKINGDOM_API UOAuthTcpListener : public UObject
{
	GENERATED_BODY()
	
public:
	bool Start(uint16 Port = 5005, UWorld* InWorldContext = nullptr);
	void Stop();

private:
	FSocket* ListenerSocket = nullptr;
	FTimerHandle AcceptTimerHandle;

	void AcceptConnection();
	void HandleClient(FSocket* ClientSocket);
	FString ExtractAuthCodeFromRequest(const FString& Request);

	UPROPERTY()
	TObjectPtr<UWorld> WorldContext;
};
