// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "LKItemData.generated.h"

/**
 * 
 */
UCLASS()
class LOSTKINGDOM_API ULKItemData : public UPrimaryDataAsset
{
	GENERATED_BODY()
	
public:
    // 아이템 이름
    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Item")
    FName ItemName;

    // 아이템 아이콘 이미지
    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Item")
    UTexture2D* ItemIcon;

    // 아이템 설명
    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Item")
    FText ItemDescription;

};
