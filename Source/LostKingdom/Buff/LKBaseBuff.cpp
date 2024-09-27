// Fill out your copyright notice in the Description page of Project Settings.


#include "Buff/LKBaseBuff.h"
#include "Buff/LKBuffData.h"
#include "Character/LKCharacterBase.h"

ULKBaseBuff::ULKBaseBuff()
{
	BuffStat = FLKCharacterStat();
}

void ULKBaseBuff::OnBuffStart(ALKCharacterBase* InTarget)
{
	Target = InTarget;

	GetWorld()->GetTimerManager().SetTimer(BuffTimerHandle, this, &ULKBaseBuff::OnBuffEnd, Data->BuffDuration, false);
}

void ULKBaseBuff::OnBuffEnd()
{
	if (Target)
	{
		Target->RemoveBuff(this);
	}
}

void ULKBaseBuff::OnBuffReset()
{
	if (Target)
	{
		GetWorld()->GetTimerManager().ClearTimer(BuffTimerHandle);
		GetWorld()->GetTimerManager().SetTimer(BuffTimerHandle, this, &ULKBaseBuff::OnBuffEnd, Data->BuffDuration, false);
	}
}
