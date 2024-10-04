// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Equipment/LKWeapon.h"
#include "LKPlayerWeapon.generated.h"

/**
 * 
 */
UCLASS()
class LOSTKINGDOM_API ALKPlayerWeapon : public ALKWeapon
{
	GENERATED_BODY()
	
public:
	virtual void Attack() override;
};
