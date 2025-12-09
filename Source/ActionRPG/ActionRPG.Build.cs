// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class ActionRPG : ModuleRules
{
	public ActionRPG(ReadOnlyTargetRules Target)
		: base(Target)
	{
		PrivatePCHHeaderFile = "Public/ActionRPG.h";

		PublicDependencyModuleNames.AddRange(
			new string[] {
				"Core",
				"CoreUObject",
				"Engine"
			}
		);

		PrivateDependencyModuleNames.AddRange(
			new string[] {
				"ActionRPGLoadingScreen",
				"Slate",
				"SlateCore",
				"InputCore",
				"MoviePlayer",
				"GameplayAbilities",
				"GameplayTags",
				"GameplayTasks",
				"AIModule"
			}
		);

		if (Target.Platform == UnrealTargetPlatform.IOS)
		{
			PrivateDependencyModuleNames.AddRange(new string[] { "OnlineSubsystem", "OnlineSubsystemUtils" });
			DynamicallyLoadedModuleNames.Add("OnlineSubsystemFacebook");
			DynamicallyLoadedModuleNames.Add("OnlineSubsystemIOS");
			DynamicallyLoadedModuleNames.Add("IOSAdvertising");
		}
		else if (Target.Platform == UnrealTargetPlatform.Android)
		{
			PrivateDependencyModuleNames.AddRange(new string[] { "OnlineSubsystem", "OnlineSubsystemUtils" });
			DynamicallyLoadedModuleNames.Add("AndroidAdvertising");
			DynamicallyLoadedModuleNames.Add("OnlineSubsystemGooglePlay");
            // 添加 UPL 以将 configrules.txt 添加到我们的 APK 中
            string PluginPath = Utils.MakePathRelativeTo(ModuleDirectory, Target.RelativeEnginePath);
            AdditionalPropertiesForReceipt.Add("AndroidPlugin", System.IO.Path.Combine(PluginPath, "AddRoundIcon_UPL.xml"));

        }
    }
}
