#pragma once

#include "CoreMinimal.h"
#include "LKBattleProperty.generated.h"

USTRUCT(BlueprintType)
struct FLKBattleProperty
{
	GENERATED_BODY()
	
public:
	FLKBattleProperty() : Crit(0.0f), Special(0.0f), Speed(0.0f){}

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float Crit;			// Critical

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float Special;		// Specialization

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float Speed;		// Speed

	float GetCritical() const { return (Crit * 0.036f) / 100; }
	float GetSpecial() const { return (Special * 0.1f) / 100; }
	float GetSpeed() const { return (Speed * 0.02f) / 100; }

    FLKBattleProperty operator+(const FLKBattleProperty& Other) const
    {
        FLKBattleProperty Result;
        Result.Crit = this->Crit + Other.Crit;
        Result.Special = this->Special + Other.Special;
        Result.Speed = this->Speed + Other.Speed;
        return Result;
    }

    FLKBattleProperty& operator+=(const FLKBattleProperty& Other)
    {
        this->Crit += Other.Crit;
        this->Special += Other.Special;
        this->Speed += Other.Speed;
        return *this;
    }

    FLKBattleProperty& operator-=(const FLKBattleProperty& Other)
    {
        this->Crit -= Other.Crit;
		this->Special -= Other.Special;
		this->Speed -= Other.Speed;
		return *this;
	}
};