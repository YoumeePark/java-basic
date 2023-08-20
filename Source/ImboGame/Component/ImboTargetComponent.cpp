#include "Component/ImboTargetComponent.h"
#include "Global.h"

#include "Sound/SoundCue.h"

#include "Character/ImboBaseCharacter.h"
#include "Character/Hero/ImboBaseHero.h"
#include "Character/Enemy/ImboBaseEnemy.h"
#include "Controller/ImboBaseHeroController.h"

UImboTargetComponent::UImboTargetComponent()
{
	PrimaryComponentTick.bCanEverTick = true;

	ImboHelpers::GetAsset<USoundCue>(&TargetingSound, TEXT("/Script/Engine.SoundCue'/Game/Asset/Sound/TargetSelect_Cue.TargetSelect_Cue'"));
}

void UImboTargetComponent::BeginPlay()
{
	Super::BeginPlay();

	OwnerCharacter = Cast<AImboBaseHero>(GetOwner());
}

void UImboTargetComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

}

void UImboTargetComponent::EndTargeting()
{
	if (CurrentTarget != nullptr)
	{
		IImboTargetAgentInterface* temp = Cast<IImboTargetAgentInterface>(CurrentTarget.Get());
		if(temp != nullptr)
		{
			temp->SetHiddenInGameTargetDecal(true);
			CurrentTarget = nullptr;
			IsTab = false;
		}
		else
		{
			//TODO : ItemTargetAgentInterface로 사용 예정?
		}
	}
	else
		return;
}

void UImboTargetComponent::StartTabTargeting()
{
	if(IsTab)
		ChangeTabTarget();

	SetTabTraceTarget();
	ChangeTabTarget();
}

void UImboTargetComponent::ChangeTabTarget()
{
	if(TraceTargets.IsEmpty() != true)
	{
		AImboBaseEnemy* nearestEnemy = nullptr;
		FVector ownerLocation = OwnerCharacter->GetActorLocation();

		AImboBaseEnemy* currentTarget = nullptr;
		if (CurrentTarget != nullptr)
			currentTarget = Cast<AImboBaseEnemy>(CurrentTarget);

		float currentTargetDistance = 0;
		float newTargetDistance = 0;
		for (AImboBaseEnemy* newTarget : TraceTargets)
		{
			if (CurrentTarget == nullptr)
			{
				CurrentTarget = newTarget;
				newTarget->SetHiddenInGameTargetDecal(false);
				UGameplayStatics::PlaySound2D(GetWorld(), TargetingSound.Get());

				return;
			}
			else
			{
				currentTargetDistance = FVector::Dist(OwnerCharacter->GetActorLocation(), currentTarget->GetActorLocation());
				newTargetDistance = FVector::Dist(OwnerCharacter->GetActorLocation(), newTarget->GetActorLocation());

				if (newTargetDistance > currentTargetDistance)
				{
					currentTarget->SetHiddenInGameTargetDecal(true);

					CurrentTarget = newTarget;
					newTarget->SetHiddenInGameTargetDecal(false);
					UGameplayStatics::PlaySound2D(GetWorld(), TargetingSound.Get());

					return;
				}
			}
		}
	}
}

void UImboTargetComponent::NextChangeTabTarget()
{
	
}

void UImboTargetComponent::StartClickTargeting()
{
	SetClickTraceTarget();
}

void UImboTargetComponent::SetClickTraceTarget()
{
	AImboBaseHeroController* heroController = OwnerCharacter->GetImboPlayerController();

	TArray<TEnumAsByte<EObjectTypeQuery>> tempObjectTypes;
	tempObjectTypes.Add(EObjectTypeQuery::ObjectTypeQuery3); //Pawn

	FHitResult hitResult;
	heroController->GetHitResultUnderCursorForObjects(tempObjectTypes, false, hitResult);

	if(hitResult.IsValidBlockingHit())
	{
		IImboTargetAgentInterface* temp = CastChecked<IImboTargetAgentInterface>(hitResult.GetActor());
		if(temp == nullptr)
			return;

		//TODO : Item까지 체크할 것이면 ItemAgentInterface를 만들어서 체크.

		if (CurrentTarget == nullptr) //게임 시작하고 처음 찍었나?, 아니면 ESC 눌러서 타겟 빠진 상태로 찍었나?
		{
			CurrentTarget = hitResult.GetActor();
			temp->SetHiddenInGameTargetDecal(false);
			UGameplayStatics::PlaySound2D(GetWorld(), TargetingSound.Get());
		}
		else if(CurrentTarget == hitResult.GetActor())
		{
			return;
		}
		else
		{
			//이전
			Cast<IImboTargetAgentInterface>(CurrentTarget.Get())->SetHiddenInGameTargetDecal(true);

			//새거
			CurrentTarget = hitResult.GetActor();
			temp->SetHiddenInGameTargetDecal(false);
			UGameplayStatics::PlaySound2D(GetWorld(), TargetingSound.Get());
		}
	}
}

/**
 * @brief Tab 키로 수행하는 Enemy 검출 타겟팅
 * @return	
 */
void UImboTargetComponent::SetTabTraceTarget()
{
	//FVector start = OwnerCharacter->GetActorLocation();
	//FVector end = FVector(start.X, start.Y, start.Z + 1);

	//TArray<AActor*> ignoreActors;
	//ignoreActors.Add(OwnerCharacter);

	//TArray<FHitResult> hitResults;

	//Debug = EDrawDebugTrace::ForDuration;
	//bool bTraceResult = UKismetSystemLibrary::SphereTraceMultiByProfile(GetWorld(), start, end, TraceRadius, "Pawn", false, ignoreActors, Debug, hitResults, true, FLinearColor::Red, FLinearColor::Green, 1.0f);
	//
	//if(bTraceResult == true)
	//{
	//	for (const FHitResult& result : hitResults)
	//	{
	//		if (result.GetActor()->GetClass() == OwnerCharacter->GetClass())
	//			continue;

	//		//TODO : 230818, 여기서부터 시작 
	//		AActor* character = Cast<AActor>(result.GetActor());

	//		if (!!character)
	//			TraceTargets.AddUnique(character);
	//	}

	//	return true;
	//}
	//else
	//{
	//	return false;
	//}


	const FVector myLocation = OwnerCharacter->GetActorLocation();
	TArray<FOverlapResult> overlappedActors;

	GetWorld()->OverlapMultiByObjectType(
		overlappedActors,
		myLocation,
		FQuat::Identity,
		FCollisionObjectQueryParams(ECollisionChannel::ECC_Pawn),
		FCollisionShape::MakeSphere(TraceRadius)
	);

	if(overlappedActors.IsEmpty() != true)
	{
		for (const FOverlapResult& Actor : overlappedActors)
		{
			if (Actor.GetActor() != nullptr)
			{
				if (Actor.GetActor()->GetClass() == OwnerCharacter.GetClass())
					continue;

				TraceTargets.AddUnique(Cast<AImboBaseEnemy>(Actor.GetActor()));
			}
		}

		IsTab = true;
	}
	else
	{
		IsTab = false;
	}
}