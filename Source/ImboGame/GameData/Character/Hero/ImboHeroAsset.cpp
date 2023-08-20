#include "GameData/Character/Hero/ImboHeroAsset.h"

TObjectPtr<UImboHeroData> UImboHeroAsset::GetHeroData(FGameplayTag heroTag)
{
	if(HeroDatas[heroTag].IsValid())
		return HeroDatas[heroTag].LoadSynchronous();

	return HeroDatas[heroTag].Get();
}
