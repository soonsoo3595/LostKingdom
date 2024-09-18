// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/LKSkillQuickSlot.h"
#include "Blueprint/DragDropOperation.h"
#include "Blueprint/WidgetBlueprintLibrary.h"
#include "Character/LKCharacterBase.h"
#include "Components/Image.h"
#include "Skill/LKSkillData.h"
#include "Skill/LKBaseSkill.h"

void ULKSkillQuickSlot::NativeConstruct()
{
	Super::NativeConstruct();

	// To Debug
	if (SkillClass)
	{
		Skill = NewObject<ULKBaseSkill>(this, SkillClass);
	}

	UpdateSlot();
}

bool ULKSkillQuickSlot::NativeOnDrop(const FGeometry& InGeometry, const FDragDropEvent& InDragDropEvent, UDragDropOperation* InOperation)
{
	if (InOperation && InOperation->DefaultDragVisual && !bIsCoolDown)
	{
		ULKSkillQuickSlot* QuickSlot = Cast<ULKSkillQuickSlot>(InOperation->Payload);
		if (QuickSlot)
		{
			// Replace Skill between QuickSlots
			ULKBaseSkill* TempSkill = Skill;
			Skill = QuickSlot->Skill;
			QuickSlot->Skill = TempSkill;
			UpdateSlot();
			QuickSlot->UpdateSlot();
		}
		return true;
	}
	return Super::NativeOnDrop(InGeometry, InDragDropEvent, InOperation);
}

FReply ULKSkillQuickSlot::NativeOnMouseButtonDown(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent)
{
	if (Skill && !bIsCoolDown)
	{
		if (InMouseEvent.IsMouseButtonDown(EKeys::LeftMouseButton))
		{
			return UWidgetBlueprintLibrary::DetectDragIfPressed(InMouseEvent, this, EKeys::LeftMouseButton).NativeReply;
		}
	}
	return FReply::Unhandled();
}

void ULKSkillQuickSlot::NativeOnDragDetected(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent, UDragDropOperation*& OutOperation)
{
	if (Image)
	{
		UDragDropOperation* DragOperation = NewObject<UDragDropOperation>();
		DragOperation->DefaultDragVisual = Image;
		DragOperation->Payload = this;

		OutOperation = DragOperation;
	}
}

void ULKSkillQuickSlot::SetImage()
{
	if (Skill)
	{
		Image->SetVisibility(ESlateVisibility::Visible);
		Image->SetBrushFromTexture(Skill->Data->SkillIcon);
	}
	else
	{
		Image->SetVisibility(ESlateVisibility::Hidden);
	}
}

void ULKSkillQuickSlot::UpdateSlot()
{
	if (Skill)
	{
		CooldownTime = Skill->Data->CooldownTime;
	}
	else
	{
		CooldownTime = -1.0f;
	}

	SetImage();
}

bool ULKSkillQuickSlot::UseSlot()
{
	if (Skill && !bIsCoolDown)
	{
		ALKCharacterBase* Caster = Cast<ALKCharacterBase>(Owner);
		if (Caster && Caster->UseSkill(Skill))
		{
			return Super::UseSlot();
		}
	}
	
	return false;
}




