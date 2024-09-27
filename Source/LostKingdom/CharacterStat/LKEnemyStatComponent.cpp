// Fill out your copyright notice in the Description page of Project Settings.


#include "CharacterStat/LKEnemyStatComponent.h"
#include "GameData/LKGameSingleton.h"

void ULKEnemyStatComponent::SetLevelStat(int32 InNewLevel)
{
	CurrentLevel = FMath::Clamp(InNewLevel, 1, ULKGameSingleton::Get().CharacterMaxLevel);
	SetBaseStat(ULKGameSingleton::Get().GetEnemyStat(CurrentLevel));
}
