// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/LKLoginUI.h"
#include "Type/LKAccountType.h"
#include "Components/Button.h"
#include "Components/TextBlock.h"
#include "Components/Overlay.h"
#include "Account/LKAccountManager.h"
#include "Kismet/GameplayStatics.h"

void ULKLoginUI::NativeConstruct()
{
	Super::NativeConstruct();

	Btn_Login_Guest->OnClicked.AddDynamic(this, &ULKLoginUI::OnGuestLoginBtnClicked);
	Btn_Login_Google->OnClicked.AddDynamic(this, &ULKLoginUI::OnGoogleLoginBtnClicked);
	Btn_Logout->OnClicked.AddDynamic(this, &ULKLoginUI::OnLogoutBtnClicked);
	Btn_Start->OnClicked.AddDynamic(this, &ULKLoginUI::OnStartBtnClicked);

	if (ULKAccountManager* AccountManager = ULKAccountManager::GetInstance(GetWorld()))
	{
		AccountManager->OnLoginRequestAck.AddUObject(this, &ULKLoginUI::OnLoginRequestAck);
		AccountManager->StartOAuthListener();
		AccountManager->TryAutoLogin();
	}
}

void ULKLoginUI::NativeDestruct()
{
	Super::NativeDestruct();

	Btn_Login_Guest->OnClicked.RemoveDynamic(this, &ULKLoginUI::OnGuestLoginBtnClicked);
	Btn_Login_Google->OnClicked.RemoveDynamic(this, &ULKLoginUI::OnGoogleLoginBtnClicked);
	Btn_Logout->OnClicked.RemoveDynamic(this, &ULKLoginUI::OnLogoutBtnClicked);
	Btn_Start->OnClicked.RemoveDynamic(this, &ULKLoginUI::OnStartBtnClicked);

	if (ULKAccountManager* AccountManager = ULKAccountManager::GetInstance(GetWorld()))
	{
		AccountManager->OnLoginRequestAck.RemoveAll(this);
		AccountManager->StopOAuthListener();
	}
}

void ULKLoginUI::OnGuestLoginBtnClicked()
{
	if (ULKAccountManager* AccountManager = ULKAccountManager::GetInstance(GetWorld()))
	{
		AccountManager->RequestLogin(ELKProviderType::Guest);
	}
}

void ULKLoginUI::OnGoogleLoginBtnClicked()
{
	FString GoogleLoginURL = FString::Printf
	(TEXT("https://accounts.google.com/o/oauth2/v2/auth"
		"?client_id=%s"
		"&redirect_uri=%s"
		"&response_type=code"
		"&scope=openid%%20email%%20profile"
		"&nonce=%s"
		),
		TEXT("236303691504-l5qteodkhnivsrt8q2v00d60n1rk55mb.apps.googleusercontent.com"),
		TEXT("http://localhost:5005/oauth2callback"),
		*FGuid::NewGuid().ToString()
	);

	FPlatformProcess::LaunchURL(*GoogleLoginURL, nullptr, nullptr);
}

void ULKLoginUI::OnLogoutBtnClicked()
{
	if (ULKAccountManager* AccountManager = ULKAccountManager::GetInstance(GetWorld()))
	{
		AccountManager->RequestLogout();
	}
}

void ULKLoginUI::OnStartBtnClicked()
{
	if (ULKAccountManager* AccountManager = ULKAccountManager::GetInstance(GetWorld()))
	{
		AccountManager->ConnectToServer();
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
