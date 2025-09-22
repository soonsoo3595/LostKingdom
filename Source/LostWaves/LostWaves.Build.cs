// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class LostWaves : ModuleRules
{
	public LostWaves(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

        PublicIncludePaths.AddRange(new string[] { "LostWaves" });
        PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore", "HeadMountedDisplay", "EnhancedInput", "NavigationSystem", "AIModule", "Niagara", "EnhancedInput", "HTTP", "Json", "JsonUtilities", "Sockets", "Networking", "UMG", "Slate", "SlateCore"});
	}
}
