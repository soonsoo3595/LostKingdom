// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Buff/LKBaseBuff.h"
#include "LKPowerBuff.generated.h"

/**
 * 
 */
UCLASS()
class LOSTKINGDOM_API ULKPowerBuff : public ULKBaseBuff
{
	GENERATED_BODY()
	
protected:
	virtual void OnBuffStart(class ALKCharacterBase* InTarget) override;
	virtual void OnBuffEnd() override;
};
