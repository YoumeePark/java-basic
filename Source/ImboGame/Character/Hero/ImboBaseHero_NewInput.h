#pragma once

#include "CoreMinimal.h"
#include "Character/ImboBaseCharacter.h"
#include "AbilitySystemInterface.h"
#include "InputMappingContext.h"
#include "InputActionValue.h"
#include "Components/TimelineComponent.h"
//#include "Abilities/GameplayAbility.h"
#include "ImboBaseHero.h"
#include "Ability/ImboAbilitySystemComponent.h"
#include "ImboBaseHero_NewInput.generated.h"


class UInputMappingContext;
class UInputAction;

class USpringArmComponent;
class UCameraComponent;

class UImboTargetComponent;

class AImboBaseHeroController;
class UAbilitySystemComponent;

UCLASS(config=Game)
class IMBOGAME_API AImboBaseHero_NewInput : public AImboBaseCharacter//, public IAbilitySystemInterface//, public IGenericTeamAgentInterface
{
	GENERATED_BODY()


/* Default */
public:	
	AImboBaseHero_NewInput();
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


/* Enhanced Input */
public:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
		TObjectPtr<UInputMappingContext> DefaultMappingContext;

	UPROPERTY(EditDefaultsOnly)
		TObjectPtr<UInputAction> MouseLeft;

	UPROPERTY(EditDefaultsOnly)
		TObjectPtr<UInputAction> MouseRight;

	UPROPERTY(EditDefaultsOnly, Category = Input)
		TObjectPtr<UInputAction> WS;

	UPROPERTY(EditDefaultsOnly, Category = Input)
		TObjectPtr<UInputAction> DA;

	void OnMove(const FInputActionValue& Value); //Called for movement input
	void OnLook(const FInputActionValue& Value);	

	void OnClickMouseLeft(const FInputActionValue& Value);
	void OnUnClickMouseLeft();
	void OnClickMouseRight(const FInputActionValue& Value);
	void OnUnClickMouseRight();

	void OnMouseWheel(const FInputActionValue& Value);

	void OnESC(const FInputActionValue& Value);
	void OnTab(const FInputActionValue& Value);


/* New Input System */
public:
	void OnWS(const FInputActionValue& Value);
	void OnDA(const FInputActionValue& Value);


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


private:
	float RotationRate = 150.0f;
};
