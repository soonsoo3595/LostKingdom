// Fill out your copyright notice in the Description page of Project Settings.


#include "Buff/LKSpeedBuff.h"
#include "Character/LKCharacterBase.h"
#include "CharacterStat/LKCharacterStatComponent.h"
#include "Buff/LKBuffData.h"

void ULKSpeedBuff::OnBuffStart(ALKCharacterBase* InTarget)
{
	Super::OnBuffStart(InTarget);

	if (Target)
	{
		Target->Stat->AddBattleBuffStat(Data->BuffBattleStat);
	}
} 

void ULKSpeedBuff::OnBuffEnd()
{
	if (Target)
	{
		Target->Stat->MinusBattleBuffStat(Data->BuffBattleStat);
	}

	Super::OnBuffEnd();
}
