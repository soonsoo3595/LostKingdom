// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "GameData/LKCharacterStat.h"
#include "GameData/LKBattleStat.h"
#include "GameData/LKBattleProperty.h"
#include "LKCharacterStatComponent.generated.h"

DECLARE_MULTICAST_DELEGATE(FOnHPZeroDelegate);
DECLARE_MULTICAST_DELEGATE_OneParam(FOnHPChangedDelegate, float /*CurrentHp*/);

DECLARE_MULTICAST_DELEGATE_OneParam(FOnStatChangedDelegate, const FLKCharacterStat&);
DECLARE_MULTICAST_DELEGATE(FOnBattleStatChangedDelegate);

DECLARE_MULTICAST_DELEGATE_TwoParams(FOnExpChangeDelegate, int32 /*CurrentExp*/ , int32 /*MaxExp*/);
DECLARE_MULTICAST_DELEGATE_OneParam(FOnLevelUpDelegate, int32 /*NewLevel*/);

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class LOSTKINGDOM_API ULKCharacterStatComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	ULKCharacterStatComponent();

protected:
	virtual void InitializeComponent() override;

public:
	FOnHPZeroDelegate OnHPZero;
	FOnHPChangedDelegate OnHPChanged;

	FOnExpChangeDelegate OnExpChanged;
	FOnLevelUpDelegate OnLevelUp;

	FORCEINLINE float GetCurrentHp() { return CurrentHP; }
	FORCEINLINE FText GetCharacterName() { return CharacterName; }
	float ApplyDamage(float InDamage);

	float GetAttack();
	FORCEINLINE float GetSpeed() { return FMath::Clamp(1 + GetFinalBattleStat().SpeedPercent, 0.8f, 1.4f); }
	FORCEINLINE bool CheckCriticalHit() { return FMath::FRandRange(0.0f, 1.0f) <= GetFinalBattleStat().CritPercent; }

	// Level Section
public:
	FORCEINLINE int32 GetCurrentLevel() const { return CurrentLevel; }
	FORCEINLINE int32 GetCurrentExp() const { return CurrentExp; }
	FORCEINLINE virtual void AddExp(int32 InExp) {  }

protected:
	FORCEINLINE virtual void SetLevelStat(int32 InNewLevel) {	}

	UPROPERTY(VisibleInstanceOnly, Category = Stat)
	int32 CurrentLevel;

	UPROPERTY(VisibleInstanceOnly, Category = Stat)
	int32 CurrentExp;

protected:
	void SetHP(float NewHP);

	UPROPERTY(Transient, VisibleInstanceOnly, Category = Stat)
	float CurrentHP;

	UPROPERTY(EditAnywhere, Category = Info)
	FText CharacterName;

	// Stat Section
public:
	FOnStatChangedDelegate OnStatChanged;
	FOnBattleStatChangedDelegate OnBattleStatChanged;

	FORCEINLINE void SetBaseStat(const FLKCharacterStat& InBaseStat) { BaseStat = InBaseStat; OnStatChanged.Broadcast(GetFinalStat()); }
	FORCEINLINE void SetEquipmentStat(const FLKCharacterStat& InModifierStat) { EquipmentStat = InModifierStat; OnStatChanged.Broadcast(GetFinalStat()); }
	FORCEINLINE void AddBuffStat(const FLKCharacterStat& InBuffStat) { BuffStat = BuffStat + InBuffStat; OnStatChanged.Broadcast(GetFinalStat()); }

	FORCEINLINE const FLKCharacterStat& GetBaseStat() { return BaseStat; }
	FORCEINLINE const FLKCharacterStat& GetEquipmentStat() { return EquipmentStat; }
	FORCEINLINE const FLKCharacterStat	GetFinalStat() { return BaseStat + EquipmentStat + BuffStat; }

	FORCEINLINE const FLKBattleStat GetFinalBattleStat() { return BattleStat + BattleBuffStat; }
	FORCEINLINE void AddBattleBuffStat(const FLKBattleStat& InBattleBuffStat) { BattleBuffStat = BattleBuffStat + InBattleBuffStat; UpdateBattleStat(); }
	FORCEINLINE void MinusBattleBuffStat(const FLKBattleStat& InBattleBuffStat) { BattleBuffStat = BattleBuffStat - InBattleBuffStat; UpdateBattleStat(); }

	FORCEINLINE const FLKBattleProperty& GetBattleProperty() { return BattleProperty; }
	FORCEINLINE void AddBattleProperty(const FLKBattleProperty& InBattleProperty) { BattleProperty += InBattleProperty; UpdateBattleStat(); }
	FORCEINLINE void MinusBattleProperty(const FLKBattleProperty& InBattleProperty) { BattleProperty -= InBattleProperty; UpdateBattleStat(); }

	void UpdateBattleStat();

protected:
	UPROPERTY(Transient, VisibleInstanceOnly, Category = "Stat", Meta = (AllowPrivateAccess = true))
	FLKCharacterStat BaseStat;

	UPROPERTY(Transient, VisibleInstanceOnly, Category = "Stat", Meta = (AllowPrivateAccess = true))
	FLKCharacterStat EquipmentStat;

	UPROPERTY(Transient, VisibleInstanceOnly, Category = "Stat", Meta = (AllowPrivateAccess = true))
	FLKCharacterStat BuffStat;

	UPROPERTY(Transient, VisibleInstanceOnly, Category = "Stat", Meta = (AllowPrivateAccess = true))
	FLKBattleStat BattleStat;

	UPROPERTY(Transient, VisibleInstanceOnly, Category = "Stat", Meta = (AllowPrivateAccess = true))
	FLKBattleStat BattleBuffStat;

	UPROPERTY(Transient, VisibleInstanceOnly, Category = "Stat", Meta = (AllowPrivateAccess = true))
	FLKBattleProperty BattleProperty;
};
