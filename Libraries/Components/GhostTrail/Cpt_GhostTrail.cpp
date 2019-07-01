#include "Cpt_GhostTrail.h"
#include "GhostTrail_Root.h"
#include "Mdl_GhostTrail_TickSpawn.h"

UCpt_GhostTrail::UCpt_GhostTrail()
{
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}

void UCpt_GhostTrail::BeginPlay()
{
	Super::BeginPlay();

	m_pOwnerChar = Cast<ACharacter>(this->GetOwner());	
}

void UCpt_GhostTrail::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	Super::EndPlay(EndPlayReason);
	m_pOwnerChar = nullptr;

	for (TMap<FString, UMdl_GhostTrail_TickSpawn*>::TIterator it = m_pEffectTickSpawnModule_List.CreateIterator(); it; ++it)
	{
		it->Value->ConditionalBeginDestroy();
	}
	m_pEffectTickSpawnModule_List.Empty();
}


void UCpt_GhostTrail::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	Tick_GhostTrailEffect(DeltaTime);
}

void UCpt_GhostTrail::Add_GhostTrailEffectActor(FString sName, FString sPath)
{
	FText TextVariable = FText::AsCultureInvariant(sPath);
	ConstructorHelpers::FClassFinder<AGhostTrail_Root> Asset_Effect(*sPath);
	if (Asset_Effect.Succeeded())
	{
		m_pEffect_List.Add(sName, Asset_Effect.Class);
	}
	else
	{
		ULOG(TEXT("ObjectFind Fail"));
	}
}

TSubclassOf<class AGhostTrail_Root> UCpt_GhostTrail::GetGhostTrailEffectActor(FString sName)
{
	for (TMap<FString, TSubclassOf<class AGhostTrail_Root>>::TIterator it = m_pEffect_List.CreateIterator(); it; ++it)
	{
		if (it->Key == sName)
		{
			return it->Value;
		}
	}
	return nullptr;
}

void UCpt_GhostTrail::Spawn_GhostTrailEffect(FString sName, FTransform tSpawnTransform)
{
	if (m_pOwnerChar == nullptr) return;

	TSubclassOf<class AGhostTrail_Root> pEffect = GetGhostTrailEffectActor(sName);
	if (pEffect == nullptr)
	{
		ULOG(TEXT("GhostTrail is NULL"));
		return;
	}

	AGhostTrail_Root* pGhostTrail = GetWorld()->SpawnActor<AGhostTrail_Root>(pEffect);
	if (pGhostTrail == nullptr) return;

	pGhostTrail->Spawn(m_pOwnerChar->GetMesh());
	pGhostTrail->SetActorTransform(tSpawnTransform);
}

void UCpt_GhostTrail::Spawn_GhostTrailEffect(FString sName)
{
	if (m_pOwnerChar == nullptr) return;

	Spawn_GhostTrailEffect(sName, m_pOwnerChar->GetMesh()->GetComponentTransform());
}



void UCpt_GhostTrail::Active_TickGhostTrailEffect(FString sName, float fIntervalTime, float fTickTime)
{
	if (CheckOverlapTickEffect(sName) == true) return;

	UMdl_GhostTrail_TickSpawn* pModule = NewObject<UMdl_GhostTrail_TickSpawn>();
	pModule->Spawn(this, sName, fIntervalTime, fTickTime);

	m_pEffectTickSpawnModule_List.Add(sName, pModule);
}

void UCpt_GhostTrail::DeActive_TickGhostTrailEffect(FString sName)
{
	if (CheckOverlapTickEffect(sName) == false) return;

	for (TMap<FString, UMdl_GhostTrail_TickSpawn*>::TIterator it = m_pEffectTickSpawnModule_List.CreateIterator(); it; ++it)
	{
		if (it->Key == sName)
		{
			it->Value->SetActive(false);
		}
	}
}

void UCpt_GhostTrail::Tick_GhostTrailEffect(float fDeltaTime)
{
	bool bCheckDestroy = false;
	UMdl_GhostTrail_TickSpawn* pTickEffect = nullptr;
	FString sTickEffect_Key;
	do
	{
		bCheckDestroy = false;
		pTickEffect = nullptr;

		for (TMap<FString, UMdl_GhostTrail_TickSpawn*>::TIterator it = m_pEffectTickSpawnModule_List.CreateIterator(); it; ++it)
		{
			if (it->Value->GetActive() == false)
			{
				pTickEffect = it->Value;
				sTickEffect_Key = it->Key;
				bCheckDestroy = true;
				break;
			}
		}
		if (bCheckDestroy == true)
		{
			pTickEffect->ConditionalBeginDestroy();
			pTickEffect = nullptr;
			m_pEffectTickSpawnModule_List.Remove(sTickEffect_Key);
		}

	} while (bCheckDestroy == true);


	for (TMap<FString, UMdl_GhostTrail_TickSpawn*>::TIterator it = m_pEffectTickSpawnModule_List.CreateIterator(); it; ++it)
	{
		it->Value->Tick_Effect(fDeltaTime);
	}
}

bool UCpt_GhostTrail::CheckOverlapTickEffect(FString sName)
{
	bool bCheckOverlap = false;
	for (TMap<FString, UMdl_GhostTrail_TickSpawn*>::TIterator it = m_pEffectTickSpawnModule_List.CreateIterator(); it; ++it)
	{
		if (it->Key == sName)
		{
			return true;
		}
	}
	return false;
}