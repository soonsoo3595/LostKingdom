// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UI/LKUserWidget.h"
#include "LKBuffListWidget.generated.h"

/**
 * 
 */
UCLASS()
class LOSTKINGDOM_API ULKBuffListWidget : public ULKUserWidget
{
	GENERATED_BODY()
	
public:
	void AddBuff(class ULKBaseBuff* Buff);
	void RemoveBuff(class ULKBaseBuff* Buff);

protected:
	virtual void NativeConstruct() override;

protected:
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<class UHorizontalBox> BuffList;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Buff")
	TSubclassOf<class ULKBuffWidget> BuffWidgetClass;

	UPROPERTY()
	TMap<class ULKBaseBuff*, class ULKBuffWidget*> BuffWidgets;
};
