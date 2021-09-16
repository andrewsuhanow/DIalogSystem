// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class DialogSystem_Test : ModuleRules
{
	public DialogSystem_Test(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore", "HeadMountedDisplay" });
	}
}
