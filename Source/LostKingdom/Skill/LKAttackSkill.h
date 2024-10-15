// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Skill/LKBaseSkill.h"
#include "LKAttackSkill.generated.h"

/**
 * 
 */
UCLASS()
class LOSTKINGDOM_API ULKAttackSkill : public ULKBaseSkill
{
	GENERATED_BODY()
	
protected:
	virtual void Attack(class ALKCharacterBase* Caster) override;

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Attack")
	float AttackRange;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Attack")
	float AttackRadius;
};
