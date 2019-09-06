

using UnrealBuildTool;

public class Riders : ModuleRules
{
	public Riders(ReadOnlyTargetRules Target) : base(Target)
	{
       PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

       PublicDependencyModuleNames.AddRange(
            new string[] { 
                "Core", 
                "CoreUObject", 
                "Engine", 
                "InputCore", 
                "AIModule", 
                "AnimGraph", 
                "BlueprintGraph",
                "UMG",                
                "APPFRAMEWORK",
                "ANIMGRAPHRUNTIME",
                "XMLPARSER",
                "PhysX",
                "APEX",
                "PhysXVehicles",
                "PhysXVehicleLib",
                "RenderCore",
                "UnrealEd",
                "MEDIAASSETS"
            }
        );

        PrivateDependencyModuleNames.AddRange(new string[] { "FMODStudio" });

		// Uncomment if you are using Slate UI
		 PrivateDependencyModuleNames.AddRange(new string[] { "Slate", "SlateCore" });
		
		// Uncomment if you are using online features
		// PrivateDependencyModuleNames.Add("OnlineSubsystem");
		// if ((Target.Platform == UnrealTargetPlatform.Win32) || (Target.Platform == UnrealTargetPlatform.Win64))
		// {
		//		if (UEBuildConfiguration.bCompileSteamOSS == true)
		//		{
		//			DynamicallyLoadedModuleNames.Add("OnlineSubsystemSteam");
		//		}
		// }
	}
}
