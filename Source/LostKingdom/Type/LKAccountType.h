#pragma once

#include "CoreMinimal.h"

UENUM(BlueprintType)
enum class ELKProviderType : uint8 
{
	Guest		= 0,
	Google		= 1,
	Facebook	= 2,
	KaKao		= 3,
	Count
};