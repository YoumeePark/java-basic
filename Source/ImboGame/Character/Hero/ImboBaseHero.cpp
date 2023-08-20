#include "ImboBaseHero.h"
#include "Global.h"

#include "Components/CapsuleComponent.h"
#include "Components/InputComponent.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"

#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/Controller.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"

#include "Controller/ImboBaseHeroController.h"
#include "Blueprint/WidgetBlueprintLibrary.h"
#include "GameplayTags.h"
#include "GameFramework/GameModeBase.h"
#include "Materials/MaterialInstanceConstant.h"

#include "Component/ImboTargetComponent.h"

AImboBaseHero::AImboBaseHero()
{
	/* Set Default Pawn */
	PrimaryActorTick.bCanEverTick = true;
	bUseControllerRotationPitch = false; //Don't rotate when the controller rotates. Let that just affect the camera.
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;
	

	/* Team */
	CurrentTeamID = 0;


	/* Get Input Mapping Assets */
	ImboHelpers::GetAsset<UInputMappingContext>(&DefaultMappingContext, TEXT("/Script/EnhancedInput.InputMappingContext'/Game/Blueprint/Character/Input/MC_BaseInputMapping.MC_BaseInputMapping'"));
	ImboHelpers::GetAsset<UInputAction>(&InputActions.LookAction, TEXT("/Script/EnhancedInput.InputAction'/Game/Blueprint/Character/Input/IA_Look.IA_Look'"));
	ImboHelpers::GetAsset<UInputAction>(&InputActions.MoveAction, TEXT("/Script/EnhancedInput.InputAction'/Game/Blueprint/Character/Input/IA_Move.IA_Move'"));
	ImboHelpers::GetAsset<UInputAction>(&InputActions.JumpAction, TEXT("/Script/EnhancedInput.InputAction'/Game/Blueprint/Character/Input/IA_Jump.IA_Jump'"));
	ImboHelpers::GetAsset<UInputAction>(&InputActions.MouseLeft, TEXT("/Script/EnhancedInput.InputAction'/Game/Blueprint/Character/Input/IA_MouseLeft.IA_MouseLeft'"));
	ImboHelpers::GetAsset<UInputAction>(&InputActions.MouseRight, TEXT("/Script/EnhancedInput.InputAction'/Game/Blueprint/Character/Input/IA_MouseRight.IA_MouseRight'"));
	ImboHelpers::GetAsset<UInputAction>(&InputActions.MouseWheel, TEXT("/Script/EnhancedInput.InputAction'/Game/Blueprint/Character/Input/IA_MouseWheel.IA_MouseWheel'"));
	ImboHelpers::GetAsset<UInputAction>(&InputActions.ESC, TEXT("/Script/EnhancedInput.InputAction'/Game/Blueprint/Character/Input/IA_ESC.IA_ESC'"));
	ImboHelpers::GetAsset<UInputAction>(&InputActions.Tab, TEXT("/Script/EnhancedInput.InputAction'/Game/Blueprint/Character/Input/IA_Tab.IA_Tab'"));
	
	
	/* Create Default Component */
	ImboHelpers::CreateComponent<USpringArmComponent>(this, &SpringArm, TEXT("SpringArm"), GetCapsuleComponent());
	ImboHelpers::CreateComponent<UCameraComponent>(this, &Camera, TEXT("Camera"), SpringArm);


	/* Create Actor Component */
	ImboHelpers::CreateActorComponent(this, &TargetComponent, "TargetComponent");


	/* Set AnimInstance */
	//TSubclassOf<UAnimInstance> tempAnimInstance;
	//ImboHelpers::GetClass<UAnimInstance>(&tempAnimInstance, TEXT("/Script/Engine.AnimBlueprint'/Game/Blueprint/Animation/Hero/AB_ImboHeroAnimInstance.AB_ImboHeroAnimInstance'"));
	//tempMeshComp->SetAnimationMode(EAnimationMode::AnimationBlueprint);
	//tempMeshComp->SetAnimClass(tempAnimInstance);


	/* Set SpringArm & Camera */
	SpringArm->SetRelativeLocation(FVector(0, 0, 50));
	SpringArm->bUsePawnControlRotation = true;
	SpringArm->TargetArmLength = 1500.f;
	SpringArm->bDoCollisionTest = true;
	SpringArm->bEnableCameraLag = true;
	Camera->bUsePawnControlRotation = false; //Camera does not rotate relative to arm


	/* Configure Character Movement */
	GetCharacterMovement()->bOrientRotationToMovement = true; //Rotate Character to Controller


	/* Delegate */
	//OnSetTargetObject.BindUFunction(this, "ClickTargetObject");
}

