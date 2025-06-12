// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class LostKingdom : ModuleRules
{
	public LostKingdom(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

        PublicIncludePaths.AddRange(new string[] { "LostKingdom" });
        PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore", "HeadMountedDisplay", "NavigationSystem", "AIModule", "Niagara", "EnhancedInput", "HTTP", "Json", "JsonUtilities", "Sockets", "Networking", "UMG", "Slate", "SlateCore" });
    }
}
