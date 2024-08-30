// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/LKHUDWidget.h"
#include "Components/ProgressBar.h"
#include "Components/TextBlock.h"
#include "Interface/LKCharacterWidgetInterface.h"

ULKHUDWidget::ULKHUDWidget(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
	MaxHP = -1.0f;
}

void ULKHUDWidget::NativeConstruct()
{
	Super::NativeConstruct();

	ILKCharacterWidgetInterface* CharacterWidget = Cast<ILKCharacterWidgetInterface>(Owner);
	if (CharacterWidget)
	{
		CharacterWidget->SetupCharacterWidget(this);
	}
}

void ULKHUDWidget::UpdateHPBar(float InCurrentHP)
{
	ensure(MaxHP > 0.0f);
	if (PBHPBar)
	{
		PBHPBar->SetPercent(InCurrentHP / MaxHP);
	}
}

void ULKHUDWidget::SetCharacterName(const FText& InCharacterName)
{
	if (TXTName)
	{
		TXTName->SetText(InCharacterName);
	}
}
