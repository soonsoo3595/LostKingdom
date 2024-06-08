// Fill out your copyright notice in the Description page of Project Settings.


#include "Animation/AnimNotify_ComboCheck.h"
#include "Character/LKPlayerCharacter.h"

void UAnimNotify_ComboCheck::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation)
{
	Super::Notify(MeshComp, Animation);

	if (MeshComp)
	{
		ALKPlayerCharacter* PlayerCharacter = Cast<ALKPlayerCharacter>(MeshComp->GetOwner());
		if (PlayerCharacter)
		{
			PlayerCharacter->NotifyCombo();
		}
	}
}
