// Fill out your copyright notice in the Description page of Project Settings.

#include "PPE_PlayerHit.h"
#include "Components/PostProcessComponent.h"
#include "Materials/MaterialInstanceDynamic.h"
#include "Materials/Material.h"
#include "Materials/MaterialInterface.h"
#include "Kismet/KismetMaterialLibrary.h"
#include "Kismet/KismetMathLibrary.h"

UPPE_PlayerHit::UPPE_PlayerHit()
{

}

UPPE_PlayerHit::~UPPE_PlayerHit()
{

}

void UPPE_PlayerHit::Enter()
{
	Super::Enter();
	m_bPingPong = false;
	m_fValue = 0.3f;
	m_fCurrTime = 0.0f;

	m_pDynamicMaterial->SetScalarParameterValue("GlobalIntensity", m_fValue);
	m_pPostProcess->Settings.AddBlendable(m_pDynamicMaterial, 1.0f);

}

void UPPE_PlayerHit::End()
{
	Super::End();
	m_pDynamicMaterial->SetScalarParameterValue("GlobalIntensity", 0.0f);
	m_pPostProcess->Settings.RemoveBlendable(m_pDynamicMaterial);

}

bool UPPE_PlayerHit::Tick_Effect(float fDeltaTime)
{
	if (Super::Tick_Effect(fDeltaTime) == false) return false;


	if (m_bPingPong == false)
	{
		m_fCurrTime += fDeltaTime;
		if (m_fCurrTime >= 0.15f)
		{
			m_bPingPong = true;
		}
	}
	else
	{
		m_fValue = UKismetMathLibrary::FInterpTo(m_fValue, 0.0f, fDeltaTime, 13.0f);
		m_pDynamicMaterial->SetScalarParameterValue("GlobalIntensity", m_fValue);
		if (m_fValue <= 0.05f)
		{
			m_fValue = 0.0f;
			End();
		}
	}
	return true;
}