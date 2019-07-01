// Fill out your copyright notice in the Description page of Project Settings.

using UnrealBuildTool;

public class Revenger : ModuleRules
{
	public Revenger(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;
	
		PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore",
            "HeadMountedDisplay", "NavigationSystem", "AIModule", "GameplayTasks", "UMG", "ApexDestruction", "MediaAssets" });
        PrivateDependencyModuleNames.AddRange(new string[] { "Slate", "SlateCore" });
    }
}
