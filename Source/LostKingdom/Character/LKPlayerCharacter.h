// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Character/LKCharacterBase.h"
#include "GameData/LKBattleStat.h"
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

	virtual void Tick(float DeltaTime) override;

protected:
	virtual void PostInitializeComponents() override;
	virtual void AttackStart() override;

	void OnBattleStatChanged(const FLKBattleStat& InBattleStat);

public:
	FORCEINLINE void ZoomIn() { bZoomIn = true; }
	FORCEINLINE void ZoomOut() { bZoomIn = false; }

	void Roll();

protected:
	/** Spring Arm */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class USpringArmComponent* CameraBoom;
	/** Top down camera */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class UCameraComponent* FollowCamera;

	// Montage
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Animation")
	TObjectPtr<UAnimMontage> RollMontage;

private:
	uint8 bZoomIn : 1;

	UPROPERTY(EditAnywhere, Category = Camera, meta = (AllowPrivate))
	float ZoomInArmLength;
	UPROPERTY(EditAnywhere, Category = Camera, meta = (AllowPrivate))
	float ZoomOutArmLength;

	UPROPERTY(EditAnywhere, Category = Camera, meta = (AllowPrivate))
	FRotator ZoomInRotation;
	UPROPERTY(EditAnywhere, Category = Camera, meta = (AllowPrivate))
	FRotator ZoomOutRotation;
};
