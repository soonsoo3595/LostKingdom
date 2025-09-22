// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

/**
 * GameInstanceSubsystem 클래스 정의 후 이를 다중 상속하면 인스턴스를 얻는 함수를 사용할 수 있음
 */
template<typename Derived>
class TLWGameInstanceSubsystemBase
{
public:
	static Derived* Get(const UObject* WorldContextObject)
	{
		if (UWorld* World = GEngine->GetWorldFromContextObject(WorldContextObject, EGetWorldErrorMode::LogAndReturnNull))
		{
			if (UGameInstance* GameInstance = World->GetGameInstance())
			{
				return GameInstance->GetSubsystem<Derived>();
			}
		}

		return nullptr;
	}
};