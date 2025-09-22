#pragma once

#include "CoreMinimal.h"
#include "Engine/DataTable.h"
#include "LWTableInfo.generated.h"

UENUM(BlueprintType)
enum class ELWInfoType : uint8
{
	Static		UMETA(DisplayName = "Static"),
	Dynamic		UMETA(DisplayName = "Dynamic"),
};

USTRUCT(BlueprintType)
struct FLWTableInfo : public FTableRowBase
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Info)
	ELWInfoType InfoType;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Info)
	TSoftObjectPtr<class UDataTable> TablePtr;

	FLWTableInfo()
		: InfoType(ELWInfoType::Static)
	{
	}
};
