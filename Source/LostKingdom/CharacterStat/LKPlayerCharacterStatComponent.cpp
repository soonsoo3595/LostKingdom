// Fill out your copyright notice in the Description page of Project Settings.


#include "CharacterStat/LKPlayerCharacterStatComponent.h"
#include "GameData/LKGameSingleton.h"

ULKPlayerCharacterStatComponent::ULKPlayerCharacterStatComponent()
{
	CriticalRate = 0.036f;
	SpecialRate = 0.1f;
	SpeedRate = 0.02f;

	bWantsInitializeComponent = true;
}

void ULKPlayerCharacterStatComponent::BeginPlay()
{
	SetBattleStat(TestBattleStat);
}

void ULKPlayerCharacterStatComponent::SetLevelStat(int32 InNewLevel)
{
	CurrentLevel = FMath::Clamp(InNewLevel, 1, ULKGameSingleton::Get().CharacterMaxLevel);
	SetBaseStat(ULKGameSingleton::Get().GetPlayerStat(CurrentLevel));
	check(BaseStat.MaxHP > 0);
}

void ULKPlayerCharacterStatComponent::UpdateStat()
{
	CritPercent = (BattleStat.Crit * CriticalRate) / 100;
	SpecialPercent = (BattleStat.Special * SpecialRate) / 100;
	SpeedPercent = (BattleStat.Speed * SpeedRate) / 100;
}

void ULKPlayerCharacterStatComponent::SetBattleStat(const FLKBattleStat& InBattleStat)
{
	BattleStat = InBattleStat;
	UpdateStat();
	OnBattleStatChanged.Broadcast(BattleStat);
}

void ULKPlayerCharacterStatComponent::AddBattleStat(const FLKBattleStat& InAddBattleStat)
{
	BattleStat = BattleStat + InAddBattleStat;
	UpdateStat();
	OnBattleStatChanged.Broadcast(BattleStat);
}

float ULKPlayerCharacterStatComponent::GetSpeed()
{
	float Speed = Super::GetSpeed();

	Speed += SpeedPercent;

	return Speed;
}

bool ULKPlayerCharacterStatComponent::CheckCriticalHit()
{
	return FMath::FRandRange(0.0f, 1.0f) <= CritPercent;
}
