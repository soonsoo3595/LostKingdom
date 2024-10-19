// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "LKItem.generated.h"

UCLASS()
class LOSTKINGDOM_API ALKItem : public AActor
{
	GENERATED_BODY()
	
public:	
	ALKItem();

	virtual class ULKItemData* GetItemData() const { return ItemData; }

protected:

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item")
	TObjectPtr<class ULKItemData> ItemData;
};
