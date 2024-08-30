// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/LKExpWidget.h"
#include "Components/ProgressBar.h"
#include "Components/TextBlock.h"
#include "Interface/LKCharacterWidgetInterface.h"
#include "UI/LKExpPopup.h"
#include "Components/CanvasPanelSlot.h"
#include "Blueprint/WidgetLayoutLibrary.h"

void ULKExpWidget::NativeConstruct()
{
	Super::NativeConstruct();

	ILKCharacterWidgetInterface* CharacterWidget = Cast<ILKCharacterWidgetInterface>(Owner);
	if (CharacterWidget)
	{
		CharacterWidget->SetupCharacterWidget(this);
	}

	if (ExpPopup)
	{
		ExpPopup->SetVisibility(ESlateVisibility::Hidden);
	}
}

void ULKExpWidget::NativeOnMouseEnter(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent)
{
	Super::NativeOnMouseEnter(InGeometry, InMouseEvent);

	if (ExpPopup)
	{
		ExpPopup->SetExpText(CurrentExp, MaxExp);
		ExpPopup->SetVisibility(ESlateVisibility::Visible);
	
		FVector2D MousePosition = UWidgetLayoutLibrary::GetMousePositionOnViewport(GetWorld());
		FVector2D FinalPosition = { MousePosition.X, MousePosition.Y - 5.0f };

		UCanvasPanelSlot* CanvasSlot = Cast<UCanvasPanelSlot>(ExpPopup->Slot);
		if (CanvasSlot)
		{
			CanvasSlot->SetPosition(FinalPosition);
		}
	}
}

void ULKExpWidget::NativeOnMouseLeave(const FPointerEvent& InMouseEvent)
{
	Super::NativeOnMouseLeave(InMouseEvent);

	if (ExpPopup)
	{
		ExpPopup->SetVisibility(ESlateVisibility::Hidden);
	}
}

void ULKExpWidget::UpdateExpGuage(int32 InCurrentExp, int32 InMaxExp)
{
	CurrentExp = InCurrentExp;
	MaxExp = InMaxExp;

	if (ExpGuage)
	{
		ExpGuage->SetPercent((float)InCurrentExp / (float)InMaxExp);
	}
}

void ULKExpWidget::UpdateExpLevel(int32 InLevel)
{
	if (ExpLevel)
	{
		ExpLevel->SetText(FText::FromString(FString::FromInt(InLevel)));
	}
}
