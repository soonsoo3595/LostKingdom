// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/SaveGame.h"
#include "Account/LKLoginSession.h"
#include "LKLoginSaveData.generated.h"

/**
 * 
 */
UCLASS()
class LOSTKINGDOM_API ULKLoginSaveData : public USaveGame
{
	GENERATED_BODY()
	
public:
	UPROPERTY()
	FLKLoginSession SavedSession;
};
