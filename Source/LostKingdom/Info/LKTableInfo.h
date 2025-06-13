#pragma once

#include "CoreMinimal.h"
#include "Engine/DataTable.h"
#include "LKTableInfo.generated.h"

UENUM(BlueprintType)
enum class EInfoType : uint8
{
	Static		UMETA(DisplayName = "Static"),
	Dynamic		UMETA(DisplayName = "Dynamic"),
};

USTRUCT(BlueprintType)
struct FLKTableInfo : public FTableRowBase
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Info)
	EInfoType InfoType;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Info)
	TSoftObjectPtr<class UDataTable> TablePtr;

	FLKTableInfo()
		: InfoType(EInfoType::Static)
		, TablePtr(nullptr)
	{
	}
};
