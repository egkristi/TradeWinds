using UnrealBuildTool;
using System.Collections.Generic;
using System.IO;

public class ArgosyTidesEditorTarget : TargetRules
{
	public ArgosyTidesEditorTarget(TargetInfo Target) : base(Target)
	{
		Type = TargetType.Editor;
		DefaultBuildSettings = BuildSettingsVersion.V5;
		IncludeOrderVersion = EngineIncludeOrderVersion.Unreal5_4;
		ExtraModuleNames.Add("ArgosyTides");
	}
}
