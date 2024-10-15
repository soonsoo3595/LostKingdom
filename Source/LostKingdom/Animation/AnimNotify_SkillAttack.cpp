// Fill out your copyright notice in the Description page of Project Settings.


#include "Animation/AnimNotify_SkillAttack.h"
#include "Interface/LKAttackInterface.h"

void UAnimNotify_SkillAttack::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, const FAnimNotifyEventReference& EventReference)
{
	Super::Notify(MeshComp, Animation, EventReference);
	
	if (MeshComp)
	{
		ILKAttackInterface* AttackPawn = Cast<ILKAttackInterface>(MeshComp->GetOwner());
		if (AttackPawn)
		{
			AttackPawn->SkillAttack();
		}
	}
}
