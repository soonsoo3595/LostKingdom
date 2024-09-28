// Fill out your copyright notice in the Description page of Project Settings.


#include "Skill/LKDeathTranceSkill.h"
#include "Buff/LKBaseBuff.h"

void ULKDeathTranceSkill::SetBuffData(int32 Index)
{
	if (BuffDatas.IsValidIndex(Index - 1))
	{
		Buff->SetData(BuffDatas[Index - 1]);
	}
}
