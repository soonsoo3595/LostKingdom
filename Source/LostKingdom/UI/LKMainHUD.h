// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "LKMainHUD.generated.h"

/**
 * 
 */
UCLASS()
class LOSTKINGDOM_API ULKMainHUD : public UUserWidget
{
	GENERATED_BODY()
	
protected:
	virtual void NativeOnInitialized() override;
	virtual void NativeConstruct() override;

protected:
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<class ULKExpWidget> ExpWidget;

protected:
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<class UTextBlock> Time;

	void UpdateTime();
};
