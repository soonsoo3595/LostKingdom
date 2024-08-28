// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "LKBaseQuickSlot.generated.h"

/**
 * 
 */
UCLASS()
class LOSTKINGDOM_API ULKBaseQuickSlot : public UUserWidget
{
	GENERATED_BODY()
	
protected:
	virtual void NativeConstruct() override;

protected:
	UFUNCTION(BlueprintCallable, Category = "QuickSlot")
	virtual bool CanDrop(UObject* DropObject) const;

	virtual bool NativeOnDrop(const FGeometry& InGeometry, const FDragDropEvent& InDragDropEvent, UDragDropOperation* InOperation) override;

	virtual void SetImage();
	void SetKey();

	virtual void UseSlot();

// Input
protected:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	class UInputAction* Action;

	UPROPERTY()
	FKey MappedKey;

// Component
protected:
	UPROPERTY(meta=(BindWidget))
	TObjectPtr<class UImage> Image;

	UPROPERTY(meta=(BindWidget))
	TObjectPtr<class UTextBlock> KeyText;

protected:
	uint8 bIsEmpty : 1;
};
