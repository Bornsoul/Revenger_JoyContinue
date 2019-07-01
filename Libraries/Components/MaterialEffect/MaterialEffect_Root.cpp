#include "MaterialEffect_Root.h"
#include "Materials/MaterialInstanceDynamic.h"
#include "Materials/MaterialInterface.h"
#include "Cpt_MaterialEffect.h"

UMaterialEffect_Root::UMaterialEffect_Root()
{

}

void UMaterialEffect_Root::Init(UCpt_MaterialEffect* pRootComp)
{
	m_pRootComp = pRootComp;
}

void UMaterialEffect_Root::Destroy()
{
	m_pRootComp = nullptr;
}

void UMaterialEffect_Root::ActiveEffect()
{
	m_bActive = true;
}

void UMaterialEffect_Root::Tick_Effect(float fDeltaTime)
{

}

void UMaterialEffect_Root::EndEffect()
{
	m_bActive = false;
}

