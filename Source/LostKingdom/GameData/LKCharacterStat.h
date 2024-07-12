#pragma once

#include "CoreMinimal.h"
#include "Engine/DataTable.h"
#include "LKCharacterStat.generated.h"

USTRUCT(BlueprintType)
struct FLKCharacterStat : public FTableRowBase
{
	GENERATED_BODY()
	
public:
	FLKCharacterStat() : MaxHP(0.0f), ATK(0.0f), DEF(0.0f), Exp(0.0f) {}

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stat")
	float MaxHP;	// 최대 체력

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stat")
	float ATK;		// 공격력

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stat")
	float DEF;		// 방어력

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stat")
	float Exp;		// 이 캐릭터를 죽였을 때 획득할 경험치 / 플레이어의 경우 레벨업에 필요한 경험치

	FLKCharacterStat operator+(const FLKCharacterStat& Other) const
	{
		const float* const ThisPtr = reinterpret_cast<const float* const>(this);
		const float* const OtherPtr = reinterpret_cast<const float* const>(&Other);

		FLKCharacterStat Result;
		float* ResultPtr = reinterpret_cast<float*>(&Result);

		int32 StatNum = sizeof(FLKCharacterStat) / sizeof(float);
		for (int32 i = 0; i < StatNum; ++i)
		{
			ResultPtr[i] = ThisPtr[i] + OtherPtr[i];
		}

		return Result;
	}
};