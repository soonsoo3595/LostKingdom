// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UI/LKUserWidget.h"
#include "LKBaseQuickSlot.generated.h"

/**
 * 
 */
UCLASS()
class LOSTKINGDOM_API ULKBaseQuickSlot : public ULKUserWidget
{
	GENERATED_BODY()
	
public:
	ULKBaseQuickSlot(const FObjectInitializer& ObjectInitializer);

protected:
	virtual void NativeConstruct() override;

protected:
	FORCEINLINE virtual void OnKeyInput() { UseSlot(); }
	virtual void UpdateSlot();
	virtual bool UseSlot();

	virtual void SetImage();
	virtual void OnCooldownEnd();
	void SetMappedKey();

// Input
protected:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	class UInputAction* Action;

	UPROPERTY()
	FKey MappedKey;

// Component
protected:
	UPROPERTY(meta=(BindWidget))
	TObjectPtr<class UImage> Image;

	UPROPERTY(meta=(BindWidget))
	TObjectPtr<class UTextBlock> KeyText;

	UPROPERTY(meta=(BindWidget))
	TObjectPtr<class ULKRoundProgressbar> CoolDownProgressBar;

// Cool Down	
protected:
	FTimerHandle CooldownTimerHandle;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "CoolDown")
	float CooldownTime;

	uint8 bIsCoolDown : 1;
};
