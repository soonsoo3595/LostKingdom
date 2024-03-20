// Fill out your copyright notice in the Description page of Project Settings.


#include "Game/LKGameModeBase.h"
#include "Player/LKPlayerController.h"

ALKGameModeBase::ALKGameModeBase()
{
	// Set Pawn
	static ConstructorHelpers::FClassFinder<APawn> DefaultPawnClassRef(TEXT("'/Game/LostKingdom/Blueprint/BP_LKPlayerCharacter.BP_LKPlayerCharacter_C'"));
	if (DefaultPawnClassRef.Class)
	{
		DefaultPawnClass = DefaultPawnClassRef.Class;
	}

	// Set Player Controller
	static ConstructorHelpers::FClassFinder<APlayerController> PlayerControllerClassRef(TEXT("/Script/Engine.Blueprint'/Game/LostKingdom/Blueprint/BP_LKPlayerController.BP_LKPlayerController_C'"));
	if (PlayerControllerClassRef.Class)
	{
		PlayerControllerClass = PlayerControllerClassRef.Class;
	}
	// PlayerControllerClass = ALKPlayerController::StaticClass();
}
