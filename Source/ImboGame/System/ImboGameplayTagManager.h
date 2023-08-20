#pragma once

#include "CoreMinimal.h"
#include "NativeGameplayTags.h"

struct IMBOGAME_API FImboGameplayTagManager : public FGameplayTagNativeAdder
{
public:
	static const FImboGameplayTagManager& Get() { return TagManager; };
	static FGameplayTag FindTagByString(FString TagString, bool bMatchPartialString = false);
	static void InitializeNativeTags();


public:
	FImboGameplayTagManager();
	virtual void AddTags() override; //이거 써도 되고 그냥 AddAllTags 써도 된다.


public:
	FImboGameplayTagManager& GetInstance() const { return TagManager; };

	void AddAllTags(UGameplayTagsManager& manager);
	void AddTag(const ANSICHAR* tagName, const ANSICHAR* tagComment);
	void AddTag(FGameplayTag& outTag, const ANSICHAR* tagName, const ANSICHAR* tagComment);


public:
	/* Character : Hero */
	FGameplayTag Character_Hero_Paladin;
	FGameplayTag Character_Hero_Warrior;
	FGameplayTag Character_Hero_DeathKnight;
	FGameplayTag Character_Hero_Rogue;
	FGameplayTag Character_Hero_Ranger;
	FGameplayTag Character_Hero_Druid;
	FGameplayTag Character_Hero_Warlock;
	FGameplayTag Character_Hero_FireMage;
	FGameplayTag Character_Hero_IceMage;
	FGameplayTag Character_Hero_Priest;


private:
	static FImboGameplayTagManager TagManager;
};
