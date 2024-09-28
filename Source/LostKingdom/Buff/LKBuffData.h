// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "GameData/LKBattleStat.h"
#include "LKBuffData.generated.h"

/**
 * 
 */
UCLASS()
class LOSTKINGDOM_API ULKBuffData : public UPrimaryDataAsset
{
	GENERATED_BODY()
	
public:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Buff")
	FName BuffName;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Buff")
	FText BuffDescription;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Buff")
	UTexture2D* BuffIcon;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Buff")
	float BuffDuration;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Buff")
	float BuffCoefficient;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Buff")
	FLKBattleStat BuffBattleStat;
};