void AImboBaseHero::BeginPlay()
{
	Super::BeginPlay();

	
	/* Input */
	if (APlayerController* PlayerController = Cast<APlayerController>(Controller))
	{
		if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer()))
		{
			Subsystem->AddMappingContext(DefaultMappingContext, 0);
		}
	}


	///* Test Use Tag */
	//{
	//	UGameplayTagsManager& tempManager = UGameplayTagsManager::Get();
	//
	//	FGameplayTag tempTag = FGameplayTag::RequestGameplayTag(FName("Character.Hero.DeathKnight")); // Ok
	//	//FGameplayTag tempTag = tempManager.RequestGameplayTagChildren(FGameplayTag(FName("Character"))); // Fail, please get the container
	//
	//	if (tempTag.IsValid())
	//	{
	//		ImboLog::Print("Success Get Tag!!");
	//		ImboLog::Print(tempTag.ToString());
	//	}
	//}
}

void AImboBaseHero::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AImboBaseHero::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	check(PlayerInputComponent);	
	Super::SetupPlayerInputComponent(PlayerInputComponent);


	if (UEnhancedInputComponent* EnhancedInputComponent = CastChecked<UEnhancedInputComponent>(PlayerInputComponent))
	{
		EnhancedInputComponent->BindAction(InputActions.LookAction, ETriggerEvent::Triggered, this, &AImboBaseHero::OnLook);
		EnhancedInputComponent->BindAction(InputActions.MoveAction, ETriggerEvent::Triggered, this, &AImboBaseHero::OnMove);

		EnhancedInputComponent->BindAction(InputActions.JumpAction, ETriggerEvent::Triggered, this, &ACharacter::Jump); //used built-in function
		EnhancedInputComponent->BindAction(InputActions.JumpAction, ETriggerEvent::Completed, this, &ACharacter::StopJumping); //used built-in function

		EnhancedInputComponent->BindAction(InputActions.MouseLeft, ETriggerEvent::Started, this, &AImboBaseHero::OnClickMouseLeft);
		EnhancedInputComponent->BindAction(InputActions.MouseLeft, ETriggerEvent::Completed, this, &AImboBaseHero::OnUnClickMouseLeft);
		EnhancedInputComponent->BindAction(InputActions.MouseRight, ETriggerEvent::Started, this, &AImboBaseHero::OnClickMouseRight);
		EnhancedInputComponent->BindAction(InputActions.MouseRight, ETriggerEvent::Completed, this, &AImboBaseHero::OnUnClickMouseRight);

		EnhancedInputComponent->BindAction(InputActions.MouseWheel, ETriggerEvent::Triggered, this, &AImboBaseHero::OnMouseWheel);

		EnhancedInputComponent->BindAction(InputActions.ESC, ETriggerEvent::Started, this, &AImboBaseHero::OnESC);
		EnhancedInputComponent->BindAction(InputActions.Tab, ETriggerEvent::Started, this, &AImboBaseHero::OnTab);
	}
}

