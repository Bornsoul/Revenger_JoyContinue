// Fill out your copyright notice in the Description page of Project Settings.

#include "PPE_ChromaticBlur.h"

#include "Components/PostProcessComponent.h"
#include "Materials/MaterialInstanceDynamic.h"
#include "Materials/Material.h"
#include "Materials/MaterialInterface.h"
#include "Kismet/KismetMaterialLibrary.h"
#include "Kismet/KismetMathLibrary.h"

UPPE_ChromaticBlur::UPPE_ChromaticBlur()
{

}

UPPE_ChromaticBlur::~UPPE_ChromaticBlur()
{

}

void UPPE_ChromaticBlur::Enter()
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
	m_fValue = 4.0f;

	m_fColorValue = 0.0f;
	//m_pDynamicMaterial->GetScalarParameterValue();
	m_pDynamicMaterial->SetScalarParameterValue("GlobalIntensity", m_fValue);
	//m_pDynamicMaterial->SetScalarParameterValue("ColorIntensity", 1.0f);

	m_pPostProcess->Settings.AddBlendable(m_pDynamicMaterial, 1.0f);
	m_nState = 0;
}

void UPPE_ChromaticBlur::End()
{
	Super::End();

	m_pDynamicMaterial->SetScalarParameterValue("GlobalIntensity", 0.0f);
	m_pPostProcess->Settings.RemoveBlendable(m_pDynamicMaterial);
}

bool UPPE_ChromaticBlur::Tick_Effect(float fDeltaTime)
{
	if (Super::Tick_Effect(fDeltaTime) == false) return false;

	if (m_nState == 0)
	{
		m_fValue = UKismetMathLibrary::FInterpTo(m_fValue, 1.0f, fDeltaTime, 7.0f);
		m_pDynamicMaterial->SetScalarParameterValue("GlobalIntensity", m_fValue);
		if (m_fValue <= 1.05f)
		{
			m_fValue = 1.0f;
			m_pDynamicMaterial->SetScalarParameterValue("GlobalIntensity", m_fValue);
			m_nState++;
		}
	}
	else if (m_nState == 1)
	{

	}
	else if (m_nState == 2)
	{

	}

	return true;
}


