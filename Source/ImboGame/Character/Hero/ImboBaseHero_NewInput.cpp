#include "ImboBaseHero_NewInput.h"
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

AImboBaseHero_NewInput::AImboBaseHero_NewInput()
{
	/* Set Default Pawn */
	PrimaryActorTick.bCanEverTick = true;
	bUseControllerRotationPitch = false; //Don't rotate when the controller rotates. Let that just affect the camera.
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;
	

	/* Team */
	CurrentTeamID = 0;


	/* Get Input Mapping Assets */
	//ImboHelpers::GetAsset<UInputMappingContext>(&DefaultMappingContext, TEXT("/Script/EnhancedInput.InputMappingContext'/Game/Blueprint/Character/Input/MC_BaseInputMapping.MC_BaseInputMapping'"));
	//ImboHelpers::GetAsset<UInputAction>(&InputActions.LookAction, TEXT("/Script/EnhancedInput.InputAction'/Game/Blueprint/Character/Input/IA_Look.IA_Look'"));
	//ImboHelpers::GetAsset<UInputAction>(&InputActions.MoveAction, TEXT("/Script/EnhancedInput.InputAction'/Game/Blueprint/Character/Input/IA_Move.IA_Move'"));
	//ImboHelpers::GetAsset<UInputAction>(&InputActions.JumpAction, TEXT("/Script/EnhancedInput.InputAction'/Game/Blueprint/Character/Input/IA_Jump.IA_Jump'"));
	//ImboHelpers::GetAsset<UInputAction>(&InputActions.MouseLeft, TEXT("/Script/EnhancedInput.InputAction'/Game/Blueprint/Character/Input/IA_MouseLeft.IA_MouseLeft'"));
	//ImboHelpers::GetAsset<UInputAction>(&InputActions.MouseRight, TEXT("/Script/EnhancedInput.InputAction'/Game/Blueprint/Character/Input/IA_MouseRight.IA_MouseRight'"));
	//ImboHelpers::GetAsset<UInputAction>(&InputActions.MouseWheel, TEXT("/Script/EnhancedInput.InputAction'/Game/Blueprint/Character/Input/IA_MouseWheel.IA_MouseWheel'"));
	//ImboHelpers::GetAsset<UInputAction>(&InputActions.ESC, TEXT("/Script/EnhancedInput.InputAction'/Game/Blueprint/Character/Input/IA_ESC.IA_ESC'"));
	//ImboHelpers::GetAsset<UInputAction>(&InputActions.Tab, TEXT("/Script/EnhancedInput.InputAction'/Game/Blueprint/Character/Input/IA_Tab.IA_Tab'"));
	
	
	/* Create Default Component */
	ImboHelpers::CreateComponent<USpringArmComponent>(this, &SpringArm, TEXT("SpringArm"), GetCapsuleComponent());
	ImboHelpers::CreateComponent<UCameraComponent>(this, &Camera, TEXT("Camera"), SpringArm);


	/* Set SpringArm & Camera */
	SpringArm->SetRelativeLocation(FVector(0, 0, 50));
	SpringArm->bUsePawnControlRotation = true;
	SpringArm->TargetArmLength = 1500.f;
	SpringArm->bDoCollisionTest = true;
	SpringArm->bEnableCameraLag = true;
	Camera->bUsePawnControlRotation = false; //Camera does not rotate relative to arm


	/* Configure Character Movement */
	GetCharacterMovement()->bOrientRotationToMovement = true; //Rotate Character to Controller
}

void AImboBaseHero_NewInput::BeginPlay()
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

