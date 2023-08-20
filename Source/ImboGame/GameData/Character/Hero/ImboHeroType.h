#pragma once

#include "CoreMinimal.h"

UENUM(BlueprintType)
enum class EImboHeroType : uint8
{
	None = 0,

	/* Tank */
	Paladin = 1,
	Warrior = 2,

	/* Dealer */
	DeathKnight = 9,
	Rogue = 3,
	Ranger = 4,
	Druid = 5,
	Warlock = 6,
	FireMage = 7,
	IceMage = 8,

	/* Healer */
	Priest = 10
};
