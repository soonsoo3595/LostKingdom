#pragma once

#include "CoreMinimal.h"
#include "LKLoginSession.generated.h"

USTRUCT(BlueprintType)
struct FLKLoginSession
{
	GENERATED_BODY()

public:
    UPROPERTY()
    FString AuthToken;

    UPROPERTY()
    int32 AccountKey;

    UPROPERTY()
    FGuid UserKey;

    bool IsValid() const
    {
        return !AuthToken.IsEmpty() && UserKey.IsValid();
    }

    void Clear()
    {
        AuthToken = TEXT("");
        AccountKey = -1;
        UserKey.Invalidate();
    }
};