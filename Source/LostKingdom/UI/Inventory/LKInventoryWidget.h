// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UI/LKUserWidget.h"
#include "LKInventoryWidget.generated.h"

/**
 * 
 */
UCLASS()
class LOSTKINGDOM_API ULKInventoryWidget : public ULKUserWidget
{
	GENERATED_BODY()
	
protected:
	virtual void NativeOnInitialized() override;
	virtual void NativeConstruct() override;

	FORCEINLINE virtual bool NativeOnDrop(const FGeometry& InGeometry, const FDragDropEvent& InDragDropEvent, UDragDropOperation* InOperation) override { UE_LOG(LogTemp, Log, TEXT("Drop"));  return false; }
	FORCEINLINE virtual FReply NativeOnMouseButtonDown(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent) override { return FReply::Handled(); }
	FORCEINLINE virtual FReply NativeOnMouseButtonDoubleClick(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent) override { return FReply::Handled(); }
	FORCEINLINE virtual FReply NativeOnMouseWheel(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent) override { return FReply::Handled(); }

protected:
	UPROPERTY()
	TArray<class ULKInventorySlot*> Slots;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<class ULKCloseButton> Close;
};
