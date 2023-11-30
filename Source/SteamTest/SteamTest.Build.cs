// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class SteamTest : ModuleRules
{
	public SteamTest(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore", "HeadMountedDisplay", "EnhancedInput", "UMG", "GameplayTasks", "Slate", "SlateCore", "OnlineSubsystemSteam", "OnlineSubsystem", "OnlineSubsystemNull" });
	}
}
