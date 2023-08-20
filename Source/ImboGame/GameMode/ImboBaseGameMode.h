#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "System/ImboGameInstance.h"
#include "ImboBaseGameMode.generated.h"

UCLASS(Blueprintable)
class IMBOGAME_API AImboBaseGameMode : public AGameModeBase
{
	GENERATED_BODY()

public:
	/* Default */
	AImboBaseGameMode();


	/* Base Function */
	const float GetFPS() const;
	UImboGameInstance* GetImboGameInstance();


private:
	/* Default Member */
	UPROPERTY(Transient)
		UImboGameInstance* CurrentGameInstance;
};
