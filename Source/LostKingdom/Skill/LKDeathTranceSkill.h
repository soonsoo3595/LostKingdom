// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Skill/LKBaseSkill.h"
#include "LKDeathTranceSkill.generated.h"

/**
 * 
 */
UCLASS()
class LOSTKINGDOM_API ULKDeathTranceSkill : public ULKBaseSkill
{
	GENERATED_BODY()

public:
	virtual void SetBuffData(int32 Index);

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<class ULKBuffData*> BuffDatas;
};
