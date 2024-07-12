// Fill out your copyright notice in the Description page of Project Settings.


#include "GameData/LKGameSingleton.h"

ULKGameSingleton::ULKGameSingleton()
{
	static ConstructorHelpers::FObjectFinder<UDataTable> EnemyDataTableRef(TEXT("/Script/Engine.DataTable'/Game/LostKingdom/GameData/LKEnemyStatTable.LKEnemyStatTable'"));
	if (nullptr != EnemyDataTableRef.Object)
	{
		const UDataTable* DataTable = EnemyDataTableRef.Object;
		check(DataTable->GetRowMap().Num() > 0);

		TArray<uint8*> ValueArray;
		DataTable->GetRowMap().GenerateValueArray(ValueArray);
		Algo::Transform(ValueArray, EnemyStatTable,
			[](uint8* Value)
			{
				return *reinterpret_cast<FLKCharacterStat*>(Value);
			}
		);
	}

	static ConstructorHelpers::FObjectFinder<UDataTable> PlayerDataTableRef(TEXT("/Script/Engine.DataTable'/Game/LostKingdom/GameData/LKPlayerStatTable.LKPlayerStatTable'"));
	if (nullptr != PlayerDataTableRef.Object)
	{
		const UDataTable* DataTable = PlayerDataTableRef.Object;
		check(DataTable->GetRowMap().Num() > 0);

		TArray<uint8*> ValueArray;
		DataTable->GetRowMap().GenerateValueArray(ValueArray);
		Algo::Transform(ValueArray, PlayerStatTable,
			[](uint8* Value)
			{
				return *reinterpret_cast<FLKCharacterStat*>(Value);
			}
		);
	}
	CharacterMaxLevel = PlayerStatTable.Num();
	ensure(CharacterMaxLevel > 0);
}

ULKGameSingleton& ULKGameSingleton::Get()
{
	ULKGameSingleton* Singleton = CastChecked<ULKGameSingleton>(GEngine->GameSingleton);
	if (Singleton)
	{
		return *Singleton;
	}

	return *NewObject<ULKGameSingleton>();
}