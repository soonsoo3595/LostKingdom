// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UI/LKUserWidget.h"
#include "LKMainHUD.generated.h"

/**
 * 
 */
UCLASS()
class LOSTKINGDOM_API ULKMainHUD : public ULKUserWidget
{
	GENERATED_BODY()
	
protected:
	virtual void NativeConstruct() override;

protected:
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<class UProgressBar> ExpGuage;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<class UTextBlock> ExpLevel;

protected:
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<class UTextBlock> Time;

	void UpdateTime();
};
