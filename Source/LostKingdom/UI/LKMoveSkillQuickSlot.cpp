// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/LKMoveSkillQuickSlot.h"

void ULKMoveSkillQuickSlot::NativeConstruct()
{
	Super::NativeConstruct();

	SetVisibility(ESlateVisibility::Hidden);
}

bool ULKMoveSkillQuickSlot::UseSlot()
{
	if (Super::UseSlot())
	{
		SetVisibility(ESlateVisibility::Visible);
		return true;
	}

	return false;
}

void ULKMoveSkillQuickSlot::OnCooldownEnd()
{
	Super::OnCooldownEnd();

	SetVisibility(ESlateVisibility::Hidden);
}
