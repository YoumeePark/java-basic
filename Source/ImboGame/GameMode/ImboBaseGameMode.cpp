#include "GameMode/ImboBaseGameMode.h"
#include "Global.h"

AImboBaseGameMode::AImboBaseGameMode()
{
	
}

UImboGameInstance* AImboBaseGameMode::GetImboGameInstance()
{
	if(CurrentGameInstance == false)
	{
		CurrentGameInstance = Cast<UImboGameInstance>(GetWorld()->GetGameInstance());
	}
	return CurrentGameInstance;
}

const float AImboBaseGameMode::GetFPS() const
{
	const float fps = (1.0f / GetWorld()->GetDeltaSeconds());
	return fps;
}
