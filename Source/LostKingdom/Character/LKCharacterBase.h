// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Interface/LKAttackInterface.h"
#include "Interface/LKCharacterWidgetInterface.h"
#include "Interface/LKDamageInterface.h"
#include "Buff/LKBaseBuff.h"
#include "LKCharacterBase.generated.h"

DECLARE_MULTICAST_DELEGATE_OneParam(FOnBuffAddedDelegate, ULKBaseBuff*);
DECLARE_MULTICAST_DELEGATE_OneParam(FOnBuffRemovedDelegate, ULKBaseBuff*);

UCLASS()
class LOSTKINGDOM_API ALKCharacterBase : public ACharacter, public ILKAttackInterface, public ILKCharacterWidgetInterface, public ILKDamageInterface
{
	GENERATED_BODY()

public:
	ALKCharacterBase();

	FORCEINLINE UAnimInstance* GetAnimInstance() const { return AnimInstance; }

protected:
	virtual void PostInitializeComponents() override;
	virtual void BeginPlay() override;

protected:
	UPROPERTY()
	class UAnimInstance* AnimInstance;

// Equip Section
public:
	virtual void EquipWeapon();

protected:
	UPROPERTY()
	TObjectPtr<class ALKWeapon> Weapon;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Equipement")
	TSubclassOf<class ALKWeapon> WeaponClass;

// Attack Section
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Animation")
	TObjectPtr<class UAnimMontage> AttackMontage;

public:
	virtual void ProcessCombo() override;
	FORCEINLINE virtual void AttackComplete() override { HasNextComboInput = false; }
	virtual void AttackStart() override;
	virtual void AttackEnd() override;
	virtual void AttackSuccess();
	FORCEINLINE virtual void ComboAttackCheck() override { ComboCheck(); }

	virtual bool OnDamaged(AActor* DamageCauser, float Damage) override;

protected:
	void ComboAttackBegin();
	void ComboAttackEnd(class UAnimMontage* TargetMontage, bool IsProperlyEnded);

	// 노티파이 이벤트가 호출되면 입력이 들어왔는지 확인 후 다음 콤보 액션을 실행
	void ComboCheck();

	void LookAt();

	int32 MaxCombo = 4;
	int32 CurrentCombo = 0;

	// 노티파이 이전에 입력이 들어왔는지
	bool HasNextComboInput = false;

// Skill Section
public:
	virtual bool UseSkill(class ULKBaseSkill* Skill);
	virtual void OnSkillEnd(class UAnimMontage* TargetMontage, bool IsProperlyEnded);

protected:
	uint8 bUseSkill : 1;	// Check if the skill is being used

// Buff Section
public:
	FOnBuffAddedDelegate OnBuffAdded;
	FOnBuffRemovedDelegate OnBuffRemoved;

	virtual void AddBuff(class ULKBaseBuff* Buff);
	virtual void RemoveBuff(class ULKBaseBuff* Buff);

protected:
	UPROPERTY()
	TSet<class ULKBaseBuff*> ActiveBuffs;
	
// Dead Section
protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Animation")
	TObjectPtr<UAnimMontage> DeadMontage;

	virtual void SetDead();

	void PlayDeadAnimation();
	uint8 bIsDead : 1;

// Stat Section
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Stat, Meta = (AllowPrivateAccess = "true"))
	TObjectPtr<class ULKCharacterStatComponent> Stat;

// UI Widget Section
protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Widget, Meta = (AllowPrivateAccess = "true"))
	TObjectPtr<class ULKWidgetComponent> HUD;
 
	virtual void SetupCharacterWidget(class ULKUserWidget* InUserWidget) override;

};
