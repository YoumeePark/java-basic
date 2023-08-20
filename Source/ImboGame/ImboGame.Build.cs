// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class ImboGame : ModuleRules
{
	public ImboGame(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		
		/* Include Paths */
		{
			//PublicIncludePaths.Add(ModuleDirectory);
			PublicIncludePaths.AddRange(
				new string[] {
					"ImboGame"
				}
			);

			//PrivateIncludePaths.Add(ModuleDirectory);
			PrivateIncludePaths.AddRange(
				new string[] {
					"ImboGame"
				}
			);
		}
		

		/* Dependency Module Name */
		{

			PublicDependencyModuleNames.AddRange(
				new string[] {
					"Core",
					"CoreUObject",
					"Engine",
					"InputCore",
					"HeadMountedDisplay",
                    "EnhancedInput",
                    "UMG",
                    "Niagara",
                    "AIModule",

					/* User Defined */ 
					"AnimGraphRuntime",

					/* Experimental */
					"GameplayAbilities",	//GameplayAbility
					"GameplayTags",			//"
					"GameplayTasks",		//"
				}
			);

			PrivateDependencyModuleNames.AddRange(
				new string[] {
                    //"InputCore",
                    //"Slate",
                    //"SlateCore",
                    //"RenderCore",
                    //"DeveloperSettings",
					"AnimGraphRuntime",
					//"EnhancedInput",
					//"NetCore",
					//"RHI",
					//"Projects",
					//"Gauntlet",
					//"UMG",
					//"CommonUI",
					//"CommonInput",
					//"GameSettings",
					//"CommonGame",
					//"CommonUser", //Lyra Plug-in, �Ϲ� ����� �÷������� ���� ���
					//"GameSubtitles",
					//"GameplayMessageRuntime",
					//"AudioMixer",
					//"NetworkReplayStreaming",
					//"UIExtension",
					//"ClientPilot",
					//"AudioModulation"
				}
			);
		}


		/* Dynamically Load Module */
		{
			DynamicallyLoadedModuleNames.AddRange(
				new string[] {
				}
			);
		}


		/* DrawDebug Function */
		{
			PublicDefinitions.Add("SHIPPING_DRAW_DEBUG_ERROR = 1"); //Generate compile errors if using DrawDebug functions in test/shipping builds.Z
		}
	}
}
