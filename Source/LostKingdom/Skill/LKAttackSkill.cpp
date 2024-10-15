// Fill out your copyright notice in the Description page of Project Settings.


#include "Skill/LKAttackSkill.h"
#include "Character/LKCharacterBase.h"
#include "CharacterStat/LKCharacterStatComponent.h"
#include "Skill/LKSkillData.h"
#include "Interface/LKDamageInterface.h"

void ULKAttackSkill::Attack(ALKCharacterBase* Caster)
{
	if (Caster)
	{
		TArray<FHitResult> HitResults;

		FCollisionQueryParams Params(SCENE_QUERY_STAT(SkillAttack), false, Caster);

		const float AttackDamage = Caster->Stat->GetAttack() * Data->SkillCoefficient;
		const float FinalDamage = FMath::FRandRange(AttackDamage * 0.9f, AttackDamage * 1.1f);

		FVector Start = Caster->GetActorLocation();
		FVector End = Start + Caster->GetActorForwardVector() * AttackRange;

		bool HitDetected = Caster->GetWorld()->SweepMultiByChannel(HitResults, Start, End, FQuat::Identity, ECollisionChannel::ECC_GameTraceChannel6, FCollisionShape::MakeSphere(AttackRadius), Params);
		if(HitDetected)
		{
			for (FHitResult HitResult : HitResults)
			{
				ILKDamageInterface* Target = Cast<ILKDamageInterface>(HitResult.GetActor());
				if (Target && Target->OnDamaged(Caster, AttackDamage))
				{
					Caster->AttackSuccess();
				}
			}
		}

#if ENABLE_DRAW_DEBUG
		FVector CapsuleOrigin = Start + (End - Start) * 0.5f;
		float CapsuleHalfHeight = AttackRange * 0.5f;
		FColor DrawColor = HitDetected ? FColor::Green : FColor::Red;
		DrawDebugCapsule(Caster->GetWorld(), CapsuleOrigin, CapsuleHalfHeight, AttackRadius, FRotationMatrix::MakeFromZ(Caster->GetActorForwardVector()).ToQuat(), DrawColor, false, 5.0f);
#endif
	}
}
