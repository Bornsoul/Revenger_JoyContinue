#include "Cpt_PostProcessEffect.h"
#include "Components/PostProcessComponent.h"
#include "Materials/MaterialInstanceDynamic.h"
#include "Materials/Material.h"
#include "Materials/MaterialInterface.h"
#include "Kismet/KismetMaterialLibrary.h"
#include "Kismet/KismetMathLibrary.h"

#include "PostProcessEffect_Root.h"

UCpt_PostProcessEffect::UCpt_PostProcessEffect()
{
	PrimaryComponentTick.bCanEverTick = true;

}

void UCpt_PostProcessEffect::BeginPlay()
{
	Super::BeginPlay();

}

void UCpt_PostProcessEffect::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	Super::EndPlay(EndPlayReason);
	m_pPostProcess = nullptr;

	for (TMap<FString, UPostProcessEffect_Root*>::TIterator it = m_pPostprocessEffect_SpawnList.CreateIterator(); it; ++it)
	{
		it->Value->ConditionalBeginDestroy();
	}
	m_pPostprocessEffect_SpawnList.Empty();
}

void UCpt_PostProcessEffect::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if (m_bInit == false) return;
	for (TMap<FString, UPostProcessEffect_Root*>::TIterator it = m_pPostprocessEffect_SpawnList.CreateIterator(); it; ++it)
	{
		it->Value->Tick_Effect(DeltaTime);
	}
}

void UCpt_PostProcessEffect::Init(class UPostProcessComponent* pPostProcess)
{
	m_pPostProcess = pPostProcess;
	if (m_pPostProcess == nullptr)
	{
		ULOG(TEXT("PostProcess is null"));
		return;
	}

	for (TMap<FString, TSubclassOf<class UPostProcessEffect_Root>>::TIterator it = m_pPostprocessEffect_List.CreateIterator(); it; ++it)
	{
		UPostProcessEffect_Root* pObj = NewObject<UPostProcessEffect_Root>(this, it->Value);

		if (pObj == nullptr) continue;

		pObj->Init(m_pPostProcess, GetOwner()->GetWorld());
		m_pPostprocessEffect_SpawnList.Add(it->Key, pObj);
	}

	m_bInit = true;
}

void UCpt_PostProcessEffect::Add_PostProcessEffect(FString sName, FString sPath)
{
	FText TextVariable = FText::AsCultureInvariant(sPath);
	ConstructorHelpers::FClassFinder<UPostProcessEffect_Root> Asset_Effect(*sPath);

	if (Asset_Effect.Succeeded())
	{
		m_pPostprocessEffect_List.Add(sName, Asset_Effect.Class);
	}
	else
	{
		ULOG(TEXT("ObjectFind Fail"));
	}
}

void UCpt_PostProcessEffect::Active_Effect(FString sName)
{

	for (TMap<FString, UPostProcessEffect_Root*>::TIterator it = m_pPostprocessEffect_SpawnList.CreateIterator(); it; ++it)
	{
		if (it->Key == sName)
		{
			it->Value->Enter();
		}
	}
}

void UCpt_PostProcessEffect::DeActive_Effect(FString sName)
{
	for (TMap<FString, UPostProcessEffect_Root*>::TIterator it = m_pPostprocessEffect_SpawnList.CreateIterator(); it; ++it)
	{
		if (it->Key == sName)
		{
			it->Value->End();
		}
	}
}

void UCpt_PostProcessEffect::DeActive_AllEffect()
{
	for (TMap<FString, UPostProcessEffect_Root*>::TIterator it = m_pPostprocessEffect_SpawnList.CreateIterator(); it; ++it)
	{
		it->Value->End();
	}
}