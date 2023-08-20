#include "System/ImboGameInstance.h"

UImboGameInstance::UImboGameInstance()
{
}

void UImboGameInstance::Init()
{
	Super::Init();

	GameDataSupervisor.LoadSynchronous();
}

void UImboGameInstance::Shutdown()
{
	Super::Shutdown();
}

void UImboGameInstance::StartGameInstance()
{
	Super::StartGameInstance();
}

UImboGameDataSupervisor* UImboGameInstance::GetGameDataSupervisor()
{
	return GameDataSupervisor.Get();
}

#if WITH_EDITOR
FGameInstancePIEResult UImboGameInstance::InitializeForPlayInEditor(int32 PIEInstanceIndex, const FGameInstancePIEParameters& Params)
{
	return Super::InitializeForPlayInEditor(PIEInstanceIndex, Params);
}

FGameInstancePIEResult UImboGameInstance::StartPlayInEditorGameInstance(ULocalPlayer* LocalPlayer, const FGameInstancePIEParameters& Params)
{
	return Super::StartPlayInEditorGameInstance(LocalPlayer, Params);
}
#endif