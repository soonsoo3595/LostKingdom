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
	
protected:
	virtual void PostInitProperties() override;

public:
	virtual void Use(class ALKCharacterBase* Caster);

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Skill")
	TObjectPtr<class ULKSkillData> Data;

protected:
	UPROPERTY()
	TObjectPtr<class ULKBaseBuff> Buff;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Buff")
	TSubclassOf<class ULKBaseBuff> BuffClass;

};
