// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/Specialty/LKSpecialtyWidget.h"
#include "UI/Specialty/LKOrbWidget.h"
#include "Interface/LKCharacterWidgetInterface.h"

void ULKSpecialtyWidget::UpdateOrbs(float InCurrentGuage)
{
	int32 OrbCount = FMath::Clamp(FMath::FloorToInt(InCurrentGuage / 100), 0, Orbs.Num());

	for(int32 i = 0; i < Orbs.Num(); i++)
	{
		if (i < OrbCount)
		{
			Orbs[i]->UpdateOrb(1.0f);
		}
		else
		{
			Orbs[i]->UpdateOrb(0.0f);
		}
	}

	if (Orbs.IsValidIndex(OrbCount))
	{
		float Percent = FMath::Fmod(InCurrentGuage, 100) / 100;
		Orbs[OrbCount]->UpdateOrb(Percent);
	}
}

void ULKSpecialtyWidget::ChangeOrbColor(ESpecialtyType SpecialType)
{
	for(int32 i = 0; i < Orbs.Num(); i++)
	{
		if (SpecialType == ESpecialtyType::Activate)
		{
			Orbs[i]->ChangeColor(ActiveColor);
		}
		else
		{
			Orbs[i]->ChangeColor(FLinearColor::White);
		}
	}
}

void ULKSpecialtyWidget::NativeOnInitialized()
{
	Super::NativeOnInitialized();

	for (int32 i = 0; i < 3; i++)
	{
		FString OrbName = FString::Printf(TEXT("Orb_%d"), i);
		ULKOrbWidget* Orb = Cast<ULKOrbWidget>(GetWidgetFromName(*OrbName));

		if (Orb)
		{
			Orbs.Add(Orb);
		}
	}
}

void ULKSpecialtyWidget::NativeConstruct()
{
	Super::NativeConstruct();

	ILKCharacterWidgetInterface* CharacterWidget = Cast<ILKCharacterWidgetInterface>(Owner);
	if (CharacterWidget)
	{
		CharacterWidget->SetupCharacterWidget(this);
	}
}
