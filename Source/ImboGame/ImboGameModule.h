#pragma once

#include "Modules/ModuleManager.h"

class FImboGameModule : public FDefaultGameModuleImpl
{
public:
	virtual void StartupModule() override;
	virtual void ShutdownModule() override;
};