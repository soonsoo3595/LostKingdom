// Fill out your copyright notice in the Description page of Project Settings.


#include "CharacterStat/LKPlayerCharacterStatComponent.h"
#include "GameData/LKGameSingleton.h"

void ULKPlayerCharacterStatComponent::SetLevelStat(int32 InNewLevel)
{
	CurrentLevel = FMath::Clamp(InNewLevel, 1, ULKGameSingleton::Get().CharacterMaxLevel);
	SetBaseStat(ULKGameSingleton::Get().GetPlayerStat(CurrentLevel));
}

void ULKPlayerCharacterStatComponent::AddExp(int32 InExp)
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
