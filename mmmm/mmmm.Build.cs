// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class mmmm : ModuleRules
{
	public mmmm(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(new string[] {
			"Core",
			"CoreUObject",
			"Engine",
			"InputCore",
			"EnhancedInput",
			"AIModule",
			"StateTreeModule",
			"GameplayStateTreeModule",
			"UMG",
			"Slate"
		});

		PrivateDependencyModuleNames.AddRange(new string[] { });

		PublicIncludePaths.AddRange(new string[] {
			"mmmm",
			"mmmm/Variant_Platforming",
			"mmmm/Variant_Platforming/Animation",
			"mmmm/Variant_Combat",
			"mmmm/Variant_Combat/AI",
			"mmmm/Variant_Combat/Animation",
			"mmmm/Variant_Combat/Gameplay",
			"mmmm/Variant_Combat/Interfaces",
			"mmmm/Variant_Combat/UI",
			"mmmm/Variant_SideScrolling",
			"mmmm/Variant_SideScrolling/AI",
			"mmmm/Variant_SideScrolling/Gameplay",
			"mmmm/Variant_SideScrolling/Interfaces",
			"mmmm/Variant_SideScrolling/UI"
		});

		// Uncomment if you are using Slate UI
		// PrivateDependencyModuleNames.AddRange(new string[] { "Slate", "SlateCore" });

		// Uncomment if you are using online features
		// PrivateDependencyModuleNames.Add("OnlineSubsystem");

		// To include OnlineSubsystemSteam, add it to the plugins section in your uproject file with the Enabled attribute set to true
	}
}
