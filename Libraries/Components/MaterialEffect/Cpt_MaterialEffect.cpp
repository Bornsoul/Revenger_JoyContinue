#include "Cpt_MaterialEffect.h"
#include "Kismet/KismetMaterialLibrary.h"
#include "MaterialEffect_Root.h"

#include "Effects/ME_FresnelHit.h"
#include "Effects/ME_CharacterHit.h"
#include "Effects/ME_DisintEffect.h"

UCpt_MaterialEffect::UCpt_MaterialEffect()
{
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}

void UCpt_MaterialEffect::BeginPlay()
{
	Super::BeginPlay();

	// ...
}

void UCpt_MaterialEffect::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	Super::EndPlay(EndPlayReason);
	for (TMap<int, class UMaterialEffect_Root*>::TIterator it = m_pEffectList_Running.CreateIterator(); it; ++it)
	{
		it->Value->Destroy();
	}
	m_pEffectList_Running.Empty();
}

void UCpt_MaterialEffect::Init(class USkeletalMeshComponent* pMesh)
{
	if (m_bInit == true) return;
	m_bInit = true;
	m_pSkeletal_Mesh = pMesh;
	TArray<UMaterialInterface*> pMaterials = pMesh->GetMaterials();
	for (int i = 0; i < pMaterials.Num(); i++)
	{
		UMaterialInstanceDynamic* pSpawnMaterial = UKismetMaterialLibrary::CreateDynamicMaterialInstance(pMesh->GetWorld(), pMaterials[i]);

		pMesh->SetMaterial(i, pSpawnMaterial);
		m_pSpawnMaterial.Add(pSpawnMaterial);
	}
}

void UCpt_MaterialEffect::Init(class UStaticMeshComponent* pMesh)
{
	if (m_bInit == true) return;
	m_bInit = true;
	m_pStatic_Mesh = pMesh;
	TArray<UMaterialInterface*> pMaterials = pMesh->GetMaterials();


	for (int i = 0; i < pMaterials.Num(); i++)
	{
		UMaterialInstanceDynamic* pSpawnMaterial = pMesh->CreateDynamicMaterialInstance(i);
		m_pSpawnMaterial.Add(pSpawnMaterial);
	}
}

void UCpt_MaterialEffect::AddEffect(E_MaterialEffect eEffect)
{
	UMaterialEffect_Root* pEffect = nullptr;

	switch (eEffect)
	{
	case E_MaterialEffect::E_Hit:
		pEffect = NewObject<UME_FresnelHit>();
		break;
	case E_MaterialEffect::E_Hit2:
		pEffect = NewObject<UME_CharacterHit>();
		break;
	case E_MaterialEffect::E_Disint:
		pEffect = NewObject<UME_DisintEffect>();
		break;
	}

	if (pEffect != nullptr)
	{
		pEffect->Init(this);
		m_pEffectList.Add((int)eEffect, pEffect);

		//ULOG(TEXT("%d"), (int)eEffect);
	}
}

void UCpt_MaterialEffect::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if (m_bInit == false) return;

	TickEffects(DeltaTime);
}

void UCpt_MaterialEffect::ActiveEffect_Hit()
{
	UMaterialEffect_Root* pEffect = GetEffect(E_MaterialEffect::E_Hit);
	if (pEffect == nullptr) return;

	pEffect->ActiveEffect();

	if (CheckEffectRunning(E_MaterialEffect::E_Hit) == true) return;
	m_pEffectList_Running.Add((int)E_MaterialEffect::E_Hit, pEffect);


}

void UCpt_MaterialEffect::ActiveEffect(E_MaterialEffect eEffect)
{
	UMaterialEffect_Root* pEffect = GetEffect(eEffect);
	if (pEffect == nullptr) return;

	pEffect->ActiveEffect();

	if (CheckEffectRunning(eEffect) == true) return;
	m_pEffectList_Running.Add((int)eEffect, pEffect);
}

void UCpt_MaterialEffect::TickEffects(float fDeltaTime)
{
	//	if (m_nRunningEffectCount == 0) return;

	bool bCheck = false;
	do
	{
		bCheck = false;
		int nRemoveObj = -1;
		UMaterialEffect_Root* pObj = nullptr;

		for (TMap<int, UMaterialEffect_Root*>::TIterator it = m_pEffectList_Running.CreateIterator(); it; ++it)
		{
			if (it->Value->GetActive() == false)
			{
				m_pEffectList_Running.Remove(it->Key);
				int nRemoveObj = it->Key;
				pObj = it->Value;
				break;
			}
		}

		/*if (pObj != nullptr)
		{
			ULOG(TEXT("adasdas"));
			m_pEffectList_Running.Remove()
			bCheck = true;
		}*/

		/*if (nRemoveObj != -1)
		{
			ULOG(TEXT("adasdas %d"), nRemoveObj);
			m_pEffectList_Running.Remove(nRemoveObj);
			bCheck = true;
		}*/
	} while (bCheck);

	for (TMap<int, class UMaterialEffect_Root*>::TIterator it = m_pEffectList_Running.CreateIterator(); it; ++it)
	{
		it->Value->Tick_Effect(fDeltaTime);
	}
}

UMaterialEffect_Root* UCpt_MaterialEffect::GetEffect(E_MaterialEffect eEffect)
{
	for (TMap<int, class UMaterialEffect_Root*>::TIterator it = m_pEffectList.CreateIterator(); it; ++it)
	{
		if (it->Key == (int)eEffect)
		{
			return it->Value;
		}
	}
	return nullptr;
}

bool UCpt_MaterialEffect::CheckEffectRunning(E_MaterialEffect eEffect)
{
	for (TMap<int, class UMaterialEffect_Root*>::TIterator it = m_pEffectList_Running.CreateIterator(); it; ++it)
	{
		if (it->Key == (int)eEffect)
		{
			return true;
		}
	}
	return false;
}