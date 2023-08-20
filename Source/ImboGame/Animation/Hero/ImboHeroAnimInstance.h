#pragma once

#include "CoreMinimal.h"
#include "Animation/ImboBaseAnimInstance.h"
#include "ImboHeroAnimInstance.generated.h"

UCLASS()
class IMBOGAME_API UImboHeroAnimInstance : public UImboBaseAnimInstance
{
	GENERATED_BODY()


/* Default */
public:
	UImboHeroAnimInstance();
	virtual void NativeBeginPlay() override;
	virtual void NativeUpdateAnimation(float DeltaSeconds) override;

};
