// Fill out your copyright notice in the Description page of Project Settings.


#include "Info/LWInfoManager.h"
#include "Info/LWTableInfo.h"

ULWInfoManager::ULWInfoManager()
{
	const UDataTable* StaticInfoPtr = LoadObject<UDataTable>(nullptr, TEXT("/Game/GameDatas/DTL_StaticInfo.DTL_StaticInfo"));
	if (StaticInfoPtr != nullptr)
	{
		const TArray<FName>& RowNames = StaticInfoPtr->GetRowNames();
		StaticInfo.Reserve(RowNames.Num());

		for (const FName& RowName : RowNames)
		{
			if (FLWTableInfo* TableInfo = StaticInfoPtr->FindRow<FLWTableInfo>(RowName, TEXT("")))
			{
				if (UDataTable* Table = TableInfo->TablePtr.LoadSynchronous())
				{
					StaticInfo.Add(RowName, Table);
				}
			}
		}
	}

	const UDataTable* DynamicInfoPtr = LoadObject<UDataTable>(nullptr, TEXT("/Game/GameDatas/DTL_DynamicInfo.DTL_DynamicInfo"));
	if (DynamicInfoPtr != nullptr)
	{
		const TArray<FName>& RowNames = DynamicInfoPtr->GetRowNames();
		DynamicInfo.Reserve(RowNames.Num());
		DynamicInfoCache.Reserve(RowNames.Num());

		for (const FName& RowName : RowNames)
		{
			if (FLWTableInfo* TableInfo = DynamicInfoPtr->FindRow<FLWTableInfo>(RowName, TEXT("")))
			{
				DynamicInfo.Add(RowName, TableInfo->TablePtr);
			}
		}
	}
}

ULWInfoManager* ULWInfoManager::Get()
{
	if (GEngine)
	{
		return GEngine->GetEngineSubsystem<ULWInfoManager>();
	}

	return nullptr;
}

TArray<FName> ULWInfoManager::GetTableRowNames(FName TableKey)
{
	if (TObjectPtr<UDataTable>* FoundTable = StaticInfo.Find(TableKey))
	{
		return (*FoundTable)->GetRowNames();
	}

	if (TWeakObjectPtr<UDataTable>* CachedTablePtr = DynamicInfoCache.Find(TableKey))
	{
		if (CachedTablePtr->IsValid())
		{
			return CachedTablePtr->Get()->GetRowNames();
		}
	}

	if (TSoftObjectPtr<UDataTable>* FoundDynamicTable = DynamicInfo.Find(TableKey))
	{
		if (UDataTable* LoadedTable = FoundDynamicTable->LoadSynchronous())
		{
			DynamicInfoCache.Add(TableKey, LoadedTable);
			return LoadedTable->GetRowNames();
		}
	}

	return TArray<FName>();
}
