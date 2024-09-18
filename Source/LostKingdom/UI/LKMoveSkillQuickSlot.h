// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UI/LKSkillQuickSlot.h"
#include "LKMoveSkillQuickSlot.generated.h"

/**
 * 
 */
UCLASS()
class LOSTKINGDOM_API ULKMoveSkillQuickSlot : public ULKSkillQuickSlot
{
	GENERATED_BODY()
	
protected:
	virtual void NativeConstruct() override;

	virtual bool UseSlot() override;
	virtual void OnCooldownEnd() override;
};
