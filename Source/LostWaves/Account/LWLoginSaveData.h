// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/SaveGame.h"
#include "Account/LWLoginSession.h"
#include "LWLoginSaveData.generated.h"

/**
 * 
 */
UCLASS()
class LOSTWAVES_API ULWLoginSaveData : public USaveGame
{
	GENERATED_BODY()
	
public:
	UPROPERTY()
	FLWLoginSession SavedSession;
};
