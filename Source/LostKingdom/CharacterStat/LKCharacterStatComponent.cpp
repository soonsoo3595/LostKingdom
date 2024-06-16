// Fill out your copyright notice in the Description page of Project Settings.


#include "CharacterStat/LKCharacterStatComponent.h"

ULKCharacterStatComponent::ULKCharacterStatComponent()
{
	MaxHP = 200.0f;
	CurrentHP = MaxHP;

	bWantsInitializeComponent = true;
}

void ULKCharacterStatComponent::InitializeComponent()
{
	Super::InitializeComponent();

	SetHP(MaxHP);
}

float ULKCharacterStatComponent::ApplyDamage(float InDamage)
{
	const float PrevHP = CurrentHP;
	const float ActualDamage = FMath::Clamp<float>(InDamage, 0, InDamage);

	SetHP(PrevHP - ActualDamage);
	if (CurrentHP <= KINDA_SMALL_NUMBER)
	{
		OnHPZero.Broadcast();
	}

	return ActualDamage;
}

void ULKCharacterStatComponent::SetHP(float NewHP)
{
	CurrentHP = FMath::Clamp<float>(NewHP, 0, MaxHP);
	OnHPChanged.Broadcast(CurrentHP);
}

