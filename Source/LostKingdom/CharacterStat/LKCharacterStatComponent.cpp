// Fill out your copyright notice in the Description page of Project Settings.


#include "CharacterStat/LKCharacterStatComponent.h"

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
	float RandomDamage = FMath::FRandRange(AttackPower * 0.9f, AttackPower * 1.1f);

	CheckCriticalHit() ? RandomDamage *= 2.0f : RandomDamage;

	return RandomDamage;
}

void ULKCharacterStatComponent::SetHP(float NewHP)
{
	CurrentHP = FMath::Clamp<float>(NewHP, 0, BaseStat.MaxHP);
	OnHPChanged.Broadcast(CurrentHP);
}

void ULKCharacterStatComponent::UpdateBattleStat()
{
	BattleStat.CritPercent = BattleProperty.GetCritical();
	BattleStat.SpecialPercent = BattleProperty.GetSpecial();
	BattleStat.SpeedPercent = BattleProperty.GetSpeed();

	OnBattleStatChanged.Broadcast();
}

