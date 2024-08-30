// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UI/LKUserWidget.h"
#include "LKExpWidget.generated.h"

/**
 * 
 */
UCLASS()
class LOSTKINGDOM_API ULKExpWidget : public ULKUserWidget
{
	GENERATED_BODY()
	
protected:
	virtual void NativeConstruct() override;
	
	virtual void NativeOnMouseEnter(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent) override;
	virtual void NativeOnMouseLeave(const FPointerEvent& InMouseEvent) override;

public:
	void UpdateExpGuage(int32 InCurrentExp, int32 InMaxExp);
	void UpdateExpLevel(int32 InLevel);

protected:
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<class UProgressBar> ExpGuage;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<class UTextBlock> ExpLevel;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, category = Popup)
	TObjectPtr<class ULKExpPopup> ExpPopup;

protected:
	UPROPERTY(VisibleAnywhere, Category = "Exp")
	int32 CurrentExp;

	UPROPERTY(VisibleAnywhere, Category = "Exp")
	int32 MaxExp;
};
