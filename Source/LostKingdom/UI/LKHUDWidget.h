// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UI/LKUserWidget.h"
#include "LKHUDWidget.generated.h"

/**
 * 
 */
UCLASS()
class LOSTKINGDOM_API ULKHUDWidget : public ULKUserWidget
{
	GENERATED_BODY()
	
public:
	ULKHUDWidget(const FObjectInitializer& ObjectInitializer);

protected:
	virtual void NativeConstruct() override;

public:
	FORCEINLINE void SetMaxHP(float InMaxHP) { MaxHP = InMaxHP; }
	void UpdateHPBar(float InCurrentHP);
	void SetCharacterName(const FText& InCharacterName);

protected:
	UPROPERTY()
	TObjectPtr<class UProgressBar> HPProgressBar;

	UPROPERTY()
	TObjectPtr<class UTextBlock> CharacterName;

	UPROPERTY()
	float MaxHP;
};
