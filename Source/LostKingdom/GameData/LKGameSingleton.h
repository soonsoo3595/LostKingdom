// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "LKCharacterStat.h"
#include "LKGameSingleton.generated.h"

/**
 * 
 */
UCLASS()
class LOSTKINGDOM_API ULKGameSingleton : public UObject
{
	GENERATED_BODY()
	
public:
	ULKGameSingleton();
	static ULKGameSingleton& Get();

	// Character Stat
public:
	FORCEINLINE FLKCharacterStat GetPlayerStat(int32 InLevel) const { return PlayerStatTable.IsValidIndex(InLevel - 1) ? PlayerStatTable[InLevel - 1] : FLKCharacterStat(); }
	FORCEINLINE FLKCharacterStat GetEnemyStat(int32 InLevel) const { return EnemyStatTable.IsValidIndex(InLevel - 1) ? EnemyStatTable[InLevel - 1] : FLKCharacterStat(); }

	UPROPERTY()
	int32 CharacterMaxLevel;

private:
	TArray<FLKCharacterStat> PlayerStatTable;	// 플레이어 레벨 별 스탯
	TArray<FLKCharacterStat> EnemyStatTable;	// 일반 적 레벨 별 스탯
};
