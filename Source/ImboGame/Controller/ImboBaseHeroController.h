#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "ImboBaseHeroController.generated.h"

UCLASS()
class IMBOGAME_API AImboBaseHeroController : public APlayerController
{
	GENERATED_BODY()

public:
	/* Default */
	AImboBaseHeroController();
	virtual void BeginPlay() override;
	virtual void PlayerTick(float DeltaTime) override;

protected:
	virtual void SetupInputComponent() override;
};
