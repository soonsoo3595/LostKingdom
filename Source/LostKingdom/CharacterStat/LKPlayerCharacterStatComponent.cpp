// Fill out your copyright notice in the Description page of Project Settings.


#include "CharacterStat/LKPlayerCharacterStatComponent.h"
#include "GameData/LKGameSingleton.h"

ULKPlayerCharacterStatComponent::ULKPlayerCharacterStatComponent()
{
	bWantsInitializeComponent = true;
}

void ULKPlayerCharacterStatComponent::InitializeComponent()
{
	Super::InitializeComponent();
}

void ULKPlayerCharacterStatComponent::SetLevelStat(int32 InNewLevel)
{
	CurrentLevel = FMath::Clamp(InNewLevel, 1, ULKGameSingleton::Get().CharacterMaxLevel);
	SetBaseStat(ULKGameSingleton::Get().GetPlayerStat(CurrentLevel));
	check(BaseStat.MaxHP > 0);
}
