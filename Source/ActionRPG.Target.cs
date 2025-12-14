// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class ActionRPGTarget : TargetRules
{
	public ActionRPGTarget(TargetInfo Target)
		: base(Target)
	{
		Type = TargetType.Game;
		ExtraModuleNames.AddRange(["ActionRPG"]);

		DefaultBuildSettings = BuildSettingsVersion.V6;
	}
}
