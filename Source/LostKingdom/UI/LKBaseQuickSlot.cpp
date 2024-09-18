// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/LKBaseQuickSlot.h"
#include "Components/TextBlock.h"
#include "InputMappingContext.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "Player/LKPlayerController.h"
#include "UI/LKRoundProgressbar.h"

ULKBaseQuickSlot::ULKBaseQuickSlot(const FObjectInitializer& ObjectInitializer)
{
	bIsCoolDown = false;
	CooldownTime = -1.0f;
}

void ULKBaseQuickSlot::NativeConstruct()
{
	Super::NativeConstruct();

	if (UEnhancedInputComponent* EnhancedInputComponent = CastChecked<UEnhancedInputComponent>(GetWorld()->GetFirstPlayerController()->InputComponent))
	{
		EnhancedInputComponent->BindAction(Action, ETriggerEvent::Started, this, &ULKBaseQuickSlot::OnKeyInput);
	}

	SetMappedKey();
}

void ULKBaseQuickSlot::UpdateSlot()
{
}

bool ULKBaseQuickSlot::UseSlot()
{
	bIsCoolDown = true;
	GetWorld()->GetTimerManager().SetTimer(CooldownTimerHandle, this, &ULKBaseQuickSlot::OnCooldownEnd, CooldownTime, false);

	CoolDownProgressBar->SetVisibility(ESlateVisibility::Visible);
	CoolDownProgressBar->SetCoolDown(CooldownTime);

	return true;
}

void ULKBaseQuickSlot::SetImage()
{
}

void ULKBaseQuickSlot::SetMappedKey()
{
	ALKPlayerController *PlayerController = Cast<ALKPlayerController>(GetWorld()->GetFirstPlayerController());
	if (PlayerController)
	{
		const TArray<FEnhancedActionKeyMapping>& Mappings = PlayerController->DefaultMappingContext->GetMappings();

		for (const auto& Mapping : Mappings)
		{
			if (Action == Mapping.Action)
			{
				MappedKey = Mapping.Key;
				if (KeyText)
				{
					KeyText->SetText(MappedKey.GetDisplayName());
				}
			}
		}
	}
}

void ULKBaseQuickSlot::OnCooldownEnd()
{
	bIsCoolDown = false;
	CoolDownProgressBar->SetVisibility(ESlateVisibility::Hidden);
}
