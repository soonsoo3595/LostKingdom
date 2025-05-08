// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/LKLoginUI.h"
#include "Type/LKAccountType.h"
#include "Components/Button.h"
#include "Components/TextBlock.h"
#include "Components/Overlay.h"
#include "Account/LKAccountManager.h"

void ULKLoginUI::NativeConstruct()
{
	Super::NativeConstruct();

	Btn_Login_Guest->OnClicked.AddDynamic(this, &ULKLoginUI::OnGuestLoginBtnClicked);
	Btn_Logout->OnClicked.AddDynamic(this, &ULKLoginUI::OnLogoutBtnClicked);

	if (ULKAccountManager* AccountManager = ULKAccountManager::Get(GetWorld()))
	{
		AccountManager->TryAutoLogin([this](bool bSuccess)
		{
			SetLoginPanel(bSuccess);
		});
	}
}

void ULKLoginUI::NativeDestruct()
{
	Super::NativeDestruct();

	Btn_Login_Guest->OnClicked.RemoveDynamic(this, &ULKLoginUI::OnGuestLoginBtnClicked);
	Btn_Logout->OnClicked.RemoveDynamic(this, &ULKLoginUI::OnLogoutBtnClicked);
}

void ULKLoginUI::OnGuestLoginBtnClicked()
{
	if (ULKAccountManager* AccountManager = ULKAccountManager::Get(GetWorld()))
	{
		AccountManager->RequestLogin(ELKProviderType::Guest, [this](bool bSuccess, const FString& Message)
		{
			OnLoginRequestAck(bSuccess, Message);
		});
	}
}

void ULKLoginUI::OnLogoutBtnClicked()
{
	if (ULKAccountManager* AccountManager = ULKAccountManager::Get(GetWorld()))
	{
		AccountManager->RequestLogout([this](bool bSuccess, const FString& Message)
		{
			OnLoginRequestAck(!bSuccess, Message);
		});
	}
}

void ULKLoginUI::OnLoginRequestAck(bool bSuccess, const FString& Message)
{
	SetLoginPanel(bSuccess);
}

void ULKLoginUI::SetLoginPanel(bool bIsLoggedIn)
{
	if (bIsLoggedIn)
	{
		Panel_PreLogin->SetVisibility(ESlateVisibility::Collapsed);
		Panel_PostLogin->SetVisibility(ESlateVisibility::Visible);
	}
	else
	{
		Panel_PreLogin->SetVisibility(ESlateVisibility::Visible);
		Panel_PostLogin->SetVisibility(ESlateVisibility::Collapsed);
	}
}
