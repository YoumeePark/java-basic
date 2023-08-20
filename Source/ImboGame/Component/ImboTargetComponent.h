#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "GameFramework/Actor.h"
#include "Kismet/KismetSystemLibrary.h"
#include "ImboTargetComponent.generated.h"

class AImboBaseCharacter;
class AImboBaseHero;
class AImboBaseEnemy;
class USoundCue;


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class IMBOGAME_API UImboTargetComponent : public UActorComponent
{
	GENERATED_BODY()


/* Default */
public:	
	UImboTargetComponent();
	virtual void BeginPlay() override;
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;


	void EndTargeting();


/* Tab Targeting */
public:
	void StartTabTargeting();
private:
	void SetTabTraceTarget();
	void TabChangeTarget();
	void NextTabChangeTarget();


/* Mouse Click Targeting */
public:
	void StartClickTargeting();
private:
	void SetClickTraceTarget();


/* Target Getter & Setter */
public:
	FORCEINLINE AActor* GetCurrentTarget() const { return CurrentTarget.Get(); }


/* Trace Target Option */
public:
	UPROPERTY(EditAnywhere)
		TObjectPtr<USoundCue> TargetingSound;

	UPROPERTY(EditAnywhere)
		float TraceRadius = 2000.0f;

	UPROPERTY(EditAnywhere)
		float InteropSpeed = 2.5f;

	UPROPERTY(EditAnywhere)
		TEnumAsByte<EDrawDebugTrace::Type> Debug;


/* Target Setup : Common */
private:
	UPROPERTY()
		TObjectPtr<AActor> CurrentTarget;

	UPROPERTY()
		TObjectPtr<AActor> PreviousTarget;


/* Target Setup : Tab */
private:
	bool IsTab = false;
	TArray<TObjectPtr<AImboBaseEnemy>> TraceTargets;


/* Owner */
private:
	TObjectPtr<AImboBaseHero> OwnerCharacter;
};
