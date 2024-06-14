// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Character/LKCharacterBase.h"
#include "LKEnemyCharacter.generated.h"

/**
 * 
 */
UCLASS()
class LOSTKINGDOM_API ALKEnemyCharacter : public ALKCharacterBase
{
	GENERATED_BODY()
	
public:
	ALKEnemyCharacter();

protected:
	virtual void AttackStart() override;
};
