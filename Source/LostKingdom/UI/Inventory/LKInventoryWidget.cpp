// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/Inventory/LKInventoryWidget.h"
#include "UI/Inventory/LKInventorySlot.h"
#include "UI/LKCloseButton.h"

void ULKInventoryWidget::NativeOnInitialized()
{
	Super::NativeOnInitialized();

	for (int32 i = 0; i < 55; i++)
	{
		FString SlotName = FString::Printf(TEXT("WBP_InventorySlot_%d"), i);
		ULKInventorySlot* InventorySlot = Cast<ULKInventorySlot>(GetWidgetFromName(*SlotName));

		if (InventorySlot)
		{
			Slots.Add(InventorySlot);
		}
	}
}

void ULKInventoryWidget::NativeConstruct()
{
	Super::NativeConstruct();

	for (int32 i = 0; i < Slots.Num(); i++)
	{
		Slots[i]->UpdateSlot();
	}

	if (Close)
	{
		Close->SetTargetWidget(this);
	}
}
