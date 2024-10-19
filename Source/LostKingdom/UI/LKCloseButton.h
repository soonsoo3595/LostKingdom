// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "LKCloseButton.generated.h"

/**
 * 
 */
UCLASS()
class LOSTKINGDOM_API ULKCloseButton : public UUserWidget
{
	GENERATED_BODY()
	
protected:
	virtual void NativeConstruct() override;

public:
	FORCEINLINE void SetTargetWidget(class UUserWidget* InTargetWidget) { TargetWidget = InTargetWidget; }

protected:
	UFUNCTION()
	void OnBtnClicked();

protected:
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<class UButton> Btn;

	UPROPERTY()
	TObjectPtr<class UUserWidget> TargetWidget;
};
