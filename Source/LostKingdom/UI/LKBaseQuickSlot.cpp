// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/LKBaseQuickSlot.h"
#include "Blueprint/DragDropOperation.h"
#include "Components/Image.h"
#include "Components/TextBlock.h"
#include "InputMappingContext.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "Player/LKPlayerController.h"

void ULKBaseQuickSlot::NativeConstruct()
{
	Super::NativeConstruct();
	bIsEmpty = true;
	SetImage();

	if (UEnhancedInputComponent* EnhancedInputComponent = CastChecked<UEnhancedInputComponent>(GetWorld()->GetFirstPlayerController()->InputComponent))
	{
		EnhancedInputComponent->BindAction(Action, ETriggerEvent::Started, this, &ULKBaseQuickSlot::UseSlot);
	}

	SetKey();
}

bool ULKBaseQuickSlot::CanDrop(UObject* DropObject) const
{
	return false;
}

bool ULKBaseQuickSlot::NativeOnDrop(const FGeometry& InGeometry, const FDragDropEvent& InDragDropEvent, UDragDropOperation* InOperation)
{
    if (InOperation && InOperation->DefaultDragVisual && CanDrop(InOperation->Payload))
    {
        // 드랍을 처리하고, 이미지 변경 등의 작업 수행
        bIsEmpty = false;
		SetImage();
        return true;
    }
    return Super::NativeOnDrop(InGeometry, InDragDropEvent, InOperation);
}

void ULKBaseQuickSlot::SetImage()
{
	if (bIsEmpty)
	{
		Image->SetVisibility(ESlateVisibility::Hidden);
	}
	else
	{
		Image->SetVisibility(ESlateVisibility::Visible);
	}
}

void ULKBaseQuickSlot::UseSlot()
{
	UE_LOG(LogTemp, Log, TEXT("UseSlot : %s"), *MappedKey.GetDisplayName().ToString());
}

void ULKBaseQuickSlot::SetKey()
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
