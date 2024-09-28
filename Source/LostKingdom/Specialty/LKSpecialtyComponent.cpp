// Fill out your copyright notice in the Description page of Project Settings.


#include "Specialty/LKSpecialtyComponent.h"
#include "Skill/LKBaseSkill.h"
#include "Skill/LKDeathTranceSkill.h"
#include "Character/LKCharacterBase.h"

ULKSpecialtyComponent::ULKSpecialtyComponent()
{
	MaxOrbCount = 3;

	CurrentGuage = 0.0f;
	MaxGuage = 100.0f * MaxOrbCount;

	SpecialtyType = ESpecialtyType::Deactivate;

	bWantsInitializeComponent = true;
	PrimaryComponentTick.bCanEverTick = true;
}

void ULKSpecialtyComponent::UseSpecialty(ALKCharacterBase* Character)
{
	switch (SpecialtyType)
	{
		case ESpecialtyType::Deactivate:
			DeathTrance(Character);
			break;
		case ESpecialtyType::Activate:
			Burst(Character);
			break;
	}
}

void ULKSpecialtyComponent::InitializeComponent()
{
	Super::InitializeComponent();

	if (DeathTranceSkillClass)
	{
		DeathTranceSkill = NewObject<ULKDeathTranceSkill>(this, DeathTranceSkillClass);
	}

	if(BurstSkillClass)
	{
		BurstSkill = NewObject<ULKBaseSkill>(this, BurstSkillClass);
	}

	SetOrbGuage(0.0f);
}

void ULKSpecialtyComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if(SpecialtyType == ESpecialtyType::Activate)
	{
		SubtractOrbGuage(10.0f * DeltaTime);
	}
}

void ULKSpecialtyComponent::DeathTrance(ALKCharacterBase* Character)
{
	if (GetOrbCount() < 1) return;

	SpecialtyType = ESpecialtyType::Activate;
	OnUseSpecialtyDelegate.Broadcast(SpecialtyType);

	if (DeathTranceSkill)
	{
		DeathTranceSkill->SetBuffData(GetOrbCount());
		Character->UseSkill(DeathTranceSkill);
	}
}

void ULKSpecialtyComponent::Burst(ALKCharacterBase* Character)
{
	SpecialtyType = ESpecialtyType::Deactivate;
	SetOrbGuage(0.0f);
	OnUseSpecialtyDelegate.Broadcast(SpecialtyType);

	if(BurstSkill)
	{	
		Character->UseSkill(BurstSkill);
	}
}

void ULKSpecialtyComponent::AddOrbGuage(float InGuage)
{
	if (IsFull() || SpecialtyType == ESpecialtyType::Activate) return;

	CurrentGuage = FMath::Clamp(CurrentGuage + InGuage, 0.0f, MaxGuage);
	OnUpdateOrbDelegate.Broadcast(CurrentGuage);
}

void ULKSpecialtyComponent::SubtractOrbGuage(float InGuage)
{
	if (CurrentGuage < KINDA_SMALL_NUMBER)
	{
		SpecialtyType = ESpecialtyType::Deactivate;
		OnUseSpecialtyDelegate.Broadcast(SpecialtyType);
		return;
	}

	CurrentGuage = FMath::Clamp(CurrentGuage - InGuage, 0.0f, MaxGuage);
	OnUpdateOrbDelegate.Broadcast(CurrentGuage);
}

void ULKSpecialtyComponent::SetOrbGuage(float InGuage)
{
	CurrentGuage = FMath::Clamp(InGuage, 0.0f, MaxGuage);
	OnUpdateOrbDelegate.Broadcast(CurrentGuage);
}



