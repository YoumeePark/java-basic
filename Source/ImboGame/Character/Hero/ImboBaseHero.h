#pragma once

#include "CoreMinimal.h"
#include "Character/ImboBaseCharacter.h"
#include "AbilitySystemInterface.h"
#include "InputMappingContext.h"
#include "InputActionValue.h"
#include "Components/TimelineComponent.h"
//#include "Abilities/GameplayAbility.h"

#include "Ability/ImboAbilitySystemComponent.h"
#include "ImboBaseHero.generated.h"


class UInputMappingContext;
class UInputAction;

class USpringArmComponent;
class UCameraComponent;

class UImboTargetComponent;

class AImboBaseHeroController;
class UAbilitySystemComponent;


USTRUCT()
struct FImboInputActions
{
	GENERATED_BODY()
	
public:
	UPROPERTY(EditDefaultsOnly)
		TObjectPtr<UInputAction> LookAction;

	UPROPERTY(EditDefaultsOnly)
		TObjectPtr<UInputAction> MoveAction;

	UPROPERTY(EditDefaultsOnly)
		TObjectPtr<UInputAction> JumpAction;

	UPROPERTY(EditDefaultsOnly)
		TObjectPtr<UInputAction> MouseLeft;

	UPROPERTY(EditDefaultsOnly)
		TObjectPtr<UInputAction> MouseRight;

	UPROPERTY(EditDefaultsOnly)
		TObjectPtr<UInputAction> MouseWheel;

	UPROPERTY(EditDefaultsOnly)
		TObjectPtr<UInputAction> ESC;

	UPROPERTY(EditDefaultsOnly)
		TObjectPtr<UInputAction> Tab;
};


UCLASS(config=Game)
class IMBOGAME_API AImboBaseHero : public AImboBaseCharacter//, public IAbilitySystemInterface//, public IGenericTeamAgentInterface
{
	GENERATED_BODY()


/* Default */
public:	
	AImboBaseHero();
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;


/* Getter & Setter */
public:
	UFUNCTION(BlueprintCallable, Category = "Imbo|Character")
		AImboBaseHeroController* GetImboPlayerController() const;

	UFUNCTION(BlueprintCallable, Category = "Imbo|Character")
		USpringArmComponent* GetImboPlayerSpringArmComponent() const;

	UFUNCTION(BlueprintCallable, Category = "Imbo|Character")
		UCameraComponent* GetImboPlayerCameraComponent() const;


/* Component */
public:
	UPROPERTY(EditAnywhere, Category = Camera)
		USpringArmComponent* SpringArm;

	UPROPERTY(EditAnywhere, Category = Camera)
		UCameraComponent* Camera;


/* ActorComponent */
public:
	UPROPERTY(VisibleAnywhere)
		UImboTargetComponent* TargetComponent;


/* Enhanced Input */
public:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
		TObjectPtr<UInputMappingContext> DefaultMappingContext;

	UPROPERTY(EditDefaultsOnly, Category = Input)
		FImboInputActions InputActions;

	void OnMove(const FInputActionValue& Value); //Called for movement input
	void OnLook(const FInputActionValue& Value);	

	void OnClickMouseLeft(const FInputActionValue& Value);
	void OnUnClickMouseLeft();
	void OnClickMouseRight(const FInputActionValue& Value);
	void OnUnClickMouseRight();

	void OnMouseWheel(const FInputActionValue& Value);

	void OnESC(const FInputActionValue& Value);
	void OnTab(const FInputActionValue& Value);
	

/* Target Agent Interface */
public:
	virtual void SetHiddenInGameTargetDecal(bool active) override;


/* Gameplay Ability System */
UPROPERTY(VisibleAnywhere)
	TObjectPtr<class UImboAbilitySystemComponent> AbilitySystemComponent;


///* Tag */
//public:
//	UPROPERTY(EditDefaultsOnly)
//		FGameplayTag HeroClass;


/* Default Properties */
private:
	/* Input */
	bool bClickMouseLeft;
	bool bClickMouseRight;
	float DefaultMouseX;
	float DefaultMouseY;

	/* Zoom */
	float ZoomSpeed = 100.0f;
	float MinTargetArmLength = 300.0f;
	float MaxTargetArmLength = 1500.0f;
};
