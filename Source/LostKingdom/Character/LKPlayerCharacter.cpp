// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/LKPlayerCharacter.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Components/CapsuleComponent.h"

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

void ALKPlayerCharacter::Roll()
{
	AnimInstance->Montage_Play(RollMontage);
}

void ALKPlayerCharacter::AttackStart()
{
	Super::AttackStart();
	WeaponComponent->SetCollisionProfileName(TEXT("LKPlayerAttack"));
}

