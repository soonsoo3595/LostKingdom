// Fill out your copyright notice in the Description page of Project Settings.


#include "Game/LKLoginGameMode.h"
#include "Game/LKLoginPlayerController.h"

ALKLoginGameMode::ALKLoginGameMode()
{
	PlayerControllerClass = ALKLoginPlayerController::StaticClass();
	DefaultPawnClass = nullptr;
}
