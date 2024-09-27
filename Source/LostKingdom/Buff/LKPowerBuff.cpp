// Fill out your copyright notice in the Description page of Project Settings.


#include "Buff/LKPowerBuff.h"
#include "Buff/LKBuffData.h"
#include "Character/LKCharacterBase.h"
#include "CharacterStat/LKCharacterStatComponent.h"


void ULKPowerBuff::OnBuffStart(ALKCharacterBase* InTarget)
{
	Super::OnBuffStart(InTarget);

	if (Target)
	{
		BuffStat = FLKCharacterStat();

		FLKCharacterStat CharacterStat = Target->Stat->GetBaseStat() + Target->Stat->GetEquipmentStat();
		BuffStat.ATK = CharacterStat.ATK * Data->BuffCoefficient;
		Target->Stat->AddBuffStat(BuffStat);
	}
}

void ULKPowerBuff::OnBuffEnd()
{
	if (Target)
	{
		Target->Stat->AddBuffStat(BuffStat * -1);
	}
	Super::OnBuffEnd();
}
