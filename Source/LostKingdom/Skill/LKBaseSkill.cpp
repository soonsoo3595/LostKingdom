// Fill out your copyright notice in the Description page of Project Settings.


#include "Skill/LKBaseSkill.h"
#include "Character/LKCharacterBase.h"
#include "Buff/LKBaseBuff.h"

void ULKBaseSkill::PostInitProperties()
{
	Super::PostInitProperties();

	if (BuffClass)
	{
		Buff = NewObject<ULKBaseBuff>(this, BuffClass);
	}
}

void ULKBaseSkill::Use(ALKCharacterBase* Caster)
{
	if (Caster)
	{
		Caster->AddBuff(Buff);
	}
}
