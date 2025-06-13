// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/EngineSubsystem.h"
#include "Engine/DataTable.h"
#include "LKInfoManager.generated.h"

class UDataTable;

/**
 * 
 */
UCLASS()
class LOSTKINGDOM_API ULKInfoManager : public UEngineSubsystem
{
	GENERATED_BODY()
	
public:
	ULKInfoManager();

	static ULKInfoManager* GetInstance();

	template<typename T>
	const T* GetInfo(FName TableKey, FName RowKey)
	{
		if (TObjectPtr<UDataTable>* FoundTable = StaticInfo.Find(TableKey))
		{
			return (*FoundTable)->FindRow<T>(RowKey, TEXT(""));
		}
		else if (TSoftObjectPtr<UDataTable>* FoundDynamicTable = DynamicInfo.Find(TableKey))
		{
			if (UDataTable* LoadedTable = FoundDynamicTable->Get())
			{
				return LoadedTable->FindRow<T>(RowKey, TEXT(""));
			}
			else
			{
				LoadedTable = FoundDynamicTable->LoadSynchronous();
				if (LoadedTable != nullptr)
				{
					return LoadedTable->FindRow<T>(RowKey, TEXT(""));
				}
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
};
