#pragma once

#include "CoreMinimal.h"
#include "UObject/ConstructorHelpers.h"
#include "Components/ActorComponent.h"
#include "Engine/World.h"

class IMBOGAME_API ImboHelpers
{
public:
	/* Asset */
	template<typename T>
	static void GetAsset(T** OutObject, FString InPath);

	template<typename T>
	static void GetAsset(TObjectPtr<T>* OutObject, FString InPath);

	template<typename T>
	static void GetAssetDynamic(T** OutObject, FString InPath);


public:
	/* Component */
	template<typename T>
	static T* GetComponent(AActor* InActor);

	template<typename T>
	static void CreateComponent(AActor* InActor, T** InComponent, FName InName, USceneComponent* InParent = nullptr);

	template<typename T>
	static void CreateComponent(AActor* InActor, TObjectPtr<T>* InComponent, FName InName, TObjectPtr<USceneComponent> InParent = nullptr);

	template<typename T>
	static void CreateActorComponent(AActor* InActor, T** InComponent, FName InName);

	template<typename T>
	static void CreateActorComponent(AActor* InActor, TObjectPtr<T>* InComponent, FName InName);

	template <typename T>
	static T* CreateRunTimeActorComponent(AActor* InActor, T** InComponent, FName InName);

	template <typename T>
	static T* CreateRunTimeActorComponent(AActor* InActor, TObjectPtr<T>* InComponent, FName InName);


public:
	/* Actor */
	template<typename T>
	static void FindActors(class UWorld* InWorld, TArray<T*>& OutActors);


public:
	/* Class */
	template<typename T>
	static void GetClass(TSubclassOf<T>* OutClass, FString InPath);
};

#include "ImboHelpers.inl"