void AImboBaseHero::OnMove(const FInputActionValue& Value)
{
	if(bClickMouseRight == true)
	{
		const FVector2D movementVector = Value.Get<FVector2D>();

		if (Controller != nullptr)
		{
			const FRotator Rotation = Controller->GetControlRotation();
			const FRotator YawRotation(0, Rotation.Yaw, 0);

			const FVector ForwardDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
			const FVector RightDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);

			AddMovementInput(ForwardDirection, movementVector.Y);
			AddMovementInput(RightDirection, movementVector.X);
		}
	}
}

void AImboBaseHero::OnLook(const FInputActionValue& Value)
{
	if (bClickMouseLeft || bClickMouseRight)
	{
		// input is a Vector2D
		FVector2D LookAxisVector = Value.Get<FVector2D>();

		if (Controller != nullptr)
		{
			// add yaw and pitch input to controller
			AddControllerYawInput(LookAxisVector.X);
			AddControllerPitchInput(LookAxisVector.Y * -1);
		}
	}
}

void AImboBaseHero::OnClickMouseLeft(const FInputActionValue& Value)
{
	auto inputValue = Value.Get<bool>();
	bClickMouseLeft = inputValue;
	GetImboPlayerController()->GetMousePosition(DefaultMouseX, DefaultMouseY);

	TargetComponent->StartClickTargeting();
}

void AImboBaseHero::OnUnClickMouseLeft()
{
	bClickMouseLeft = false;

	APlayerController* tempController = GetImboPlayerController();
	tempController->SetMouseLocation(DefaultMouseX, DefaultMouseY);
	tempController->SetShowMouseCursor(true);
	UWidgetBlueprintLibrary::SetInputMode_GameAndUIEx(GetImboPlayerController());
	UWidgetBlueprintLibrary::SetFocusToGameViewport();
}

void AImboBaseHero::OnClickMouseRight(const FInputActionValue& Value)
{
	auto inputValue = Value.Get<bool>();
	bClickMouseRight = inputValue;
	GetImboPlayerController()->GetMousePosition(DefaultMouseX, DefaultMouseY);
}

void AImboBaseHero::OnUnClickMouseRight()
{
	bClickMouseRight = false;

	APlayerController* tempController = GetImboPlayerController();
	tempController->SetMouseLocation(DefaultMouseX, DefaultMouseY);
	tempController->SetShowMouseCursor(true);
	UWidgetBlueprintLibrary::SetInputMode_GameAndUIEx(GetImboPlayerController());
	UWidgetBlueprintLibrary::SetFocusToGameViewport();
}

void AImboBaseHero::OnMouseWheel(const FInputActionValue& Value)
{
	auto inputValue = Value.Get<float>();
	SpringArm->TargetArmLength += (ZoomSpeed * inputValue); // * GetWorld()->GetDeltaSeconds());
	SpringArm->TargetArmLength = FMath::Clamp<float>(SpringArm->TargetArmLength, MinTargetArmLength, MaxTargetArmLength);
}

void AImboBaseHero::OnESC(const FInputActionValue& Value)
{
	auto inputValue = Value.Get<bool>();
	ImboLog::Print(inputValue);

	

	TargetComponent->EndTargeting();
}

void AImboBaseHero::OnTab(const FInputActionValue& Value)
{
	ImboLog::Print("Tab");

	TargetComponent->StartTabTargeting();
}

void AImboBaseHero::SetHiddenInGameTargetDecal(bool active)
{
	Super::SetHiddenInGameTargetDecal(active);

}

//void AImboBaseHero::ClickTargetObject(AActor* target)
//{
//
//}

AImboBaseHeroController* AImboBaseHero::GetImboPlayerController() const
{
	return CastChecked<AImboBaseHeroController>(Controller, ECastCheckedType::NullAllowed);
}

USpringArmComponent* AImboBaseHero::GetImboPlayerSpringArmComponent() const
{
	return SpringArm;
}

UCameraComponent* AImboBaseHero::GetImboPlayerCameraComponent() const
{
	return Camera;
}
