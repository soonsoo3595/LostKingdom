// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CharacterStat/LKCharacterStatComponent.h"
#include "GameData/LKBattleStat.h"
#include "LKPlayerCharacterStatComponent.generated.h"

DECLARE_MULTICAST_DELEGATE_OneParam(FOnBattleStatChangedDelegate, const FLKBattleStat&);
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
	virtual void BeginPlay() override;
	virtual void SetLevelStat(int32 InNewLevel) override;

	void UpdateStat();

public:
	FOnBattleStatChangedDelegate OnBattleStatChanged;

	FORCEINLINE const FLKBattleStat& GetBattleStat() { return BattleStat; }
	void SetBattleStat(const FLKBattleStat& InBattleStat);
	void AddBattleStat(const FLKBattleStat& InAddBattleStat);

	virtual float GetSpeed() override;
	virtual bool CheckCriticalHit() override;

protected:
	UPROPERTY(Transient, VisibleInstanceOnly, Category = "BattleStat", Meta = (AllowPrivateAccess = true))
	FLKBattleStat BattleStat;

	UPROPERTY(Transient, EditAnywhere, Category = "BattleStat", Meta = (AllowPrivateAccess = true))
	FLKBattleStat TestBattleStat;

	// Character Special Ability

private:
	UPROPERTY(VisibleInstanceOnly, Category = "BattleStat", Meta = (AllowPrivateAccess = true))
	float CritPercent;

	UPROPERTY(VisibleInstanceOnly, Category = "BattleStat", Meta = (AllowPrivateAccess = true))
	float SpecialPercent;

	UPROPERTY(VisibleInstanceOnly, Category = "BattleStat", Meta = (AllowPrivateAccess = true))
	float SpeedPercent;

	float CriticalRate;
	float SpecialRate;
	float SpeedRate;
};
