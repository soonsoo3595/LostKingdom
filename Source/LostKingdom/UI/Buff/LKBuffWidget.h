// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "LKBuffWidget.generated.h"

/**
 * 
 */
UCLASS()
class LOSTKINGDOM_API ULKBuffWidget : public UUserWidget
{
	GENERATED_BODY()
	
public:
	ULKBuffWidget(const FObjectInitializer& ObjectInitializer);
	virtual void SetBuffWidget(class ULKBaseBuff* InBuff);
	virtual void UpdateTime();

protected:
	virtual void DisplayBuffIcon();

protected:
	virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime) override;

protected:
	UPROPERTY()
	TObjectPtr<class ULKBaseBuff> Buff;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<class UImage> BuffIcon;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<class UTextBlock> BuffDuration;

private:
	float BuffRemainingTime;

};
