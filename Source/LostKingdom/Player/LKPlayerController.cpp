// Fill out your copyright notice in the Description page of Project Settings.


#include "Player/LKPlayerController.h"
#include "Blueprint/AIBlueprintHelperLibrary.h"
#include "NiagaraSystem.h"
#include "NiagaraFunctionLibrary.h"
#include "Engine/World.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"

ALKPlayerController::ALKPlayerController()
{
	bShowMouseCursor = true;
	Destination = FVector::ZeroVector;
}

void ALKPlayerController::BeginPlay()
{
	Super::BeginPlay();

	if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer()))
	{
		Subsystem->AddMappingContext(DefaultMappingContext, 0);
	}
}

void ALKPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();

	if (UEnhancedInputComponent* EnhancedInputComponent = CastChecked<UEnhancedInputComponent>(InputComponent))
	{
		// Setup mouse input events
		EnhancedInputComponent->BindAction(SetDestinationClickAction, ETriggerEvent::Started, this, &ALKPlayerController::OnInputStarted);
		EnhancedInputComponent->BindAction(SetDestinationClickAction, ETriggerEvent::Triggered, this, &ALKPlayerController::OnSetDestinationTriggered);
		EnhancedInputComponent->BindAction(SetDestinationClickAction, ETriggerEvent::Completed, this, &ALKPlayerController::OnSetDestinationReleased);
		EnhancedInputComponent->BindAction(SetDestinationClickAction, ETriggerEvent::Canceled, this, &ALKPlayerController::OnSetDestinationReleased);
	}
}

void ALKPlayerController::OnInputStarted()
{
	StopMovement();
}

void ALKPlayerController::OnSetDestinationTriggered()
{
	FHitResult Hit;
	bool bHitSuccessful = false;

	bHitSuccessful = GetHitResultUnderCursor(ECollisionChannel::ECC_Visibility, true, Hit);

	if (bHitSuccessful)
	{
		Destination = Hit.Location;
	}

	UAIBlueprintHelperLibrary::SimpleMoveToLocation(this, Destination);
}

void ALKPlayerController::OnSetDestinationReleased()
{
	UAIBlueprintHelperLibrary::SimpleMoveToLocation(this, Destination);
	UNiagaraFunctionLibrary::SpawnSystemAtLocation(this, FXCursor, Destination, FRotator::ZeroRotator, FVector(1.f, 1.f, 1.f), true, true, ENCPoolMethod::None, true);
}
