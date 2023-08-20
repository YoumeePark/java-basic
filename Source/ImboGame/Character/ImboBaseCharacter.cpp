#include "Character/ImboBaseCharacter.h"
#include "Global.h"

#include "Character/ImboBaseCharacter.h"
#include "Controller/ImboBaseHeroController.h"
#include "Character/Hero/ImboBaseHero.h"
#include "Character/Enemy/ImboBaseEnemy.h"

#include "Components/CapsuleComponent.h"
#include "GameFramework/PlayerState.h"
#include "Materials/MaterialInstanceConstant.h"

AImboBaseCharacter::AImboBaseCharacter()
{
	PrimaryActorTick.bCanEverTick = true;

	
	/* Component */
	ImboHelpers::CreateComponent<UDecalComponent>(this, &TargetDecal, TEXT("TargetDecal"), GetCapsuleComponent());


	/* Set Mesh */
	USkeletalMeshComponent* tempMeshComp = GetMesh();
	USkeletalMesh* tempMesh;
	ImboHelpers::GetAsset<USkeletalMesh>(&tempMesh, TEXT("/Script/Engine.SkeletalMesh'/Game/Asset/Characters/Mannequins/Meshes/SKM_Manny.SKM_Manny'"));
	tempMeshComp->SetSkeletalMesh(tempMesh);
	tempMeshComp->SetRelativeLocation(FVector(0, 0, -90));
	tempMeshComp->SetRelativeRotation(FRotator(0, -90, 0));


	/* Decal - TargetDecal */
	GetCapsuleComponent()->SetCollisionProfileName("ImboDefaultObject");

	GetMesh()->SetReceivesDecals(false);
	GetCapsuleComponent()->SetReceivesDecals(false);

	UMaterialInstanceConstant* tempTargetSelectDecal;
	ImboHelpers::GetAsset<UMaterialInstanceConstant>(&tempTargetSelectDecal, "/Script/Engine.MaterialInstanceConstant'/Game/Asset/Decal/TargetSelect/geometry_DID_100985.geometry_DID_100985'");
	TargetDecal->SetDecalMaterial(tempTargetSelectDecal);

	TargetDecal->SetRelativeLocation(FVector(0, 0, -154.085516));
	TargetDecal->SetRelativeRotation(FRotator(90, 0, 0));
	TargetDecal->DecalSize = FVector(100, 40, 40);
	TargetDecal->SetHiddenInGame(true);
}

void AImboBaseCharacter::BeginPlay()
{
	Super::BeginPlay();
	
}

void AImboBaseCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AImboBaseCharacter::NotifyActorOnClicked(FKey ButtonPressed)
{
	Super::NotifyActorOnClicked(ButtonPressed);

}

void AImboBaseCharacter::SetHiddenInGameTargetDecal(bool hiddenInGame)
{
	TargetDecal->SetHiddenInGame(hiddenInGame);
}
