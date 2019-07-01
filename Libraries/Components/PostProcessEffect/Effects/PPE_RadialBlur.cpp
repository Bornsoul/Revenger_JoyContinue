// Fill out your copyright notice in the Description page of Project Settings.

#include "PPE_RadialBlur.h"
#include "Components/PostProcessComponent.h"
#include "Materials/MaterialInstanceDynamic.h"
#include "Materials/Material.h"
#include "Materials/MaterialInterface.h"
#include "Kismet/KismetMaterialLibrary.h"
#include "Kismet/KismetMathLibrary.h"

UPPE_RadialBlur::UPPE_RadialBlur()
{

}

UPPE_RadialBlur::~UPPE_RadialBlur()
{

}

void UPPE_RadialBlur::Enter()
{
	Super::Enter();

	if (m_pDynamicMaterial == nullptr)
	{
		ULOG(TEXT("DynamicMaterial is nullptr"));
		m_bActive = false;
		return;
	}
	m_bPingPong = false;
	m_fTime = 0.0f;
	m_fAgoTime = 0.07f;
	m_fValue = 0.0f;

	m_fColorValue = 0.0f;
	//m_pDynamicMaterial->GetScalarParameterValue();
	m_pDynamicMaterial->SetScalarParameterValue("GlobalIntensity", m_fValue);
	m_pDynamicMaterial->SetScalarParameterValue("ColorIntensity", 1.0f);

	m_pPostProcess->Settings.AddBlendable(m_pDynamicMaterial, 1.0f);
}

void UPPE_RadialBlur::End()
{
	Super::End();

	m_pDynamicMaterial->SetScalarParameterValue("ColorIntensity", 0.0f);
	m_pDynamicMaterial->SetScalarParameterValue("GlobalIntensity", 0.0f);
	m_pPostProcess->Settings.RemoveBlendable(m_pDynamicMaterial);
}

bool UPPE_RadialBlur::Tick_Effect(float fDeltaTime)
{
	if (Super::Tick_Effect(fDeltaTime) == false) return false;


	if (m_bPingPong == false)
	{
		m_fValue = UKismetMathLibrary::FInterpTo(m_fValue, 0.8f, fDeltaTime, 13.0f);
		m_pDynamicMaterial->SetScalarParameterValue("GlobalIntensity", m_fValue);
		m_pDynamicMaterial->SetScalarParameterValue("ColorIntensity", m_fValue);

		if (m_fValue > 0.75f)
		{
			m_fTime += fDeltaTime;
			if (m_fTime > 0.1f)
			{
				m_fTime = 0.0f;
				m_bPingPong = !m_bPingPong;
			}
		}
	}
	else
	{
		m_fValue = UKismetMathLibrary::FInterpTo(m_fValue, 0.0f, fDeltaTime, 7.0f);
		m_pDynamicMaterial->SetScalarParameterValue("GlobalIntensity", m_fValue);

		m_pDynamicMaterial->SetScalarParameterValue("ColorIntensity", m_fValue);
		if (m_fValue <= 0.05f)
		{
			m_fValue = 0.0f;
			End();
		}
	}

	return true;
}





