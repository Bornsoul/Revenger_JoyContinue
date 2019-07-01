// Fill out your copyright notice in the Description page of Project Settings.

#include "PPE_SlowMotion.h"
#include "Components/PostProcessComponent.h"
#include "Materials/MaterialInstanceDynamic.h"
#include "Materials/Material.h"
#include "Materials/MaterialInterface.h"
#include "Kismet/KismetMaterialLibrary.h"
#include "Kismet/KismetMathLibrary.h"

UPPE_SlowMotion::UPPE_SlowMotion()
{

}

UPPE_SlowMotion::~UPPE_SlowMotion()
{

}

void UPPE_SlowMotion::Enter()
{
	Super::Enter();

	if (m_pDynamicMaterial == nullptr)
	{
		ULOG(TEXT("DynamicMaterial is nullptr"));
		m_bActive = false;
		return;
	}

	m_fValue = 0.0f;


	m_pDynamicMaterial->SetScalarParameterValue("BlackIntensity", m_fValue);
	m_pPostProcess->Settings.AddBlendable(m_pDynamicMaterial, 1.0f);
}

void UPPE_SlowMotion::End()
{
	Super::End();

	m_pDynamicMaterial->SetScalarParameterValue("BlackIntensity", 0.0f);

	m_pPostProcess->Settings.RemoveBlendable(m_pDynamicMaterial);
}

bool UPPE_SlowMotion::Tick_Effect(float fDeltaTime)
{
	if (Super::Tick_Effect(fDeltaTime) == false) return false;

	m_fValue = UKismetMathLibrary::FInterpTo(m_fValue, 1.0f, fDeltaTime, 13.0f);
	m_pDynamicMaterial->SetScalarParameterValue("BlackIntensity", m_fValue);

	return true;
}


