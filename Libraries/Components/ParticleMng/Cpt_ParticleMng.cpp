#include "Cpt_ParticleMng.h"

UCpt_ParticleMng::UCpt_ParticleMng()
{
	PrimaryComponentTick.bCanEverTick = false;

	// ...
}

void UCpt_ParticleMng::BeginPlay()
{
	Super::BeginPlay();

	// ...

}

void UCpt_ParticleMng::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void UCpt_ParticleMng::AddParticleInstance(FString sName, FString sPath)
{
	FText TextVariable = FText::AsCultureInvariant(sPath);
	ConstructorHelpers::FObjectFinder<UParticleSystem> Asset_Particle(*sPath);
	if (Asset_Particle.Succeeded())
	{
		m_pParticle_List.Add(sName, Asset_Particle.Object);
	}
	else
	{
		ULOG(TEXT("ObjectFind Fail"));
	}
}

UParticleSystemComponent* UCpt_ParticleMng::SpawnParticleAtLocation(FString sParticleName, const UObject* WorldContextObject, FVector SpawnLocation, FRotator SpawnRotation, FVector SpawnScale, bool bAutoDestroy)
{
	UParticleSystem* pInstance = GetParticleInstance(sParticleName);
	if (pInstance == nullptr)
	{
		ULOG(TEXT("%s Particle is null"), *sParticleName);
		return nullptr;
	}

	UParticleSystemComponent* pParticle = UGameplayStatics::SpawnEmitterAtLocation(WorldContextObject, pInstance,
		SpawnLocation, SpawnRotation, SpawnScale,
		bAutoDestroy);

	return pParticle;
}

class UParticleSystemComponent* UCpt_ParticleMng::SpawnParticleAttachComponent(FString sParticleName, USceneComponent* pComponent, FName sSocketName, FVector SpawnLocation, FRotator SpawnRotation, FVector SpawnScale, EAttachLocation::Type LocationType, bool bAutoDestroy)
{
	UParticleSystem* pInstance = GetParticleInstance(sParticleName);
	if (pInstance == nullptr) return nullptr;
	UParticleSystemComponent* pParticle = UGameplayStatics::SpawnEmitterAttached(pInstance, pComponent, sSocketName,
		SpawnLocation, SpawnRotation, SpawnScale,
		LocationType, bAutoDestroy);


	pParticle->AttachTo(pComponent, sSocketName, LocationType);
	return pParticle;
}

UParticleSystem*  UCpt_ParticleMng::GetParticleInstance(FString sParticleName)
{
	for (TMap<FString, UParticleSystem*>::TIterator it = m_pParticle_List.CreateIterator(); it; ++it)
	{
		if (it->Key == sParticleName)
		{
			return it->Value;
		}
	}
	return nullptr;
}