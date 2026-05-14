using UnrealBuildTool;

public class ArgosyTides : ModuleRules
{
	public ArgosyTides(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;
		
		bEnableExceptions = true;
		bUseUnity = true;
		
		PublicDependencyModuleNames.AddRange(new string[] { 
			"Core", 
			"CoreUObject", 
			"Engine", 
			"InputCore",
			"Slate",
			"SlateCore",
			"UMG"
		});
		
		PrivateDependencyModuleNames.AddRange(new string[] { 
			"Projects",
			"ApplicationCore"
		});
		
		// Uncomment if you are using online features
		// PublicDependencyModuleNames.Add("OnlineSubsystem");
		// PublicDependencyModuleNames.Add("OnlineSubsystemSteam");
		
		// Uncomment if you are using Slate UI
		// PrivateDependencyModuleNames.AddRange(new string[] { "Slate", "SlateCore" });
		
		// Uncomment if you are using UMG
		// PrivateDependencyModuleNames.AddRange(new string[] { "UMG" });
		
		DynamicallyLoadedModuleNames.AddRange(new string[] { });
	}
}
