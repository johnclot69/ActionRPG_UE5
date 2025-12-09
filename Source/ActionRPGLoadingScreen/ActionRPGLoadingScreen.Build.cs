// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

// 此模块必须在 .uproject 文件中“PreLoadingScreen”加载，否则无法及时挂接！

public class ActionRPGLoadingScreen : ModuleRules
{
	public ActionRPGLoadingScreen(ReadOnlyTargetRules Target)
		: base(Target)
	{
		PrivatePCHHeaderFile = "Public/ActionRPGLoadingScreen.h";

		PCHUsage = PCHUsageMode.UseSharedPCHs;

		PrivateIncludePaths.Add("ActionRPGLoadingScreen/Private");

		PublicDependencyModuleNames.AddRange(
			new string[] {
				"Core",
				"CoreUObject",
				"Engine"
			}
		);

		PrivateDependencyModuleNames.AddRange(
			new string[] {
				"MoviePlayer",
				"Slate",
				"SlateCore",
				"InputCore"
			}
		);
	}
}
