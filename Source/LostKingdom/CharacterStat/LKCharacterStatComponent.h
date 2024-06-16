// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "LKCharacterStatComponent.generated.h"

DECLARE_MULTICAST_DELEGATE(FOnHPZeroDelegate);
DECLARE_MULTICAST_DELEGATE_OneParam(FOnHPChangedDelegate, float /*CurrentHp*/);

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class LOSTKINGDOM_API ULKCharacterStatComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	ULKCharacterStatComponent();

protected:
	virtual void InitializeComponent() override;

public:
	FOnHPZeroDelegate OnHPZero;
	FOnHPChangedDelegate OnHPChanged;

	FORCEINLINE float GetMaxHp() { return MaxHP; }
	FORCEINLINE float GetCurrentHp() { return CurrentHP; }
	FORCEINLINE FText GetCharacterName() { return CharacterName; }
	float ApplyDamage(float InDamage);

protected:
	void SetHP(float NewHP);

	UPROPERTY(Transient, VisibleInstanceOnly, Category = Stat)
	float CurrentHP;

	UPROPERTY(Transient, VisibleInstanceOnly, Category = Stat)
	float MaxHP;

	UPROPERTY(Transient, EditAnywhere, Category = Info)
	FText CharacterName;
};
