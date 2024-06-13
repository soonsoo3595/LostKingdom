// Fill out your copyright notice in the Description page of Project Settings.


#include "Animation/AnimNotify_AttackEnd.h"
#include "Interface/LKAttackInterface.h"

void UAnimNotify_AttackEnd::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation)
{
	Super::Notify(MeshComp, Animation);

	if (MeshComp)
	{
		ILKAttackInterface* AttackPawn = Cast<ILKAttackInterface>(MeshComp->GetOwner());
		if (AttackPawn)
		{
			AttackPawn->AttackEnd();
		}
	}
}