void AImboBaseHero_NewInput::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AImboBaseHero_NewInput::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	check(PlayerInputComponent);	
	Super::SetupPlayerInputComponent(PlayerInputComponent);


	if (UEnhancedInputComponent* EnhancedInputComponent = CastChecked<UEnhancedInputComponent>(PlayerInputComponent))
	{
		EnhancedInputComponent->BindAction(WS, ETriggerEvent::Triggered, this, &AImboBaseHero_NewInput::OnWS);
		EnhancedInputComponent->BindAction(DA, ETriggerEvent::Triggered, this, &AImboBaseHero_NewInput::OnDA);

		//EnhancedInputComponent->BindAction(InputActions.LookAction, ETriggerEvent::Triggered, this, &AImboBaseHero_NewInput::OnLook);
		//EnhancedInputComponent->BindAction(InputActions.MoveAction, ETriggerEvent::Triggered, this, &AImboBaseHero_NewInput::OnMove);
		//
		//EnhancedInputComponent->BindAction(InputActions.JumpAction, ETriggerEvent::Triggered, this, &ACharacter::Jump); //used built-in function
		//EnhancedInputComponent->BindAction(InputActions.JumpAction, ETriggerEvent::Completed, this, &ACharacter::StopJumping); //used built-in function
		//
		EnhancedInputComponent->BindAction(MouseLeft, ETriggerEvent::Started, this, &AImboBaseHero_NewInput::OnClickMouseLeft);
		EnhancedInputComponent->BindAction(MouseLeft, ETriggerEvent::Completed, this, &AImboBaseHero_NewInput::OnUnClickMouseLeft);
		EnhancedInputComponent->BindAction(MouseRight, ETriggerEvent::Started, this, &AImboBaseHero_NewInput::OnClickMouseRight);
		EnhancedInputComponent->BindAction(MouseRight, ETriggerEvent::Completed, this, &AImboBaseHero_NewInput::OnUnClickMouseRight);
		//
		//EnhancedInputComponent->BindAction(InputActions.MouseWheel, ETriggerEvent::Triggered, this, &AImboBaseHero_NewInput::OnMouseWheel);
		//
		//EnhancedInputComponent->BindAction(InputActions.ESC, ETriggerEvent::Started, this, &AImboBaseHero_NewInput::OnESC);
		//EnhancedInputComponent->BindAction(InputActions.Tab, ETriggerEvent::Started, this, &AImboBaseHero_NewInput::OnTab);
	}
}

AImboBaseHeroController* AImboBaseHero_NewInput::GetImboPlayerController() const
{
	return Cast<AImboBaseHeroController>(Controller);
}

void AImboBaseHero_NewInput::OnMove(const FInputActionValue& Value)
{
	if (Controller != nullptr)
	{
		const FVector2D movementVector = Value.Get<FVector2D>();

		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);

		const FVector ForwardDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
		const FVector RightDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);

		AddMovementInput(ForwardDirection, movementVector.Y);
		AddMovementInput(RightDirection, movementVector.X);
	}
}

void AImboBaseHero_NewInput::OnLook(const FInputActionValue& Value)
{
	if (bClickMouseLeft || bClickMouseRight)
	{
		// input is a Vector2D
		FVector2D lookAxisVector = Value.Get<FVector2D>();

		if (Controller != nullptr)
		{
			// add yaw and pitch input to controller
			AddControllerYawInput(lookAxisVector.X);
			AddControllerPitchInput(lookAxisVector.Y * -1);
		}
	}
}

void AImboBaseHero_NewInput::OnClickMouseLeft(const FInputActionValue& Value)
{
	auto inputValue = Value.Get<bool>();
	bClickMouseLeft = inputValue;
	GetImboPlayerController()->GetMousePosition(DefaultMouseX, DefaultMouseY);
}

void AImboBaseHero_NewInput::OnUnClickMouseLeft()
{
	bClickMouseLeft = false;

	APlayerController* tempController = GetImboPlayerController();
	tempController->SetMouseLocation(DefaultMouseX, DefaultMouseY);
	tempController->SetShowMouseCursor(true);
	UWidgetBlueprintLibrary::SetInputMode_GameAndUIEx(GetImboPlayerController());
	UWidgetBlueprintLibrary::SetFocusToGameViewport();
}

