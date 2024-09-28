// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "LKSpecialtyComponent.generated.h"

DECLARE_MULTICAST_DELEGATE_OneParam(FOnUpdateOrbDelegate, float);
DECLARE_MULTICAST_DELEGATE_OneParam(FOnUseSpecialtyDelegate, ESpecialtyType);

UENUM()
enum class ESpecialtyType : uint8
{
	Deactivate,
	Activate
};

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class LOSTKINGDOM_API ULKSpecialtyComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	ULKSpecialtyComponent();
	
	FOnUpdateOrbDelegate OnUpdateOrbDelegate;
	FOnUseSpecialtyDelegate OnUseSpecialtyDelegate;

	virtual void UseSpecialty(class ALKCharacterBase* Character);

protected:
	UPROPERTY()
	TObjectPtr<class ULKDeathTranceSkill> DeathTranceSkill;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Skill")
	TSubclassOf<class ULKDeathTranceSkill> DeathTranceSkillClass;

	UPROPERTY()
	TObjectPtr<class ULKBaseSkill> BurstSkill;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Skill")
	TSubclassOf<class ULKBaseSkill> BurstSkillClass;

protected:
	virtual void InitializeComponent() override;
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	void DeathTrance(class ALKCharacterBase* Character);
	void Burst(class ALKCharacterBase* Character);

public:
	void AddOrbGuage(float InGuage);
	void SubtractOrbGuage(float InGuage);
	void SetOrbGuage(float InGuage);

	FORCEINLINE bool IsFull() const { return CurrentGuage >= MaxGuage; }
	FORCEINLINE int32 GetOrbCount() const { return CurrentGuage / 100; }

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Orb")
	float CurrentGuage;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Orb")
	float MaxGuage;
	
	int32 MaxOrbCount;

	UPROPERTY()
	ESpecialtyType SpecialtyType;
};
