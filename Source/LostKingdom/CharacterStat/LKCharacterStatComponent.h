// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "GameData/LKCharacterStat.h"
#include "LKCharacterStatComponent.generated.h"

DECLARE_MULTICAST_DELEGATE(FOnHPZeroDelegate);
DECLARE_MULTICAST_DELEGATE_OneParam(FOnHPChangedDelegate, float /*CurrentHp*/);
DECLARE_MULTICAST_DELEGATE_TwoParams(FOnStatChangedDelegate, const FLKCharacterStat&, const FLKCharacterStat&);

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
	FOnStatChangedDelegate OnStatChanged;

	FOnExpChangeDelegate OnExpChanged;
	FOnLevelUpDelegate OnLevelUp;

	virtual void SetLevelStat(int32 InNewLevel);
	FORCEINLINE int32 GetCurrentLevel() const { return CurrentLevel; }
	FORCEINLINE int32 GetCurrentExp() const { return CurrentExp; }
	void AddExp(int32 InExp);

	FORCEINLINE void AddBaseStat(const FLKCharacterStat& InAddBaseStat) { BaseStat = BaseStat + InAddBaseStat; OnStatChanged.Broadcast(GetBaseStat(), GetModifierStat()); }
	FORCEINLINE void SetBaseStat(const FLKCharacterStat& InBaseStat) { BaseStat = InBaseStat; OnStatChanged.Broadcast(GetBaseStat(), GetModifierStat()); }
	FORCEINLINE void SetModifierStat(const FLKCharacterStat& InModifierStat) { ModifierStat = InModifierStat; OnStatChanged.Broadcast(GetBaseStat(), GetModifierStat()); }

	FORCEINLINE const FLKCharacterStat& GetBaseStat() { return BaseStat; }
	FORCEINLINE const FLKCharacterStat& GetModifierStat() { return ModifierStat; }
	FORCEINLINE const FLKCharacterStat	GetFinalStat() { return BaseStat + ModifierStat; }
	FORCEINLINE float GetCurrentHp() { return CurrentHP; }
	FORCEINLINE FText GetCharacterName() { return CharacterName; }
	float ApplyDamage(float InDamage);

	float GetAttack();
	FORCEINLINE virtual float GetSpeed() { return 1.0f; }
	FORCEINLINE virtual bool CheckCriticalHit() { return false; }

protected:
	void SetHP(float NewHP);

	UPROPERTY(Transient, VisibleInstanceOnly, Category = Stat)
	float CurrentHP;

	UPROPERTY(VisibleInstanceOnly, Category = Stat)
	int32 CurrentLevel;

	UPROPERTY(VisibleInstanceOnly, Category = Stat)
	int32 CurrentExp;

	UPROPERTY(EditAnywhere, Category = Info)
	FText CharacterName;

	UPROPERTY(Transient, VisibleInstanceOnly, Category = "Stat", Meta = (AllowPrivateAccess = true))
	FLKCharacterStat BaseStat;

	UPROPERTY(Transient, VisibleInstanceOnly, Category = "Stat", Meta = (AllowPrivateAccess = true))
	FLKCharacterStat ModifierStat;

};
