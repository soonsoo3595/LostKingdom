// Fill out your copyright notice in the Description page of Project Settings.


#include "Skill/LKBaseSkill.h"
#include "Skill/LKSkillData.h"
#include "Character/LKCharacterBase.h"
#include "CharacterStat/LKCharacterStatComponent.h"
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
		AnimInstance = Caster->GetAnimInstance();
		if (AnimInstance)
		{
			AnimInstance->Montage_Play(Data->SkillMontage, Caster->Stat->GetSpeed());

			FOnMontageEnded EndDelegate;
			EndDelegate.BindUObject(Caster, &ALKCharacterBase::OnSkillEnd);
			AnimInstance->Montage_SetEndDelegate(EndDelegate, Data->SkillMontage);
		}
		Caster->AddBuff(Buff);
	}
}

void ULKBaseSkill::Complete()
{
}
