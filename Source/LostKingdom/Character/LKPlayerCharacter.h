// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Character/LKCharacterBase.h"
#include "GameData/LKBattleProperty.h"
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
	virtual void AttackStart() override;
	virtual void TriggerSpecialty();

protected:
	virtual void PostInitializeComponents() override;
	void OnBattleStatChanged();

	virtual void AttackSuccess() override;

public:
	FORCEINLINE void ZoomIn() { bZoomIn = true; }
	FORCEINLINE void ZoomOut() { bZoomIn = false; }

protected:
	/** Spring Arm */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class USpringArmComponent* CameraBoom;
	/** Top down camera */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class UCameraComponent* FollowCamera;

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Specialty, Meta = (AllowPrivateAccess = "true"))
	TObjectPtr<class ULKSpecialtyComponent> Specialty;

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

	float WalkSpeed;

// UI
protected:
	virtual void SetupCharacterWidget(class ULKUserWidget* InUserWidget) override;
};
