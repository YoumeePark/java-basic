#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "ImboBaseAnimInstance.generated.h"

class ACharacter;
class UCharacterMovementComponent;

UCLASS()
class IMBOGAME_API UImboBaseAnimInstance : public UAnimInstance
{
	GENERATED_BODY()


/* Default */
public:
	UImboBaseAnimInstance();
	virtual void NativeBeginPlay() override;
	virtual void NativeUpdateAnimation(float DeltaSeconds) override;
	

/* Blueprint Callable Function */
public:
	UFUNCTION(BlueprintCallable, meta=(BlueprintThreadSafe), Category="Imbo|Animation")
		FORCEINLINE ACharacter* GetOwnerCharacter() const;

	UFUNCTION(BlueprintCallable, meta=(BlueprintThreadSafe), Category = "Imbo|Animation")
		FORCEINLINE UCharacterMovementComponent* GetOwnerCharacterMovementComponent() const;


/* Movement */
public:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Imbo|Movement")
		float Direction;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category ="Imbo|Movement")
		FVector Velocity;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Imbo|Movement")
		float GroundSpeed;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Imbo|Movement")
		float Pitch;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Imbo|Movement")
		float Yaw;


/* Statement */
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Imbo|Statement")
		bool bCanMove;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Imbo|Statement")
		bool bInAir;


/* Owner */
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Imbo|Statement")
		ACharacter* Owner;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Imbo|Statement")
		UCharacterMovementComponent* OwnerMoveComp;
};
