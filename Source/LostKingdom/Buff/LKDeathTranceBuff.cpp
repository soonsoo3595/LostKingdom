// Fill out your copyright notice in the Description page of Project Settings.


#include "Buff/LKDeathTranceBuff.h"
#include "Buff/LKBuffData.h"
#include "Character/LKCharacterBase.h"
#include "CharacterStat/LKCharacterStatComponent.h"

void ULKDeathTranceBuff::OnBuffStart(ALKCharacterBase* InTarget)
{
	Super::OnBuffStart(InTarget);

	if (Target)
	{
		BuffStat = FLKCharacterStat();
		FLKCharacterStat CharacterStat = Target->Stat->GetBaseStat() + Target->Stat->GetEquipmentStat();
		BuffStat.ATK = CharacterStat.ATK * Data->BuffCoefficient;

		Target->Stat->AddBuffStat(BuffStat);
		Target->Stat->AddBattleBuffStat(Data->BuffBattleStat);
	}
}

void ULKDeathTranceBuff::OnBuffEnd()
{
	if (Target)
	{
		Target->Stat->AddBuffStat(BuffStat * -1);
		Target->Stat->MinusBattleBuffStat(Data->BuffBattleStat);
	}

	Super::OnBuffEnd();
}
