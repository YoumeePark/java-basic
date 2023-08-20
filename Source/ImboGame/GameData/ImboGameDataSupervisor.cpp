#include "GameData/ImboGameDataSupervisor.h"

UImboCharacterAsset* UImboGameDataSupervisor::GetCharacter() const
{
	if (Character.IsValid() == false)
	{
		return Character.LoadSynchronous();
	}

	return Character.Get();
}
