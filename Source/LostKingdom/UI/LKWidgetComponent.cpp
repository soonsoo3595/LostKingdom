// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/LKWidgetComponent.h"
#include "UI/LKUserWidget.h"

void ULKWidgetComponent::InitWidget()
{
	Super::InitWidget();

	ULKUserWidget* UserWidget = Cast<ULKUserWidget>(GetWidget());
	if (UserWidget)
	{
		UserWidget->SetOwner(GetOwner());
	}
}
