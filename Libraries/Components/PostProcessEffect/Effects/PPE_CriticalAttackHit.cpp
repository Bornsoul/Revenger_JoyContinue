// Fill out your copyright notice in the Description page of Project Settings.

#include "PPE_CriticalAttackHit.h"
#include "Components/PostProcessComponent.h"
#include "Materials/MaterialInstanceDynamic.h"
#include "Materials/Material.h"
#include "Materials/MaterialInterface.h"
#include "Kismet/KismetMaterialLibrary.h"
#include "Kismet/KismetMathLibrary.h"

UPPE_CriticalAttackHit::UPPE_CriticalAttackHit()
{

}

UPPE_CriticalAttackHit::~UPPE_CriticalAttackHit()
{

}

void UPPE_CriticalAttackHit::Enter()
{
	Super::Enter();

	m_fValue = 0.15f;
	m_fCurrTime = 0.0f;

	m_pDynamicMaterial->SetScalarParameterValue("GlobalIntensity", m_fValue);
	m_pPostProcess->Settings.AddBlendable(m_pDynamicMaterial, 1.0f);

}

void UPPE_CriticalAttackHit::End()
{
	Super::End();
	m_pDynamicMaterial->SetScalarParameterValue("GlobalIntensity", 0.0f);
	m_pPostProcess->Settings.RemoveBlendable(m_pDynamicMaterial);

}

bool UPPE_CriticalAttackHit::Tick_Effect(float fDeltaTime)
{
	if (Super::Tick_Effect(fDeltaTime) == false) return false;



	m_fCurrTime += fDeltaTime;
	if (m_fCurrTime >= 0.18f)
	{
		End();
	}


	return true;
}
