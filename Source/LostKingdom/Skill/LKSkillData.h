// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "LKSkillData.generated.h"

/**
 * 
 */
UCLASS()
class LOSTKINGDOM_API ULKSkillData : public UPrimaryDataAsset
{
	GENERATED_BODY()
	
public:
    // 스킬의 이름
    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Skill")
    FName SkillName;

    // 스킬의 아이콘 이미지
    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Skill")
    UTexture2D* SkillIcon;

    // 스킬 사용 시 플레이할 애니메이션 몽타주
    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Skill")
    UAnimMontage* SkillMontage;

    // 스킬을 찍는데 필요한 레벨
    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Skill")
    int32 RequiredLevel;

    // 스킬의 데미지 계수
    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Skill")
    float SkillCoefficient;

    // 스킬의 쿨타임
    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Skill")
    float CooldownTime;

    // 스킬 시전 중 취소할 수 있는지
    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Skill")
    bool bCanCancel;
};
