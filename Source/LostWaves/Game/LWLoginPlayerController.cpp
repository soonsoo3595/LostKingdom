// Fill out your copyright notice in the Description page of Project Settings.


#include "Game/LWLoginPlayerController.h"
#include "UI/LWLoginUI.h"
#include "LostWaves.h"

void ALWLoginPlayerController::BeginPlay()
{
	LW_LOG_BEGIN();

	Super::BeginPlay();

	if (IsLocalPlayerController())
	{
		bShowMouseCursor = true;
		ShowLoginUI();
	}

	LW_LOG_END();
}

void ALWLoginPlayerController::ShowLoginUI()
{
	if (LoginUIClass)
	{
		ULWLoginUI* LoginUI = CreateWidget<ULWLoginUI>(this, LoginUIClass);
		if (LoginUI)
		{
			LoginUI->AddToViewport();
		}
	}
}
