// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "LKLoginPlayerController.generated.h"

/**
 * 
 */
UCLASS()
class LOSTKINGDOM_API ALKLoginPlayerController : public APlayerController
{
	GENERATED_BODY()
	
protected:
	virtual void BeginPlay() override;

	void ShowLoginUI();

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "UI")
	TSubclassOf<class ULKLoginUI> LoginUIClass;
};