void AImboBaseHero_NewInput::OnClickMouseRight(const FInputActionValue& Value)
{
	auto inputValue = Value.Get<bool>();
	bClickMouseRight = inputValue;
	GetImboPlayerController()->GetMousePosition(DefaultMouseX, DefaultMouseY);
}

void AImboBaseHero_NewInput::OnUnClickMouseRight()
{
	bClickMouseRight = false;

	APlayerController* tempController = GetImboPlayerController();
	tempController->SetMouseLocation(DefaultMouseX, DefaultMouseY);
	tempController->SetShowMouseCursor(true);
	UWidgetBlueprintLibrary::SetInputMode_GameAndUIEx(GetImboPlayerController());
	UWidgetBlueprintLibrary::SetFocusToGameViewport();
}

void AImboBaseHero_NewInput::OnMouseWheel(const FInputActionValue& Value)
{
	auto inputValue = Value.Get<float>();
	SpringArm->TargetArmLength += (ZoomSpeed * inputValue); // * GetWorld()->GetDeltaSeconds());
	SpringArm->TargetArmLength = FMath::Clamp<float>(SpringArm->TargetArmLength, MinTargetArmLength, MaxTargetArmLength);
}

void AImboBaseHero_NewInput::OnESC(const FInputActionValue& Value)
{
	auto inputValue = Value.Get<bool>();
	ImboLog::Print(inputValue);
}

void AImboBaseHero_NewInput::OnTab(const FInputActionValue& Value)
{
	ImboLog::Print("Tab");
}

void AImboBaseHero_NewInput::OnWS(const FInputActionValue& Value)
{
	const float inputAxisValue = Value.Get<float>();
	ImboLog::Print(inputAxisValue);

	if (Controller != nullptr)
	{
		//const float inputAxisValue = Value.Get<float>();

		if (bClickMouseRight)
		{
			ImboLog::Print("W Right");

			const FRotator Rotation = Controller->GetControlRotation();
			const FRotator YawRotation(0, Rotation.Yaw, 0);
			const FVector forwardDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);

			AddMovementInput(forwardDirection, inputAxisValue);


			// 현재 캐릭터의 회전 값을 얻어옵니다.
			const FRotator CharacterRotation = GetActorRotation();
			
			// 캐릭터 회전 값의 yaw 값을 카메라 회전 값에 적용합니다.
			FRotator NewCameraRotation = Controller->GetControlRotation();
			NewCameraRotation.Yaw = CharacterRotation.Yaw;
			
			Controller->SetControlRotation(NewCameraRotation);

			//// 새로운 카메라 회전 값을 설정합니다.
			//UCameraComponent* CameraComponent = Cast<UCameraComponent>(GetComponentByClass(UCameraComponent::StaticClass()));
			//if (CameraComponent)
			//{
			//	CameraComponent->SetWorldRotation(NewCameraRotation);
			//}
		}
		else if (bClickMouseLeft)
		{
			
		}
		else
		{
			
		}
	}
}

void AImboBaseHero_NewInput::OnDA(const FInputActionValue& Value)
{
	if(Controller != nullptr)
	{
		const float inputAxisValue = Value.Get<float>();

		if (bClickMouseRight)
		{
			const FRotator Rotation = Controller->GetControlRotation();
			const FRotator YawRotation(0, Rotation.Yaw, 0);
			const FVector rightDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);

			AddMovementInput(rightDirection, inputAxisValue);
		}
		else if (bClickMouseLeft)
		{
			float rotationAmount = inputAxisValue * RotationRate * GetWorld()->GetDeltaSeconds();
			FRotator rotationDelta(0.0f, rotationAmount, 0.0f);
			FRotator newRotation = GetActorRotation() + rotationDelta;

			SetActorRotation(newRotation);
		}
		else
		{
			AddControllerYawInput(inputAxisValue);
		}
	}
}

USpringArmComponent* AImboBaseHero_NewInput::GetImboPlayerSpringArmComponent() const
{
	return SpringArm;
}

UCameraComponent* AImboBaseHero_NewInput::GetImboPlayerCameraComponent() const
{
	return Camera;
}
