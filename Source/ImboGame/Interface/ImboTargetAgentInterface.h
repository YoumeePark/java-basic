#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "ImboTargetAgentInterface.generated.h"

UINTERFACE(MinimalAPI)
class UImboTargetAgentInterface : public UInterface
{
	GENERATED_BODY()
};

class IMBOGAME_API IImboTargetAgentInterface
{
	GENERATED_BODY()

public:
	virtual void SetHiddenInGameTargetDecal(bool active) = 0;
};
