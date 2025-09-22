// Copyright Epic Games, Inc. All Rights Reserved.

#include "LostWavesGameMode.h"
#include "LostWavesCharacter.h"
#include "UObject/ConstructorHelpers.h"

ALostWavesGameMode::ALostWavesGameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdPerson/Blueprints/BP_ThirdPersonCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}
