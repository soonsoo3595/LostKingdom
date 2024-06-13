// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Interface/LKAttackInterface.h"
#include "LKCharacterBase.generated.h"

UCLASS()
class LOSTKINGDOM_API ALKCharacterBase : public ACharacter, public ILKAttackInterface
{
	GENERATED_BODY()

public:
	ALKCharacterBase();

protected:
	virtual void PostInitializeComponents() override;

protected:
	UPROPERTY()
	class UAnimInstance* AnimInstance;

// Attack Section
protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Collision")
	TObjectPtr<UCapsuleComponent> WeaponComponent;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Animation")
	TObjectPtr<class UAnimMontage> AttackMontage;

	virtual void ProcessCombo() override;
	virtual void AttackStart() override;
	virtual void AttackEnd() override;
	virtual void ComboAttackCheck() override;

	UFUNCTION()
	virtual void OnAttack(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

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
	/* Input Debounce */
	FTimerHandle DebounceTimerHandle;
	uint8 bIsDebouncing : 1;
	FORCEINLINE void ResetDebounce() { bIsDebouncing = false; }
};
