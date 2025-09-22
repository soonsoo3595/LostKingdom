// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/EngineSubsystem.h"
#include "Engine/DataTable.h"
#include "LWInfoManager.generated.h"
	
UCLASS()
class LOSTWAVES_API ULWInfoManager : public UEngineSubsystem
{
	GENERATED_BODY()

public:
	ULWInfoManager();

	static ULWInfoManager* Get();

	template<typename T>
	const T* GetInfo(FName TableKey, FName RowKey)
	{
		if (TObjectPtr<UDataTable>* FoundTable = StaticInfo.Find(TableKey))
		{
			return (*FoundTable)->FindRow<T>(RowKey, TEXT(""));
		}
		
		if (TWeakObjectPtr<UDataTable>* CachedTablePtr = DynamicInfoCache.Find(TableKey))
		{
			if (CachedTablePtr->IsValid())
			{
				return CachedTablePtr->Get()->FindRow<T>(RowKey, TEXT(""));
			}
		}

		if (TSoftObjectPtr<UDataTable>* FoundDynamicTable = DynamicInfo.Find(TableKey))
		{
			if (UDataTable* LoadedTable = FoundDynamicTable->LoadSynchronous())
			{
				DynamicInfoCache.Add(TableKey, LoadedTable);
				return LoadedTable->FindRow<T>(RowKey, TEXT(""));
			}
		}

		return nullptr;
	}

	TArray<FName> GetTableRowNames(FName TableKey);

private:
	UPROPERTY()
	TMap<FName, TObjectPtr<UDataTable>> StaticInfo;

	UPROPERTY()
	TMap<FName, TSoftObjectPtr<UDataTable>> DynamicInfo;	

	UPROPERTY()
    TMap<FName, TWeakObjectPtr<UDataTable>> DynamicInfoCache;
};
