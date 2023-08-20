#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "GameData/Character/Hero/ImboHeroData.h"
#include "ImboCharacterAsset.generated.h"

class UImboHeroData;

UCLASS(BlueprintType)
class IMBOGAME_API UImboCharacterAsset : public UDataAsset
{
	GENERATED_BODY()
	
public:
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
		TObjectPtr<UImboHeroData> Hero;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
		TObjectPtr<UImboHeroData> Monster;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
		TObjectPtr<UImboHeroData> Boss;
};
