// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"

DECLARE_LOG_CATEGORY_EXTERN(LogLostWaves, Log, All);

// NetMode 확인 (Dedicated, Client, Standalone)
#define LW_NETMODE \
    ((GetNetMode() == NM_Client) ? *FString::Printf(TEXT("CLIENT%d"), GPlayInEditorID) : \
    ((GetNetMode() == NM_Standalone) ? TEXT("STANDALONE") : TEXT("SERVER")))

// 현재 함수명
#define LW_FUNC ANSI_TO_TCHAR(__FUNCTION__)

// 로컬/리모트 Role (서버/클라 권한)
#define LW_LOCALROLE *(UEnum::GetValueAsString(TEXT("Engine.ENetRole"), GetLocalRole()))
#define LW_REMOTEROLE *(UEnum::GetValueAsString(TEXT("Engine.ENetRole"), GetRemoteRole()))

// Owner 기준 Role (Owner가 있는 컴포넌트용)
#define LW_OWNER_LOCALROLE *(UEnum::GetValueAsString(TEXT("Engine.ENetRole"), GetOwner()->GetLocalRole()))
#define LW_OWNER_REMOTEROLE *(UEnum::GetValueAsString(TEXT("Engine.ENetRole"), GetOwner()->GetRemoteRole()))

// 기본 로그
#define LW_LOG(Verbosity, Format, ...) \
    if (UE_LOG_ACTIVE(LogLostWaves, Verbosity)) \
    { \
        UE_LOG(LogLostWaves, Verbosity, TEXT("[%s][%s/%s] %s: %s"), \
            LW_NETMODE, LW_LOCALROLE, LW_REMOTEROLE, LW_FUNC, *FString::Printf(Format, ##__VA_ARGS__)); \
    }

// 컴포넌트 등 Owner 기준 로그
#define LW_LOG_OWNER(Verbosity, Format, ...) \
    if (UE_LOG_ACTIVE(LogLostWaves, Verbosity)) \
    { \
        UE_LOG(LogLostWaves, Verbosity, TEXT("[%s][%s/%s] %s: %s"), \
            LW_NETMODE, LW_OWNER_LOCALROLE, LW_OWNER_REMOTEROLE, LW_FUNC, *FString::Printf(Format, ##__VA_ARGS__)); \
    }

// Role 정보가 없는 범용 로그
#define LW_LOG_SIMPLE(Verbosity, Format, ...) \
    UE_LOG(LogLostWaves, Verbosity, TEXT("[%s] %s: %s"), \
        LW_NETMODE, *LW_FUNC, *FString::Printf(Format, ##__VA_ARGS__))

// 진입/종료 간단 로그
#define LW_LOG_BEGIN() LW_LOG(Log, TEXT("Begin"))
#define LW_LOG_END()   LW_LOG(Log, TEXT("End"))

