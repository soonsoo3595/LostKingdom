#pragma once

#include "CoreMinimal.h"

// NetMode 확인 (Dedicated, Client, Standalone)
#define LK_NETMODE \
    ((GetNetMode() == NM_Client) ? *FString::Printf(TEXT("CLIENT%d"), GPlayInEditorID) : \
    ((GetNetMode() == NM_Standalone) ? TEXT("STANDALONE") : TEXT("SERVER")))

// 로컬/리모트 Role (서버/클라 권한)
#define LK_LOCALROLE *(UEnum::GetValueAsString(TEXT("Engine.ENetRole"), GetLocalRole()))
#define LK_REMOTEROLE *(UEnum::GetValueAsString(TEXT("Engine.ENetRole"), GetRemoteRole()))

// Owner 기준 Role (Owner가 있는 컴포넌트용)
#define LK_OWNER_LOCALROLE *(UEnum::GetValueAsString(TEXT("Engine.ENetRole"), GetOwner()->GetLocalRole()))
#define LK_OWNER_REMOTEROLE *(UEnum::GetValueAsString(TEXT("Engine.ENetRole"), GetOwner()->GetRemoteRole()))

// 현재 함수명
#define LK_FUNC ANSI_TO_TCHAR(__FUNCTION__)

// 기본 로그
#define LK_LOG(Verbosity, Format, ...) \
    UE_LOG(LogLK, Verbosity, TEXT("[%s][%s/%s] %s: %s"), \
        LK_NETMODE, LK_LOCALROLE, LK_REMOTEROLE, LK_FUNC, *FString::Printf(Format, ##__VA_ARGS__))

// 컴포넌트 등 Owner 기준 로그
#define LK_LOG_OWNER(Verbosity, Format, ...) \
    UE_LOG(LogLK, Verbosity, TEXT("[%s][%s/%s] %s: %s"), \
        LK_NETMODE, LK_OWNER_LOCALROLE, LK_OWNER_REMOTEROLE, LK_FUNC, *FString::Printf(Format, ##__VA_ARGS__))

// 진입/종료 간단 로그
#define LK_LOG_BEGIN() LK_LOG(Log, TEXT("Begin"))
#define LK_LOG_END()   LK_LOG(Log, TEXT("End"))

DECLARE_LOG_CATEGORY_EXTERN(LogLK, Log, All);
