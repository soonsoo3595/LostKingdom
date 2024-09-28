// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "LKOrbWidget.generated.h"

/**
 * 
 */
UCLASS()
class LOSTKINGDOM_API ULKOrbWidget : public UUserWidget
{
	GENERATED_BODY()
	
public:
	void UpdateOrb(float InPercent);
	void ChangeColor(FLinearColor NewColor);

protected:
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<class UProgressBar> Guage;
};
