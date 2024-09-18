// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "LKBaseSkill.generated.h"

/**
 * 
 */
UCLASS(Blueprintable)
class LOSTKINGDOM_API ULKBaseSkill : public UObject
{
	GENERATED_BODY()
	
public:
	virtual void Use(class ALKCharacterBase* Caster);

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Skill")
	TObjectPtr<class ULKSkillData> Data;
};
