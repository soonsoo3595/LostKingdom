// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Equipment/LKWeapon.h"
#include "LKEnemyWeapon.generated.h"

/**
 * 
 */
UCLASS()
class LOSTKINGDOM_API ALKEnemyWeapon : public ALKWeapon
{
	GENERATED_BODY()
	
public:
	virtual void Attack() override;
};
