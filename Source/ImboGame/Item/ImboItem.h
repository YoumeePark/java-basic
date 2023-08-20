#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Character\Hero/ImboBaseHero.h"
#include "ImboItemType.h"
#include "ImboItem.generated.h"

UCLASS(BlueprintType)
class IMBOGAME_API AImboItem : public AActor
{
	GENERATED_BODY()
	
public:	
	AImboItem();
	virtual void Tick(float DeltaTime) override;


protected:
	virtual void BeginPlay() override;


protected:
	UPROPERTY(VisibleDefaultsOnly, Category = "WopCharacter")
		AImboBaseHero* OwnerCharacter;

	UPROPERTY(EditAnywhere, Category = "Type")
		EImboItemType ItemType;

	UPROPERTY(EditAnywhere, Category = "Montage")
		UAnimMontage* Equip;

	UPROPERTY(EditAnywhere, Category = "Montage")
		UAnimMontage* UnEquip;
};
