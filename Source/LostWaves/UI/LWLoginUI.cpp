// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/LWLoginUI.h"
#include "Type/LWAccountType.h"
#include "Components/Button.h"
#include "Components/TextBlock.h"
#include "Components/Overlay.h"
#include "Account/LWAccountManager.h"
#include "Kismet/GameplayStatics.h"

void ULWLoginUI::NativeConstruct()
{
	Super::NativeConstruct();

	Btn_Login_Guest->OnClicked.AddDynamic(this, &ULWLoginUI::OnGuestLoginBtnClicked);
	Btn_Login_Google->OnClicked.AddDynamic(this, &ULWLoginUI::OnGoogleLoginBtnClicked);
	Btn_Logout->OnClicked.AddDynamic(this, &ULWLoginUI::OnLogoutBtnClicked);
	Btn_Start->OnClicked.AddDynamic(this, &ULWLoginUI::OnStartBtnClicked);

	if (ULWAccountManager* AccountManager = ULWAccountManager::Get(GetWorld()))
	{
		AccountManager->OnLoginRequestAck.AddUObject(this, &ULWLoginUI::OnLoginRequestAck);
		AccountManager->StartOAuthListener();
		AccountManager->TryAutoLogin();
	}
}

void ULWLoginUI::NativeDestruct()
{
	Super::NativeDestruct();

	Btn_Login_Guest->OnClicked.RemoveDynamic(this, &ULWLoginUI::OnGuestLoginBtnClicked);
	Btn_Login_Google->OnClicked.RemoveDynamic(this, &ULWLoginUI::OnGoogleLoginBtnClicked);
	Btn_Logout->OnClicked.RemoveDynamic(this, &ULWLoginUI::OnLogoutBtnClicked);
	Btn_Start->OnClicked.RemoveDynamic(this, &ULWLoginUI::OnStartBtnClicked);

	if (ULWAccountManager* AccountManager = ULWAccountManager::Get(GetWorld()))
	{
		AccountManager->OnLoginRequestAck.RemoveAll(this);
		AccountManager->StopOAuthListener();
	}
}

void ULWLoginUI::OnGuestLoginBtnClicked()
{
	if (ULWAccountManager* AccountManager = ULWAccountManager::Get(GetWorld()))
	{
		AccountManager->RequestLogin(ELWProviderType::Guest);
	}
}

void ULWLoginUI::OnGoogleLoginBtnClicked()
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

void ULWLoginUI::OnLogoutBtnClicked()
{
	if (ULWAccountManager* AccountManager = ULWAccountManager::Get(GetWorld()))
	{
		AccountManager->RequestLogout();
	}
}

void ULWLoginUI::OnStartBtnClicked()
{
	if (ULWAccountManager* AccountManager = ULWAccountManager::Get(GetWorld()))
	{
		AccountManager->ConnectToServer();
	}
}

void ULWLoginUI::OnLoginRequestAck(bool bSuccess, const FString& Message)
{
	SetLoginPanel(bSuccess);
}

void ULWLoginUI::SetLoginPanel(bool bIsLoggedIn)
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
