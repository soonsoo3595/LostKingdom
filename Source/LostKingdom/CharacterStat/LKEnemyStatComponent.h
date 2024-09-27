// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CharacterStat/LKCharacterStatComponent.h"
#include "LKEnemyStatComponent.generated.h"

/**
 * 
 */
UCLASS()
class LOSTKINGDOM_API ULKEnemyStatComponent : public ULKCharacterStatComponent
{
	GENERATED_BODY()
	
protected:
	virtual void SetLevelStat(int32 InNewLevel) override;
};
