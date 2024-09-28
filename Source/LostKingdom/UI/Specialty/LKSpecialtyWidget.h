// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UI/LKUserWidget.h"
#include "Specialty/LKSpecialtyComponent.h"
#include "LKSpecialtyWidget.generated.h"

/**
 * 
 */
UCLASS()
class LOSTKINGDOM_API ULKSpecialtyWidget : public ULKUserWidget
{
	GENERATED_BODY()
	
public:
	void UpdateOrbs(float InCurrentGuage);
	void ChangeOrbColor(ESpecialtyType SpecialType);

protected:
	virtual void NativeOnInitialized() override;
	virtual void NativeConstruct() override;

protected:
	UPROPERTY()
	TArray<class ULKOrbWidget*> Orbs;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Color")
	FLinearColor ActiveColor;
};
