#include "PostProcessEffect_Root.h"
#include "Components/PostProcessComponent.h"
#include "Materials/MaterialInstanceDynamic.h"
#include "Materials/Material.h"
#include "Materials/MaterialInterface.h"
#include "Kismet/KismetMaterialLibrary.h"
#include "Kismet/KismetMathLibrary.h"

UPostProcessEffect_Root::UPostProcessEffect_Root()
{

}

UPostProcessEffect_Root::~UPostProcessEffect_Root()
{
	m_pDynamicMaterial = nullptr;
	m_pPostProcess = nullptr;
}

void UPostProcessEffect_Root::Init(class UPostProcessComponent* pPostProcessComponent, UObject* WorldContextObject)
{
	if (m_pInstance_Material == nullptr) return;

	m_bActive = false;
	m_bInit = false;

	m_pDynamicMaterial = UKismetMaterialLibrary::CreateDynamicMaterialInstance(WorldContextObject, m_pInstance_Material);
	m_pPostProcess = pPostProcessComponent;

	if (m_pDynamicMaterial == nullptr)
	{
		ULOG(TEXT("DynamicMaterial is NULL"));
		return;
	}
	m_bInit = true;
}

void UPostProcessEffect_Root::Enter()
{
	if (m_bInit == false) return;
	m_bActive = true;
}


void UPostProcessEffect_Root::End()
{
	m_bActive = false;
}

bool UPostProcessEffect_Root::Tick_Effect(float fDeltaTime)
{
	if (m_bActive == false) return false;

	return true;
}


