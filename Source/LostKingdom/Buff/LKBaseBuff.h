// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "GameData/LKCharacterStat.h"
#include "LKBaseBuff.generated.h"

/**
 * 
 */
UCLASS(Blueprintable)
class LOSTKINGDOM_API ULKBaseBuff : public UObject
{
	GENERATED_BODY()
	
public:
	ULKBaseBuff();

	virtual void OnBuffStart(class ALKCharacterBase* InTarget);
	virtual void OnBuffEnd();
	virtual void OnBuffReset();

	FORCEINLINE class ULKBuffData* GetData() const { return Data; }

protected:
	UPROPERTY()
	TObjectPtr<class ALKCharacterBase> Target;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Buff")
	TObjectPtr<class ULKBuffData> Data;

	FTimerHandle BuffTimerHandle;

	UPROPERTY(Transient, VisibleInstanceOnly, Category = "Stat", Meta = (AllowPrivateAccess = true))
	FLKCharacterStat BuffStat;
};
