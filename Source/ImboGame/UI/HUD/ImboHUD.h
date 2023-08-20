#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "ImboHUD.generated.h"

/**
 * @brief Widget을 관리할 최종 HUD
 */
UCLASS(Blueprintable)
class IMBOGAME_API AImboHUD final : public AHUD
{
	GENERATED_BODY()

public:
	/* Default */
	virtual void Tick(float DeltaSeconds) override;


protected:
	/* Default */
	virtual void BeginPlay() override;


	/*  */
	
};
