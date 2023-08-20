#include "Animation/ImboBaseAnimInstance.h"
#include "Global.h"
#include "GameFramework/Character.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "KismetAnimationLibrary.h" //Module : AnimGraphRuntime, Function : CalculateDirection

UImboBaseAnimInstance::UImboBaseAnimInstance()
{
}

void UImboBaseAnimInstance::NativeBeginPlay()
{
	Super::NativeBeginPlay();


	/* Set Default */
	bUseMultiThreadedAnimationUpdate = false;


	/* Set Owner & MovementComponent */
	Owner = CastChecked<ACharacter>(TryGetPawnOwner());
	CheckNull(Owner);
	OwnerMoveComp = CastChecked<UCharacterMovementComponent>(Owner->GetMovementComponent());
	CheckNull(OwnerMoveComp);
}

void UImboBaseAnimInstance::NativeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeUpdateAnimation(DeltaSeconds);


	/* Movement */
	CheckNull(Owner);
	Velocity = OwnerMoveComp->Velocity;
	GroundSpeed = UKismetMathLibrary::VSizeXY(Velocity);
	Direction = UKismetAnimationLibrary::CalculateDirection(Owner->GetVelocity(), Owner->GetActorRotation());


	/* Set Control Rotation */
	FRotator deltaRotation = UKismetMathLibrary::NormalizedDeltaRotator(Owner->GetControlRotation(), Owner->GetActorRotation());
	Pitch = deltaRotation.Pitch;
	Yaw = deltaRotation.Yaw;


	/* State */
	FVector tempAccelSpeed = OwnerMoveComp->GetCurrentAcceleration();
	bCanMove = ((GroundSpeed > 3) && (tempAccelSpeed != FVector(0, 0, 0))) ? true : false;
	bInAir = OwnerMoveComp->IsFalling();
}

ACharacter* UImboBaseAnimInstance::GetOwnerCharacter() const
{
	return Owner;
}

UCharacterMovementComponent* UImboBaseAnimInstance::GetOwnerCharacterMovementComponent() const
{
	return OwnerMoveComp;
}