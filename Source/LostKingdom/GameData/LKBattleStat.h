#pragma once

#include "CoreMinimal.h"
#include "LKBattleStat.generated.h"

USTRUCT(BlueprintType)
struct FLKBattleStat
{
	GENERATED_BODY()
	
public:
	FLKBattleStat() : CritPercent(0.0f), SpecialPercent(0.0f), SpeedPercent(0.0f){}

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float CritPercent;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float SpecialPercent;		

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float SpeedPercent;

	FLKBattleStat operator+(const FLKBattleStat& Other) const
	{
		FLKBattleStat Result;
		Result.CritPercent = this->CritPercent + Other.CritPercent;
		Result.SpecialPercent = this->SpecialPercent + Other.SpecialPercent;
		Result.SpeedPercent = this->SpeedPercent + Other.SpeedPercent;
		return Result;
	}

	FLKBattleStat operator-(const FLKBattleStat& Other) const
	{
		FLKBattleStat Result;
		Result.CritPercent = this->CritPercent - Other.CritPercent;
		Result.SpecialPercent = this->SpecialPercent - Other.SpecialPercent;
		Result.SpeedPercent = this->SpeedPercent - Other.SpeedPercent;
		return Result;
	}
};