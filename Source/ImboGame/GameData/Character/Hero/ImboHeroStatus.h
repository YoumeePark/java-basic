#pragma once

#include "CoreMinimal.h"
#include "ImboHeroStatus.generated.h"

USTRUCT(BlueprintType)
struct FImboHeroStatus
{
	GENERATED_BODY()

public:
	/* Main */
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
		int32 Strength;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
		int32 Agility;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
		int32 Intelligence;


	/* Hero Health & Mana */
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
		int32 Health;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
		int32 Mana;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
		int32 Stamina;


	/* Sub : Attack */
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
		int32 AttackDamage;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
		int32 AttackDefense;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
		float AttackCriticalRate;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
		float AttackCriticalDamage;


	/* Sub : Magic */
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
		int32 MagicDamage;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
		int32 MagicDefense;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
		float MagicCriticalRate;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
		float MagicCriticalDamage;


	/* Sub2 */
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
		float EvasionRate;
};
