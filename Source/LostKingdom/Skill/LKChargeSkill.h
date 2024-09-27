// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Skill/LKBaseSkill.h"
#include "LKChargeSkill.generated.h"

/**
 * 
 */
UCLASS()
class LOSTKINGDOM_API ULKChargeSkill : public ULKBaseSkill
{
	GENERATED_BODY()
	
public:
	virtual void Use(class ALKCharacterBase* Caster) override;
	virtual void Complete() override;

protected:
	void FinishCharge();

	FTimerHandle ChargeTimer;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = true))
	float ChargeTime;
};
