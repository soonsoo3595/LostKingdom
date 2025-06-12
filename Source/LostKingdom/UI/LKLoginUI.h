// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UI/LKUIBase.h"
#include "LKLoginUI.generated.h"

class UButton;
class UTextBlock;
class UOverlay;

/**
 * 
 */
UCLASS()
class LOSTKINGDOM_API ULKLoginUI : public ULKUIBase
{
	GENERATED_BODY()
	
protected:
	virtual void NativeConstruct() override;
	virtual void NativeDestruct() override;

protected:
	UFUNCTION()
	void OnGuestLoginBtnClicked();

	UFUNCTION()
	void OnGoogleLoginBtnClicked();

	UFUNCTION()
	void OnLogoutBtnClicked();

	UFUNCTION()
	void OnStartBtnClicked();

	void OnLoginRequestAck(bool bSuccess, const FString& Message);

	void SetLoginPanel(bool bIsLoggedIn);

protected:
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UOverlay> Panel_PreLogin;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UOverlay> Panel_PostLogin;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UButton> Btn_Login_Guest;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UButton> Btn_Login_Google;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UButton> Btn_Start;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UButton> Btn_Logout;
};
