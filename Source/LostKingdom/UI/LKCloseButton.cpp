// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/LKCloseButton.h"
#include "Components/Button.h"

void ULKCloseButton::NativeConstruct()
{
	Super::NativeConstruct();

	if (Btn)
	{
		Btn->OnClicked.AddDynamic(this, &ULKCloseButton::OnBtnClicked);
	}
}

void ULKCloseButton::OnBtnClicked()
{
	if (TargetWidget)
	{
		TargetWidget->SetVisibility(ESlateVisibility::Collapsed);
	}
}
