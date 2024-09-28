// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Buff/LKBaseBuff.h"
#include "LKDeathTranceBuff.generated.h"

/**
 * 
 */
UCLASS()
class LOSTKINGDOM_API ULKDeathTranceBuff : public ULKBaseBuff
{
	GENERATED_BODY()
	
public:
	virtual void OnBuffStart(class ALKCharacterBase* InTarget) override;
	virtual void OnBuffEnd() override;
};
