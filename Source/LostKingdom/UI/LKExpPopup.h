// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "LKExpPopup.generated.h"

/**
 * 
 */
UCLASS()
class LOSTKINGDOM_API ULKExpPopup : public UUserWidget
{
	GENERATED_BODY()
	
public:
	void SetExpText(int32 InCurrentExp, int32 InMaxExp);
		
protected:
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<class UTextBlock> ExpText;

};
