// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/LKRoundProgressbar.h"
#include "Components/Image.h"
#include "Components/TextBlock.h"

void ULKRoundProgressbar::SetCoolDown(float InCoolDownTime)
{
	MaxCoolDownTime = InCoolDownTime;
	CurrentCoolDownTime = InCoolDownTime;

	if (CoolDownImage)
	{
		UMaterialInstanceDynamic* DynamicMaterial = CoolDownImage->GetDynamicMaterial();
		if (DynamicMaterial)
		{
			DynamicMaterial->SetScalarParameterValue(FName("Percent"), 1.0f);
		}
	}
}

void ULKRoundProgressbar::NativeConstruct()
{
	Super::NativeConstruct();
	SetVisibility(ESlateVisibility::Hidden);
}

void ULKRoundProgressbar::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	Super::NativeTick(MyGeometry, InDeltaTime);

	if (CurrentCoolDownTime > 0.0f)
	{
		CurrentCoolDownTime -= InDeltaTime;
		float Progress = FMath::Clamp(CurrentCoolDownTime / MaxCoolDownTime, 0.0f, 1.0f);
		
		if (CoolDownImage)
		{
			UMaterialInstanceDynamic* DynamicMaterial = CoolDownImage->GetDynamicMaterial();
			if (DynamicMaterial)
			{
				DynamicMaterial->SetScalarParameterValue(FName("Percent"), CurrentCoolDownTime / MaxCoolDownTime);
			}
		}

		// 남은 쿨타임을 초 단위로 계산하여 텍스트로 표시
		int32 RemainingTime = FMath::CeilToInt(CurrentCoolDownTime);
		FString CooldownTextString = FString::Printf(TEXT("%ds"), RemainingTime);

		if (CoolDownText)
		{
			CoolDownText->SetText(FText::FromString(CooldownTextString));
		}
	}
}
