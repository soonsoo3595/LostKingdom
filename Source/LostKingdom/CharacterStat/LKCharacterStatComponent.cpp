// Fill out your copyright notice in the Description page of Project Settings.


#include "CharacterStat/LKCharacterStatComponent.h"
#include "GameData/LKGameSingleton.h"

ULKCharacterStatComponent::ULKCharacterStatComponent()
{
	CurrentLevel = 1;
	CurrentExp = 0;

	bWantsInitializeComponent = true;
}

void ULKCharacterStatComponent::InitializeComponent()
{
	Super::InitializeComponent();

	SetLevelStat(CurrentLevel);
	SetHP(BaseStat.MaxHP);
}

void ULKCharacterStatComponent::SetLevelStat(int32 InNewLevel)
{
	CurrentLevel = FMath::Clamp(InNewLevel, 1, ULKGameSingleton::Get().CharacterMaxLevel);
	SetBaseStat(ULKGameSingleton::Get().GetEnemyStat(CurrentLevel));
	check(BaseStat.MaxHP > 0);
}

void ULKCharacterStatComponent::AddExp(int32 InExp)
{
	CurrentExp += InExp;

	if (CurrentExp >= BaseStat.Exp)
	{
		CurrentExp = FMath::Clamp(CurrentExp - BaseStat.Exp, 0, BaseStat.Exp);
		SetLevelStat(CurrentLevel + 1);
		SetHP(BaseStat.MaxHP);
		OnLevelUp.Broadcast(CurrentLevel);
	}

	OnExpChanged.Broadcast(CurrentExp, BaseStat.Exp);
}

float ULKCharacterStatComponent::ApplyDamage(float InDamage)
{
	const float PrevHP = CurrentHP;
	const float ActualDamage = FMath::Clamp<float>(InDamage, 0, InDamage);

	SetHP(PrevHP - ActualDamage);
	if (CurrentHP <= KINDA_SMALL_NUMBER)
	{
		OnHPZero.Broadcast();
	}

	return ActualDamage;
}

float ULKCharacterStatComponent::GetAttack()
{
	float AttackPower = GetFinalStat().ATK;

	CheckCriticalHit() ? AttackPower *= 2.0f : AttackPower;

	return AttackPower;
}

void ULKCharacterStatComponent::SetHP(float NewHP)
{
	CurrentHP = FMath::Clamp<float>(NewHP, 0, BaseStat.MaxHP);
	OnHPChanged.Broadcast(CurrentHP);
}

