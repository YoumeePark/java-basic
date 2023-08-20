#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "GameplayTags.h"
#include "GameData/Character/Hero/ImboHeroData.h"
#include "ImboHeroAsset.generated.h"

struct FGameplayTag;
class UImboHeroData;

UCLASS(BlueprintType)
class IMBOGAME_API UImboHeroAsset : public UDataAsset
{
	GENERATED_BODY()
	
public:
	TObjectPtr<UImboHeroData> GetHeroData(FGameplayTag heroTag);
	
public:
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
		TMap<FGameplayTag, TSoftObjectPtr<UImboHeroData>> HeroDatas;
};
