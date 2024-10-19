// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/Inventory/LKInventorySlot.h"
#include "Item/LKItem.h"
#include "Item/LKItemData.h"
#include "Components/Image.h"
#include "Components/TextBlock.h"
#include "Blueprint/DragDropOperation.h"
#include "Blueprint/WidgetBlueprintLibrary.h"

void ULKInventorySlot::NativeOnInitialized()
{
	Super::NativeOnInitialized();

	if (ItemClass)
	{
		Item = NewObject<ALKItem>(this, ItemClass);
	}
}

bool ULKInventorySlot::NativeOnDrop(const FGeometry& InGeometry, const FDragDropEvent& InDragDropEvent, UDragDropOperation* InOperation)
{
	UE_LOG(LogTemp, Log, TEXT("NativeOnDrop %s"), *GetName());
	if (InOperation && InOperation->DefaultDragVisual)
	{
		ULKInventorySlot* InventorySlot = Cast<ULKInventorySlot>(InOperation->Payload);
		if(InventorySlot)
		{
			// Replace Item between InventorySlots
			ALKItem* TempItem = Item;
			Item = InventorySlot->Item;
			InventorySlot->Item = TempItem;
			UpdateSlot();
			InventorySlot->UpdateSlot();
		}
		return true;
	}
	return Super::NativeOnDrop(InGeometry, InDragDropEvent, InOperation);
}

FReply ULKInventorySlot::NativeOnMouseButtonDown(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent)
{
	if (Item)
	{
		if (InMouseEvent.IsMouseButtonDown(EKeys::LeftMouseButton))
		{
			return UWidgetBlueprintLibrary::DetectDragIfPressed(InMouseEvent, this, EKeys::LeftMouseButton).NativeReply;
		}
	}
	return FReply::Handled();
}

void ULKInventorySlot::NativeOnDragDetected(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent, UDragDropOperation*& OutOperation)
{
	if (InMouseEvent.IsMouseButtonDown(EKeys::LeftMouseButton))
	{
		UDragDropOperation* DragOperation = NewObject<UDragDropOperation>();
		DragOperation->DefaultDragVisual = Icon;
		DragOperation->DefaultDragVisual->SetVisibility(ESlateVisibility::SelfHitTestInvisible);
		DragOperation->Payload = this;

		OutOperation = DragOperation;
	}
}

void ULKInventorySlot::UpdateSlot()
{
	if (Item)
	{
		SetVisibility(ESlateVisibility::Visible);
		Icon->SetBrushFromTexture(Item->GetItemData()->ItemIcon);
	}
	else
	{
		SetVisibility(ESlateVisibility::Hidden);
	}
}

void ULKInventorySlot::SetVisibility(ESlateVisibility InVisibility)
{
	Icon->SetVisibility(InVisibility);
	CountText->SetVisibility(InVisibility);
}
