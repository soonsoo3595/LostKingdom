// Fill out your copyright notice in the Description page of Project Settings.


#include "Game/LWLoginGameMode.h"
#include "Game/LWLoginPlayerController.h"

ALWLoginGameMode::ALWLoginGameMode()
{
	PlayerControllerClass = ALWLoginPlayerController::StaticClass();
	DefaultPawnClass = nullptr;
}
