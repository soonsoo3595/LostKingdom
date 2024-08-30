// Fill out your copyright notice in the Description page of Project Settings.
#include "UI/LKMainHUD.h"
#include "Components/TextBlock.h"
#include "Character/LKPlayerCharacter.h"
#include "UI/LKExpWidget.h"

void ULKMainHUD::NativeOnInitialized()
{
    Super::NativeOnInitialized();

    ALKPlayerCharacter* PlayerCharacter = Cast<ALKPlayerCharacter>(GetOwningPlayerPawn());
    if (PlayerCharacter)
    {
        ExpWidget->SetOwner(PlayerCharacter);
    }
}

void ULKMainHUD::NativeConstruct()
{
	Super::NativeConstruct();

	UpdateTime();
}

void ULKMainHUD::UpdateTime()
{
    // 현재 시간을 얻어오기
    FDateTime Now = FDateTime::Now();
    FString TimeString = Now.ToString(TEXT("%H:%M"));

    // 텍스트 블록에 시간 설정
    if (Time)
    {
        Time->SetText(FText::FromString(TimeString));
    }

    GetWorld()->GetTimerManager().SetTimerForNextTick(FTimerDelegate::CreateUObject(this, &ULKMainHUD::UpdateTime));
}
