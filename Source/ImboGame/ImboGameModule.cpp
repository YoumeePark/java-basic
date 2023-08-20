#include "ImboGameModule.h"
#include "Modules/ModuleManager.h"

IMPLEMENT_PRIMARY_GAME_MODULE(FImboGameModule, ImboGame, "ImboGame"); //Set Module Name

void FImboGameModule::StartupModule()
{
	FDefaultGameModuleImpl::StartupModule();
}

void FImboGameModule::ShutdownModule()
{
	FDefaultGameModuleImpl::ShutdownModule();
}
