

using UnrealBuildTool;
using System.Collections.Generic;

public class TankGameTarget : TargetRules
{
	public TankGameTarget(TargetInfo Target) : base(Target)
	{
		Type = TargetType.Game;

		ExtraModuleNames.AddRange( new string[] { "TankGame" } );
	}
}
