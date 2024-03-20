// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Character/LKCharacterBase.h"
#include "LKPlayerCharacter.generated.h"

/**
 * 
 */
UCLASS()
class LOSTKINGDOM_API ALKPlayerCharacter : public ALKCharacterBase
{
	GENERATED_BODY()
	
public:
	ALKPlayerCharacter();

protected:
	/** Spring Arm */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class USpringArmComponent* CameraBoom;
	/** Top down camera */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class UCameraComponent* FollowCamera;

};
