#include "Cpt_CamShake.h"
#include "Camera/PlayerCameraManager.h"

UCpt_CamShake::UCpt_CamShake()
{
	PrimaryComponentTick.bCanEverTick = false;

	// ...
}

void UCpt_CamShake::BeginPlay()
{
	Super::BeginPlay();

	APlayerController* pPlayerController = UGameplayStatics::GetPlayerController(GetWorld(), 0);
	m_pCameraManager = pPlayerController->PlayerCameraManager;
}

void UCpt_CamShake::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	Super::EndPlay(EndPlayReason);
	m_pCameraManager = nullptr;
}

void UCpt_CamShake::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void UCpt_CamShake::AddCameraShakeClass(FString sName, FString sPath)
{
	ConstructorHelpers::FClassFinder<UCameraShake> Const_CS(*sPath);
	if (Const_CS.Succeeded())
	{
		m_pCSList.Add(sName, Const_CS.Class);
	}
	else
	{
		ULOG(TEXT("CameraShake is null"));
	}
}

void UCpt_CamShake::PlayCameraShake(FString sCamShakeName, float fScale, ECameraAnimPlaySpace::Type pAnimSpace)
{
	if (m_pCameraManager == nullptr) return;

	TSubclassOf<UCameraShake> pClass = GetCameraShakeClass(sCamShakeName);
	if (pClass == nullptr)
	{
		ULOG(TEXT("CameraShake is null"));
		return;
	}
	m_pCameraManager->PlayCameraShake(pClass, fScale, pAnimSpace);
}

TSubclassOf<UCameraShake> UCpt_CamShake::GetCameraShakeClass(FString sName)
{
	for (TMap<FString, TSubclassOf<UCameraShake>>::TIterator it = m_pCSList.CreateIterator(); it; ++it)
	{
		if (it->Key == sName)
		{
			return it->Value;
		}
	}
	return nullptr;
}