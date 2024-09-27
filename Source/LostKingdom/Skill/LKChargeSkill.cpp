// Fill out your copyright notice in the Description page of Project Settings.


#include "Skill/LKChargeSkill.h"
#include "Skill/LKSkillData.h"
#include "Character/LKCharacterBase.h"
#include "CharacterStat/LKCharacterStatComponent.h"

void ULKChargeSkill::Use(ALKCharacterBase* Caster)
{
	if (Caster)
	{
		AnimInstance = Caster->GetAnimInstance();
		if (AnimInstance)
		{
			AnimInstance->Montage_Play(Data->SkillMontage, Caster->Stat->GetSpeed());
			AnimInstance->Montage_JumpToSection(FName("ChargeStart"), Data->SkillMontage);

			GetWorld()->GetTimerManager().SetTimer(ChargeTimer, this, &ULKChargeSkill::FinishCharge, ChargeTime, false);

			FOnMontageEnded EndDelegate;
			EndDelegate.BindUObject(Caster, &ALKCharacterBase::OnSkillEnd);
			AnimInstance->Montage_SetEndDelegate(EndDelegate, Data->SkillMontage);
		}
	}
}

void ULKChargeSkill::Complete()
{
	GetWorld()->GetTimerManager().ClearTimer(ChargeTimer);
	if (AnimInstance) 
	{
		AnimInstance->Montage_Stop(0.2f, Data->SkillMontage);
	}
}

void ULKChargeSkill::FinishCharge()
{
	if (AnimInstance)
	{
		AnimInstance->Montage_JumpToSection(FName("ChargeEnd"), Data->SkillMontage);
	}
}
