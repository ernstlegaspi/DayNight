using UnrealBuildTool;

public class DayNight : ModuleRules {
	public DayNight(ReadOnlyTargetRules Target) : base(Target) {
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;
	
		PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore", "EnhancedInput", "UMG", "GameplayCameras", "Niagara" });

		PrivateDependencyModuleNames.AddRange(new string[] {  });
	}
}
