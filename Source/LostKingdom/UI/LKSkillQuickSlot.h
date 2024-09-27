// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UI/LKBaseQuickSlot.h"
#include "LKSkillQuickSlot.generated.h"

/**
 * 
 */
UCLASS()
class LOSTKINGDOM_API ULKSkillQuickSlot : public ULKBaseQuickSlot
{
	GENERATED_BODY()
	
protected:
	virtual void NativeConstruct() override;
	virtual bool NativeOnDrop(const FGeometry& InGeometry, const FDragDropEvent& InDragDropEvent, UDragDropOperation* InOperation) override;
	virtual FReply NativeOnMouseButtonDown(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent) override;
	virtual void NativeOnDragDetected(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent, UDragDropOperation*& OutOperation) override;

protected:
	virtual void OnKeyInputComplete() override;
	virtual void SetImage() override;
	virtual void UpdateSlot() override;
	virtual bool UseSlot() override;

protected:
	// To Debug
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Skill")
	TSubclassOf<class ULKBaseSkill> SkillClass;

	UPROPERTY()
	TObjectPtr<class ULKBaseSkill> Skill;

};
