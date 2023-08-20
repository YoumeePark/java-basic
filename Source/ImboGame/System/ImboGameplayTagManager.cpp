#include "ImboGameplayTagManager.h"
#include "Global.h"
#include "GameplayTagsSettings.h"
#include "GameplayTags/Public/NativeGameplayTags.h"
#include "GameplayTags/Public/GameplayTags.h"

#define IMBO_NATIVE_TAG(Desc) L"(Native)"##Desc

FImboGameplayTagManager FImboGameplayTagManager::TagManager;

FImboGameplayTagManager::FImboGameplayTagManager()
{
}

void FImboGameplayTagManager::AddTags()
{
	/* Character : Hero */
	AddTag(Character_Hero_Paladin, "Character.Hero.Paladin", "Character by used tag PlayerCharacter");
	AddTag(Character_Hero_Warrior, "Character.Hero.Warrior", "Character by used tag PlayerCharacter");
	AddTag(Character_Hero_DeathKnight, "Character.Hero.DeathKnight", "Character by used tag PlayerCharacter");
	AddTag(Character_Hero_Rogue, "Character.Hero.Rogue", "Character by used tag PlayerCharacter");
	AddTag(Character_Hero_Ranger, "Character.Hero.Ranger", "Character by used tag PlayerCharacter");
	AddTag(Character_Hero_Druid, "Character.Hero.Druid", "Character by used tag PlayerCharacter");
	AddTag(Character_Hero_Warlock, "Character.Hero.Warlock", "Character by used tag PlayerCharacter");
	AddTag(Character_Hero_FireMage, "Character.Hero.FireMage", "Character by used tag PlayerCharacter");
	AddTag(Character_Hero_IceMage, "Character.Hero.IceMage", "Character by used tag PlayerCharacter");
	AddTag(Character_Hero_Priest, "Character.Hero.Priest", "Character by used tag PlayerCharacter");


	/* Character : Enemy : Monster */
	AddTag("Character.Enemy.Monster.FireSpirit", "Character by used tag Normal Monster");
	AddTag("Character.Enemy.Monster.WaterSpirit", "Character by used tag Normal Monster");
	AddTag("Character.Enemy.Monster.WindSpirit", "Character by used tag Normal Monster");
	AddTag("Character.Enemy.Monster.RockSpirit", "Character by used tag Normal Monster");


	/* Character : Enemy : Boss */
	AddTag("Character.Enemy.Boss.BelthazarLoardOfFlame", "Character by used tag Boss");
	AddTag("Character.Enemy.Boss.AiSerpentOfTheSea", "Character by used tag Boss");


	/* Status */
	AddTag("Status.Strength", "Default Game Status");
	AddTag("Status.Intelligence", "Default Game Status");
	AddTag("Status.Agility", "Default Game Status");

	AddTag("Status.Health", "Default Game Status");
	AddTag("Status.Mana", "Default Game Status");
	AddTag("Status.Stamina", "Default Game Status");

	AddTag("Status.AttackDamage", "Default Game Status");
	AddTag("Status.AttackDefence", "Default Game Status");
	AddTag("Status.AttackCriticalRate", "Default Game Status");
	AddTag("Status.AttackCriticalDamage", "Default Game Status");

	AddTag("Status.MagicDamage", "Default Game Status");
	AddTag("Status.MagicDefence", "Default Game Status");
	AddTag("Status.MagicCriticalRate", "Default Game Status");
	AddTag("Status.MagicCriticalDamage", "Default Game Status");
}

void FImboGameplayTagManager::InitializeNativeTags()
{
	UGameplayTagsManager& manager = UGameplayTagsManager::Get();
	TagManager.AddAllTags(manager);
	manager.DoneAddingNativeTags(); // Notify manager that we are done adding native tags.
}

void FImboGameplayTagManager::AddAllTags(UGameplayTagsManager& manager)
{

}

void FImboGameplayTagManager::AddTag(const ANSICHAR* tagName, const ANSICHAR* tagComment)
{
	UGameplayTagsManager::Get().AddNativeGameplayTag(FName(tagName), FString(TEXT("(Native) ")) + FString(tagComment));
}

void FImboGameplayTagManager::AddTag(FGameplayTag& outTag, const ANSICHAR* tagName, const ANSICHAR* tagComment)
{
	outTag = UGameplayTagsManager::Get().AddNativeGameplayTag(FName(tagName), FString(TEXT("(Native) ")) + FString(tagComment));
}

FGameplayTag FImboGameplayTagManager::FindTagByString(FString TagString, bool bMatchPartialString)
{
	const UGameplayTagsManager& Manager = UGameplayTagsManager::Get();
	FGameplayTag Tag = Manager.RequestGameplayTag(FName(*TagString), false);

	if (!Tag.IsValid() && bMatchPartialString)
	{
		FGameplayTagContainer AllTags;
		Manager.RequestAllGameplayTags(AllTags, true);
		
		for (const FGameplayTag TestTag : AllTags)
		{
			if (TestTag.ToString().Contains(TagString))
			{
				UE_LOG(ImboGame, Display, TEXT("Could not find exact match for tag [%s] but found partial match on tag [%s]."), *TagString, *TestTag.ToString());
				Tag = TestTag;
				break;
			}
		}
	}

	return Tag;
}