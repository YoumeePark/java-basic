#include "Controller/ImboBaseHeroController.h"
#include "Global.h"
#include "Blueprint/WidgetBlueprintLibrary.h"
#include "Engine/GameViewportClient.h"

AImboBaseHeroController::AImboBaseHeroController()
{
	bEnableClickEvents = true;
}

void AImboBaseHeroController::BeginPlay()
{
	Super::BeginPlay();

	SetShowMouseCursor(true);
	UWidgetBlueprintLibrary::SetInputMode_GameAndUIEx(this);
}

void AImboBaseHeroController::PlayerTick(float DeltaTime)
{
	Super::PlayerTick(DeltaTime);

}

void AImboBaseHeroController::SetupInputComponent()
{
	Super::SetupInputComponent();
	
}
