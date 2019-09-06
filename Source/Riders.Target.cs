using UnrealBuildTool;
using System.Collections.Generic;

public class RidersTarget : TargetRules
{
	public RidersTarget(TargetInfo Target) : base(Target)
	{
        Type = TargetType.Game;

        ExtraModuleNames.AddRange( new string[] { "Riders","RidersUMG"} );
	}

	//
	// TargetRules interface.
	//

	//public override void SetupBinaries(
	//	TargetInfo Target,
	//	ref List<UEBuildBinaryConfiguration> OutBuildBinaryConfigurations,
	//	ref List<string> OutExtraModuleNames
	//	)
	//{
	//	OutExtraModuleNames.AddRange( new string[] { "Riders" } );
	//}
}
