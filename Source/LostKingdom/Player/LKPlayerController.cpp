// Fill out your copyright notice in the Description page of Project Settings.


#include "Player/LKPlayerController.h"
#include "Blueprint/AIBlueprintHelperLibrary.h"
#include "NiagaraSystem.h"
#include "NiagaraFunctionLibrary.h"
#include "Engine/World.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "Character/LKPlayerCharacter.h"

ALKPlayerController::ALKPlayerController()
{
	bShowMouseCursor = true;

	Destination = FVector::ZeroVector;
	bZooming = false;
	bCanRoll = true;
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
		EnhancedInputComponent->BindAction(ZoomAction, ETriggerEvent::Triggered, this, &ALKPlayerController::OnZoomTriggered);
		EnhancedInputComponent->BindAction(RollAction, ETriggerEvent::Started, this, &ALKPlayerController::OnRollTriggered);
	}
}

void ALKPlayerController::OnInputStarted()
{

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

void ALKPlayerController::OnZoomTriggered(const FInputActionValue& Value)
{
	float AxisValue = Value.Get<float>();

	if (AxisValue > 0.0f && !bZooming)
	{
		OnZoomIn();
	}
	else if (AxisValue < 0.0f && bZooming)
	{
		OnZoomOut();
	}
}


void ALKPlayerController::OnZoomIn()
{
	bZooming = true;

	ALKPlayerCharacter* PlayerCharacter = CastChecked<ALKPlayerCharacter>(GetPawn());

	if (PlayerCharacter)
	{
		UE_LOG(LogTemp, Log, TEXT("Zoom In"));
		PlayerCharacter->ZoomIn();
	}
}

void ALKPlayerController::OnZoomOut()
{
	bZooming = false;

	ALKPlayerCharacter* PlayerCharacter = CastChecked<ALKPlayerCharacter>(GetPawn());

	if (PlayerCharacter)
	{
		UE_LOG(LogTemp, Log, TEXT("Zoom Out"));
		PlayerCharacter->ZoomOut();
	}
}

void ALKPlayerController::OnRollTriggered(const FInputActionValue& Value)
{
	if(!bCanRoll)
	{
		return;
	}

	bCanRoll = false;

	ALKPlayerCharacter* PlayerCharacter = CastChecked<ALKPlayerCharacter>(GetPawn());
	if(PlayerCharacter)
	{
		UE_LOG(LogTemp, Log, TEXT("Roll"));
		PlayerCharacter->Roll();
	}

	GetWorld()->GetTimerManager().SetTimer(CooldownTimerHandle, this, &ALKPlayerController::OnRollCooldownCompleted, RollCooldownTime, false);
}

void ALKPlayerController::OnRollCooldownCompleted()
{
	UE_LOG(LogTemp, Log, TEXT("Roll Cooldown Completed"));
	bCanRoll = true;
}
