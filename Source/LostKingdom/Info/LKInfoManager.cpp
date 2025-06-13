// Fill out your copyright notice in the Description page of Project Settings.


#include "Info/LKInfoManager.h"
#include "Info/LKTableInfo.h"

ULKInfoManager::ULKInfoManager()
{
	/*const UDataTable* StaticInfoPtr = LoadObject<UDataTable>(nullptr, TEXT("/Game/GameDatas/DTL_StaticInfo.DTL_StaticInfo"));
	if (StaticInfoPtr != nullptr)
	{
		const TArray<FName>& RowNames = StaticInfoPtr->GetRowNames();
		StaticInfo.Reserve(RowNames.Num());

		for (const FName& RowName : RowNames)
		{
			if (FLKTableInfo* TableInfo = StaticInfoPtr->FindRow<FLKTableInfo>(RowName, TEXT("")))
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

		for (const FName& RowName : RowNames)
		{
			if (FLKTableInfo* TableInfo = DynamicInfoPtr->FindRow<FLKTableInfo>(RowName, TEXT("")))
			{
				DynamicInfo.Add(RowName, TableInfo->TablePtr);
			}
		}
	}*/
}

ULKInfoManager* ULKInfoManager::GetInstance()
{
	if (GEngine)
	{
		return GEngine->GetEngineSubsystem<ULKInfoManager>();
	}

	return nullptr;
}

TArray<FName> ULKInfoManager::GetTableRowNames(FName TableKey)
{
	if (TObjectPtr<UDataTable>* FoundTable = StaticInfo.Find(TableKey))
	{
		return (*FoundTable)->GetRowNames();
	}
	else if (TSoftObjectPtr<UDataTable>* FoundDynamicTable = DynamicInfo.Find(TableKey))
	{
		if (UDataTable* LoadedTable = FoundDynamicTable->Get())
		{
			return LoadedTable->GetRowNames();
		}
		else
		{
			LoadedTable = FoundDynamicTable->LoadSynchronous();
			if (LoadedTable != nullptr)
			{
				return LoadedTable->GetRowNames();
			}
		}
	}

	return TArray<FName>();
}
