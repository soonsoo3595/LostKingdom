// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UI/LKUIBase.h"
#include "LKLoginUI.generated.h"

class UButton;
class UTextBlock;
class UEditableText;

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
	void OnLoginButtonClicked();

	UFUNCTION()
	void OnRegisterButtonClicked();

	void OnLoginResult(bool bSuccess, const FString& Message);
	void OnRegisterResult(bool bSuccess, const FString& Message);

	void SetResultText(const FString& Message);

protected:
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UTextBlock> ResultText;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UEditableText> InputText_ID;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UEditableText> InputText_PW;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UButton> LoginBtn;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UButton> RegisterBtn;
};
