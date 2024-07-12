#pragma once

#include "CoreMinimal.h"
#include "LKBattleStat.generated.h"

USTRUCT(BlueprintType)
struct FLKBattleStat
{
	GENERATED_BODY()
	
public:
	FLKBattleStat() : Crit(0.0f), Special(0.0f), Speed(0.0f){}

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "BattleStat")
	float Crit;			// 치명 

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "BattleStat")
	float Special;		// 특화

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "BattleStat")
	float Speed;		// 신속


	FLKBattleStat operator+(const FLKBattleStat& Other) const
	{
		const float* const ThisPtr = reinterpret_cast<const float* const>(this);
		const float* const OtherPtr = reinterpret_cast<const float* const>(&Other);

		FLKBattleStat Result;
		float* ResultPtr = reinterpret_cast<float*>(&Result);

		int32 StatNum = sizeof(FLKBattleStat) / sizeof(float);
		for (int32 i = 0; i < StatNum; ++i)
		{
			ResultPtr[i] = ThisPtr[i] + OtherPtr[i];
		}

		return Result;
	}
};