// Fill out your copyright notice in the Description page of Project Settings.


#include "Buff/LKSpeedBuff.h"
#include "Buff/LKBuffData.h"
#include "Character/LKCharacterBase.h"
#include "CharacterStat/LKCharacterStatComponent.h"

void ULKSpeedBuff::OnBuffStart(ALKCharacterBase* InTarget)
{
	Super::OnBuffStart(InTarget);

	if (Target)
	{
		Target->Stat->AddBattleBuffStat(BuffBattleStat);
	}
} 

void ULKSpeedBuff::OnBuffEnd()
{
	if (Target)
	{
		Target->Stat->MinusBattleBuffStat(BuffBattleStat);
	}

	Super::OnBuffEnd();
}
