// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/LKExpPopup.h"
#include "Components/TextBlock.h"

void ULKExpPopup::SetExpText(int32 InCurrentExp, int32 InMaxExp)
{
	if (ExpText)
	{
		ExpText->SetText(FText::FromString(FString::Printf(TEXT("%d / %d"), InCurrentExp, InMaxExp)));
	}
}
