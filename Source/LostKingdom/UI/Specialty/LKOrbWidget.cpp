// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/Specialty/LKOrbWidget.h"
#include "Components/ProgressBar.h"

void ULKOrbWidget::UpdateOrb(float InPercent)
{
	if (Guage)
	{
		Guage->SetPercent(InPercent);
	}
}

void ULKOrbWidget::ChangeColor(FLinearColor NewColor)
{
	if (Guage)
	{
		Guage->SetFillColorAndOpacity(NewColor);
	}
}
