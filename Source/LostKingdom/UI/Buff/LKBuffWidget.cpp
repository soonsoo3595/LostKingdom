// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/Buff/LKBuffWidget.h"
#include "Components/Image.h"
#include "Components/TextBlock.h"
#include "Buff/LKBaseBuff.h"
#include "Buff/LKBuffData.h"


ULKBuffWidget::ULKBuffWidget(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
	BuffRemainingTime = -1.0f;
}

void ULKBuffWidget::SetBuffWidget(ULKBaseBuff* InBuff)
{
	if (InBuff)
	{
		Buff = InBuff;
		DisplayBuffIcon();
		UpdateTime();
	}
}

void ULKBuffWidget::UpdateTime()
{
	if (Buff)
	{
		BuffRemainingTime = Buff->GetData()->BuffDuration;
	}
}

void ULKBuffWidget::DisplayBuffIcon()
{
	if (Buff)
	{
		BuffIcon->SetBrushFromTexture(Buff->GetData()->BuffIcon);
	}
}

void ULKBuffWidget::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	Super::NativeTick(MyGeometry, InDeltaTime);

	if (Buff)
	{
		if (BuffRemainingTime > 0.0f)
		{
			BuffRemainingTime -= InDeltaTime;

			int32 RemainingTime = FMath::CeilToInt(BuffRemainingTime);
			FString BuffRemainTextString = FString::Printf(TEXT("%d초"), RemainingTime);

			BuffDuration->SetText(FText::FromString(BuffRemainTextString));
		}
	}
}
