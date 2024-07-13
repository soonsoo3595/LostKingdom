// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "LKAttackInterface.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class ULKAttackInterface : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class LOSTKINGDOM_API ILKAttackInterface
{
	GENERATED_BODY()

public:
	virtual void ProcessCombo() = 0;
	virtual void AttackComplete() = 0;
	virtual void AttackStart() = 0;
	virtual void AttackEnd() = 0;
	virtual void ComboAttackCheck() = 0;
};
