#include "Character/Enemy/ImboBaseEnemy.h"
#include "Global.h"

AImboBaseEnemy::AImboBaseEnemy()
{
	PrimaryActorTick.bCanEverTick = true;

	/* Team */
	CurrentTeamID = 1;
}

void AImboBaseEnemy::BeginPlay()
{
	Super::BeginPlay();
	
}

void AImboBaseEnemy::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AImboBaseEnemy::SetHiddenInGameTargetDecal(bool active)
{
	Super::SetHiddenInGameTargetDecal(active);
}
