// Fill out your copyright notice in the Description page of Project Settings.


#include "Animation/AnimNotify_ComboCheck.h"
#include "Character/LKPlayerCharacter.h"
#include "Interface/LKAttackInterface.h"

void UAnimNotify_ComboCheck::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation)
{
	Super::Notify(MeshComp, Animation);

	if (MeshComp)
	{
		ILKAttackInterface* AttackPawn = Cast<ILKAttackInterface>(MeshComp->GetOwner());
		if (AttackPawn)
		{
			AttackPawn->ComboAttackCheck();
		}
	}
}
