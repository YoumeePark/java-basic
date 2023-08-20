#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "GameData/ImboGameDataSupervisor.h"
#include "ImboGameInstance.generated.h"

UCLASS(Blueprintable)
class IMBOGAME_API UImboGameInstance : public UGameInstance
{
	GENERATED_BODY()

public:
	/* Default Function */
	UImboGameInstance();
	virtual void Init() override;
	virtual void Shutdown() override;
	virtual void StartGameInstance() override;


public:
	/* Getter */
	UFUNCTION(Category="Imbo|System")
		UImboGameDataSupervisor* GetGameDataSupervisor();


private:
	/* Editor Debug Function */
#if WITH_EDITOR
	virtual FGameInstancePIEResult InitializeForPlayInEditor(int32 PIEInstanceIndex, const FGameInstancePIEParameters& Params) override;
	virtual FGameInstancePIEResult StartPlayInEditorGameInstance(ULocalPlayer* LocalPlayer, const FGameInstancePIEParameters& Params) override;
#endif


private:
	/* Default Member */
	UPROPERTY(EditDefaultsOnly, Category = "Imbo|GameData")
		TSoftObjectPtr<UImboGameDataSupervisor> GameDataSupervisor;
};
