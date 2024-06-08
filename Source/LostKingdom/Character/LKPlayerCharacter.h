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

	virtual void PostInitializeComponents() override;
	virtual void Tick(float DeltaTime) override;

public:
	FORCEINLINE void ZoomIn() { bZoomIn = true; }
	FORCEINLINE void ZoomOut() { bZoomIn = false; }

	void Roll();

	void ProcessCombo();
	void NotifyCombo();

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

// Attack Section
protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Animation")
	TObjectPtr<class UAnimMontage> ComboAttackMontage;
	
	void ComboAttackBegin();
	void ComboAttackEnd(class UAnimMontage* TargetMontage, bool IsProperlyEnded);

	// 노티파이 이벤트가 호출되면 입력이 들어왔는지 확인 후 다음 콤보 액션을 실행
	void ComboCheck();

	void LookAt();

	int32 MaxCombo = 4;
	int32 CurrentCombo = 0;

	// 노티파이 이전에 입력이 들어왔는지
	bool HasNextComboInput = false;

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

	UPROPERTY()
	class UAnimInstance* AnimInstance;

	/* Input Debounce */
	FTimerHandle DebounceTimerHandle;
	uint8 bIsDebouncing : 1;
	FORCEINLINE void ResetDebounce() { bIsDebouncing = false; }
};
