// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "LWGameInstanceSubsystem.generated.h"

/**
 * 
 */
UCLASS()
class LOSTWAVES_API ULWGameInstanceSubsystem : public UGameInstanceSubsystem
{
	GENERATED_BODY()
	
public:
	virtual void ResetSubsystem(const FString& MapName) {}
};
