// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

/**
 *
 */
template<typename Derived>
class TLKGameInstanceSubsystemBase
{
public:
	static Derived* GetInstance(UWorld* WorldContext)
	{
		if (WorldContext == nullptr) return nullptr;

		if (UGameInstance* GameInstance = WorldContext->GetGameInstance())
		{
			return GameInstance->GetSubsystem<Derived>();
		}

		return nullptr;
	}
};
