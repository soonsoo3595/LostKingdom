// Fill out your copyright notice in the Description page of Project Settings.


#include "Game/LKLoginPlayerController.h"
#include "UI/LKLoginUI.h"
#include "Tool/LKLog.h"

void ALKLoginPlayerController::BeginPlay()
{
	LK_LOG_BEGIN();

	Super::BeginPlay();

	bShowMouseCursor = true;
	SetInputMode(FInputModeUIOnly());
	ShowLoginUI();

	LK_LOG_END();
}

void ALKLoginPlayerController::ShowLoginUI()
{
	if (LoginUIClass)
	{
		ULKLoginUI* LoginUI = CreateWidget<ULKLoginUI>(this, LoginUIClass);
		if (LoginUI)
		{
			LoginUI->AddToViewport();
		}
	}
}
