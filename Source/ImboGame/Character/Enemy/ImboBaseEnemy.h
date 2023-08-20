#pragma once

#include "CoreMinimal.h"
#include "Character/ImboBaseCharacter.h"
#include "ImboBaseEnemy.generated.h"

UCLASS()
class IMBOGAME_API AImboBaseEnemy : public AImboBaseCharacter
{
	GENERATED_BODY()


/* Default */
public:
	AImboBaseEnemy();
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;
	virtual void SetHiddenInGameTargetDecal(bool active) override;
};
