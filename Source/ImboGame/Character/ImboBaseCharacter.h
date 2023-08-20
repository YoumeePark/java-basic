#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Components/DecalComponent.h"
#include "GenericTeamAgentInterface.h"
#include "GameplayTags.h"
#include "Interface/ImboTargetAgentInterface.h"
#include "ImboBaseCharacter.generated.h"

UCLASS()
class IMBOGAME_API AImboBaseCharacter : public ACharacter, public IGenericTeamAgentInterface, public IImboTargetAgentInterface
{
	GENERATED_BODY()


/* Default */
public:
	AImboBaseCharacter();
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;
	virtual void NotifyActorOnClicked(FKey ButtonPressed) override;


/* Generic TeamID Agent */
public:	
	FORCEINLINE virtual void SetGenericTeamId(const FGenericTeamId& TeamID) override { CurrentTeamID = TeamID; }
	FORCEINLINE virtual FGenericTeamId GetGenericTeamId() const override { return CurrentTeamID; }


/* Target Decal */
	virtual void SetHiddenInGameTargetDecal(bool active) override;


/* Tag */
public:
	UPROPERTY(EditDefaultsOnly)
		FGameplayTag ObjectIdentity;


/* Component */
public:
	UPROPERTY(EditDefaultsOnly)
		UDecalComponent* TargetDecal;


/* Default Member */
protected:
	UPROPERTY(EditAnywhere)
		FGenericTeamId CurrentTeamID;
};
