// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "LKRoundProgressbar.generated.h"

/**
 * 
 */
UCLASS()
class LOSTKINGDOM_API ULKRoundProgressbar : public UUserWidget
{
	GENERATED_BODY()
	
public:
	void SetCoolDown(float InCoolDownTime);

protected:
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<class UImage> CoolDownImage;
	
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<class UTextBlock> CoolDownText;

	virtual void NativeConstruct() override;
	virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime) override;

private:
	float MaxCoolDownTime;
	float CurrentCoolDownTime;
};
