#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "GameData/Character/ImboCharacterAsset.h"
#include "ImboGameDataSupervisor.generated.h"

class UImboCharacterAsset;

UCLASS(BlueprintType, Blueprintable)
class IMBOGAME_API UImboGameDataSupervisor : public UDataAsset
{
	GENERATED_BODY()

public:
	UImboCharacterAsset* GetCharacter() const;

public:
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
		TSoftObjectPtr<UImboCharacterAsset> Character;
};