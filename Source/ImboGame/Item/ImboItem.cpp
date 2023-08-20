#include "Item/ImboItem.h"

AImboItem::AImboItem()
{
	PrimaryActorTick.bCanEverTick = true;

	OwnerCharacter = nullptr;
	ItemType = EImboItemType::None;
	Equip = nullptr;
	UnEquip = nullptr;
}

void AImboItem::BeginPlay()
{
	Super::BeginPlay();
	
}

void AImboItem::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}