// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/LKLoginUI.h"
#include "Components/Button.h"
#include "Components/TextBlock.h"
#include "Components/EditableText.h"
#include "Account/LKAccountManager.h"

void ULKLoginUI::NativeConstruct()
{
	Super::NativeConstruct();

	LoginBtn->OnClicked.AddDynamic(this, &ULKLoginUI::OnLoginButtonClicked);
	RegisterBtn->OnClicked.AddDynamic(this, &ULKLoginUI::OnRegisterButtonClicked);
}

void ULKLoginUI::NativeDestruct()
{
	Super::NativeDestruct();

	LoginBtn->OnClicked.RemoveDynamic(this, &ULKLoginUI::OnLoginButtonClicked);
	RegisterBtn->OnClicked.RemoveDynamic(this, &ULKLoginUI::OnRegisterButtonClicked);
}

void ULKLoginUI::OnLoginButtonClicked()
{
	const FString& ID = InputText_ID->GetText().ToString();
	const FString& PW = InputText_PW->GetText().ToString();

	if (ID.IsEmpty() || PW.IsEmpty())
	{
		SetResultText(TEXT("ID와 비밀번호를 입력하세요"));
		return;
	}

	if (ULKAccountManager* AccountManager = ULKAccountManager::Get(GetWorld()))
	{
		AccountManager->RequestLogin(ID, PW, [this](bool bSuccess, const FString& Message)
		{
			OnLoginResult(bSuccess, Message);
		});
	}
}

void ULKLoginUI::OnRegisterButtonClicked()
{
	const FString ID = InputText_ID->GetText().ToString();
	const FString PW = InputText_PW->GetText().ToString();

	if (ID.IsEmpty() || PW.IsEmpty())
	{
		SetResultText(TEXT("ID와 비밀번호를 입력하세요"));
		return;
	}

	if (ULKAccountManager* AccountManager = ULKAccountManager::Get(GetWorld()))
	{
		AccountManager->RequestRegister(ID, PW, [this](bool bSuccess, const FString& Message)
		{
			OnRegisterResult(bSuccess, Message);
		});
	}
}

void ULKLoginUI::OnLoginResult(bool bSuccess, const FString& Message)
{
	InputText_PW->SetText(FText::FromString(TEXT("")));

	SetResultText(Message);
}

void ULKLoginUI::OnRegisterResult(bool bSuccess, const FString& Message)
{
	InputText_ID->SetText(FText::FromString(TEXT("")));
	InputText_PW->SetText(FText::FromString(TEXT("")));

	SetResultText(Message);
}

void ULKLoginUI::SetResultText(const FString& Message)
{
	ResultText->SetText(FText::FromString(Message));

	FTimerHandle TimerHandle;
	GetWorld()->GetTimerManager().SetTimer(TimerHandle, [this]()
	{
		ResultText->SetText(FText::FromString(TEXT("")));
	}, 2.0f, false);
}
