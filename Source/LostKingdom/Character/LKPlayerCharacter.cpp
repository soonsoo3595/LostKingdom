// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/LKPlayerCharacter.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "CharacterStat/LKCharacterStatComponent.h"
#include "UI/LKExpWidget.h"
#include "Specialty/LKSpecialtyComponent.h"
#include "UI/Specialty/LKSpecialtyWidget.h"

ALKPlayerCharacter::ALKPlayerCharacter()
{
	PrimaryActorTick.bCanEverTick = true;

	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(RootComponent);
	CameraBoom->SetUsingAbsoluteRotation(true);
	CameraBoom->TargetArmLength = 800.f;
	CameraBoom->SetRelativeRotation(FRotator(-60.f, 0.f, 0.f));
	CameraBoom->bDoCollisionTest = false; 

	FollowCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("TopDownCamera"));
	FollowCamera->SetupAttachment(CameraBoom, USpringArmComponent::SocketName);
	FollowCamera->bUsePawnControlRotation = false; // Camera does not rotate relative to arm

	Specialty = CreateDefaultSubobject<ULKSpecialtyComponent>(TEXT("Specialty"));
	bZoomIn = false;
}

void ALKPlayerCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (bZoomIn)
	{
		CameraBoom->TargetArmLength = FMath::FInterpTo(CameraBoom->TargetArmLength, ZoomInArmLength, DeltaTime, 5.f);
		CameraBoom->SetRelativeRotation(FMath::RInterpTo(CameraBoom->GetRelativeRotation(), ZoomInRotation, DeltaTime, 5.f));
	}
	else
	{
		CameraBoom->TargetArmLength = FMath::FInterpTo(CameraBoom->TargetArmLength, ZoomOutArmLength, DeltaTime, 5.f);
		CameraBoom->SetRelativeRotation(FMath::RInterpTo(CameraBoom->GetRelativeRotation(), ZoomOutRotation, DeltaTime, 5.f));
	}
}

void ALKPlayerCharacter::PostInitializeComponents()
{
	Super::PostInitializeComponents();

	WalkSpeed = GetCharacterMovement()->MaxWalkSpeed;

	if (Stat)
	{
		Stat->OnBattleStatChanged.AddUObject(this, &ALKPlayerCharacter::OnBattleStatChanged);
	}
}

void ALKPlayerCharacter::TriggerSpecialty()
{
	if (Specialty && bUseSkill == false)
	{
		Specialty->UseSpecialty(this);
	}
}

void ALKPlayerCharacter::OnBattleStatChanged()
{
	// Speed Setting
	float NewWalkSpeed = WalkSpeed * Stat->GetSpeed();
	GetCharacterMovement()->MaxWalkSpeed = NewWalkSpeed;
}

void ALKPlayerCharacter::AttackSuccess()
{
	if (Specialty)
	{
		float Guage = 5 * (1 + Stat->GetFinalBattleStat().SpecialPercent);
		Specialty->AddOrbGuage(Guage);
	}
}

void ALKPlayerCharacter::SetupCharacterWidget(ULKUserWidget* InUserWidget)
{
	Super::SetupCharacterWidget(InUserWidget);

	ULKExpWidget* ExpWidget = Cast<ULKExpWidget>(InUserWidget);
	if (ExpWidget)
	{
		ExpWidget->UpdateExpGuage(Stat->GetCurrentExp(), Stat->GetBaseStat().Exp);
		ExpWidget->UpdateExpLevel(Stat->GetCurrentLevel());

		Stat->OnExpChanged.AddUObject(ExpWidget, &ULKExpWidget::UpdateExpGuage);
		Stat->OnLevelUp.AddUObject(ExpWidget, &ULKExpWidget::UpdateExpLevel);
	}

	ULKSpecialtyWidget* SpecialtyWidget = Cast<ULKSpecialtyWidget>(InUserWidget);
	if (SpecialtyWidget)
	{
		Specialty->OnUpdateOrbDelegate.AddUObject(SpecialtyWidget, &ULKSpecialtyWidget::UpdateOrbs);
		Specialty->OnUseSpecialtyDelegate.AddUObject(SpecialtyWidget, &ULKSpecialtyWidget::ChangeOrbColor);
	}
}
