/**
 * @brief 컴파일 타임 애셋 참조
 * @tparam T
 * @param OutObject
 * @param InPath
 */
template <typename T>
void ImboHelpers::GetAsset(T** OutObject, FString InPath)
{
	ConstructorHelpers::FObjectFinder<T> asset(*InPath);
	verifyf(asset.Succeeded(), L"asset.Succeeded()");

	*OutObject = asset.Object;
}


/**
 * @brief 컴파일 타임 애셋 참조 (TObjectrPtr 사용시)
 * @tparam T 
 * @param OutObject 
 * @param InPath 
 */
template<typename T>
void ImboHelpers::GetAsset(TObjectPtr<T>* OutObject, FString InPath)
{
	ConstructorHelpers::FObjectFinder<T> asset(*InPath);
	verifyf(asset.Succeeded(), L"asset.Succeeded()");

	*OutObject = asset.Object;
}

/**
 * @brief 런타임 애셋 참조
 * @tparam T
 * @param OutObject
 * @param InPath
 */
template <typename T>
void ImboHelpers::GetAssetDynamic(T** OutObject, FString InPath)
{
	T* obj = Cast<T>(StaticLoadObject(T::StaticClass(), nullptr, *InPath));
	verifyf(!!obj, L"!!asset");

	*OutObject = obj;
}

/**
 * @brief 컴파일 타임 컴포넌트 생성
 * @tparam T
 * @param InActor
 * @param InComponent
 * @param InName
 * @param InParent
 */
template <typename T>
void ImboHelpers::CreateComponent(AActor* InActor, T** InComponent, FName InName, USceneComponent* InParent)
{
	*InComponent = InActor->CreateDefaultSubobject<T>(InName);

	if (!!InParent)
	{
		(*InComponent)->SetupAttachment(InParent);
		return;
	}

	InActor->SetRootComponent((*InComponent));
}

/**
 * @brief 컴파일 타임 컴포넌트 생성 (TObjectrPtr 사용시)
 * @tparam T
 * @param InActor
 * @param InComponent
 * @param InName
 * @param InParent
 */
template <typename T>
void ImboHelpers::CreateComponent(AActor* InActor, TObjectPtr<T>* InComponent, FName InName,
                                 TObjectPtr<USceneComponent> InParent)
{
	*InComponent = InActor->CreateDefaultSubobject<T>(InName);

	if (InParent != nullptr)
	{
		(*InComponent)->SetupAttachment(InParent);
		return;
	}

	InActor->SetRootComponent((*InComponent));
}

/**
 * @brief 컴파일 타임 액터 컴포넌트 생성
 * @tparam T
 * @param InActor
 * @param InComponent
 * @param InName
 */
template <typename T>
void ImboHelpers::CreateActorComponent(AActor* InActor, T** InComponent, FName InName)
{
	*InComponent = InActor->CreateDefaultSubobject<T>(InName);
}

template <typename T>
T* ImboHelpers::GetComponent(AActor* InActor)
{
	return Cast<T>(InActor->GetComponentByClass(T::StaticClass()));
}

/**
 * @brief 컴파일 타임 액터 컴포넌트 생성 (TObject 사용시)
 * @tparam T
 * @param InActor
 * @param InComponent
 * @param InName
 */
template <typename T>
void ImboHelpers::CreateActorComponent(AActor* InActor, TObjectPtr<T>* InComponent, FName InName)
{
	*InComponent = InActor->CreateDefaultSubobject<T>(InName);
}

/**
 * @brief 런타임 컴포넌트 생성
 * @tparam T
 * @param InActor
 * @param InComponent
 * @param InName
 * @return
 */
template <typename T>
T* ImboHelpers::CreateRunTimeActorComponent(AActor* InActor, T** InComponent, FName InName)
{
	*InComponent = NewObject<T>(InActor, T::StaticClass(), InName);
	if (*InComponent)
	{
		return *InComponent;
	}

	return nullptr;
}

/**
 * @brief 런타임 컴포넌트 생성 (TObjectPtr 사용시)
 * @tparam T
 * @param InActor
 * @param InComponent
 * @param InName
 * @return
 */
template <typename T>
T* ImboHelpers::CreateRunTimeActorComponent(AActor* InActor, TObjectPtr<T>* InComponent, FName InName)
{
	*InComponent = NewObject<T>(InActor, T::StaticClass(), InName);
	if (*InComponent)
	{
		return *InComponent;
	}

	return nullptr;
}

/**
 * @brief 런타임 액터 검색
 * @tparam T
 * @param InWorld
 * @param OutActors
 */
template <typename T>
void ImboHelpers::FindActors(class UWorld* InWorld, TArray<T*>& OutActors)
{
	OutActors.Empty();

	TArray<AActor*> actors;
	UGameplayStatics::GetAllActorsOfClass(InWorld, T::StaticClass(), actors);

	for (AActor* actor : actors)
	{
		OutActors.Add(Cast<T>(actor));
	}
}

/**
 * @brief 컴파일 타임 클래스 검색
 * @tparam T
 * @param OutClass
 * @param InPath
 */
template <typename T>
void ImboHelpers::GetClass(TSubclassOf<T>* OutClass, FString InPath)
{
	ConstructorHelpers::FClassFinder<T> asset(*InPath);
	verifyf(asset.Succeeded(), L"asset.Succeeded()");

	*OutClass = asset.Class;
}
