#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "GameData/Character/Hero/ImboHeroStatus.h"
#include "ImboHeroData.generated.h"

struct FImboHeroStatus;
class USkeletalMesh;

UCLASS(BlueprintType)
class IMBOGAME_API UImboHeroData : public UDataAsset
{
	GENERATED_BODY()
	
public:
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
		USkeletalMesh* Mesh;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
		FImboHeroStatus Status;
};
