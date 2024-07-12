// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CharacterStat/LKCharacterStatComponent.h"
#include "GameData/LKBattleStat.h"
#include "LKPlayerCharacterStatComponent.generated.h"

/**
 * 
 */
UCLASS()
class LOSTKINGDOM_API ULKPlayerCharacterStatComponent : public ULKCharacterStatComponent
{
	GENERATED_BODY()
	
public:
	ULKPlayerCharacterStatComponent();

protected:
	virtual void InitializeComponent() override;
	virtual void SetLevelStat(int32 InNewLevel) override;

public:
	FORCEINLINE const FLKBattleStat& GetBattleStat() { return BattleStat; }
	FORCEINLINE void SetBattleStat(const FLKBattleStat& InBattleStat) { BattleStat = InBattleStat; }
	FORCEINLINE void AddBattleStat(const FLKBattleStat& InAddBattleStat) { BattleStat = BattleStat + InAddBattleStat; }

protected:
	UPROPERTY(Transient, VisibleInstanceOnly, Category = "BattleStat", Meta = (AllowPrivateAccess = true))
	FLKBattleStat BattleStat;
};
