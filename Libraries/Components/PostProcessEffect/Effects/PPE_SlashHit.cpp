// Fill out your copyright notice in the Description page of Project Settings.

#include "PPE_SlashHit.h"
#include "Components/PostProcessComponent.h"
#include "Materials/MaterialInstanceDynamic.h"
#include "Materials/Material.h"
#include "Materials/MaterialInterface.h"
#include "Kismet/KismetMaterialLibrary.h"
#include "Kismet/KismetMathLibrary.h"

UPPE_SlashHit::UPPE_SlashHit()
{

}

UPPE_SlashHit::~UPPE_SlashHit()
{

}

void UPPE_SlashHit::Enter()
{
	Super::Enter();

	if (m_pDynamicMaterial == nullptr)
	{
		ULOG(TEXT("DynamicMaterial is nullptr"));
		m_bActive = false;
		return;
	}

	m_fValue = 4.0f;


	m_pDynamicMaterial->SetScalarParameterValue("GlobalIntensity", m_fValue);
	m_pPostProcess->Settings.AddBlendable(m_pDynamicMaterial, 1.0f);
}

void UPPE_SlashHit::End()
{
	Super::End();

	m_pDynamicMaterial->SetScalarParameterValue("GlobalIntensity", 0.0f);

	m_pPostProcess->Settings.RemoveBlendable(m_pDynamicMaterial);
}

bool UPPE_SlashHit::Tick_Effect(float fDeltaTime)
{
	if (Super::Tick_Effect(fDeltaTime) == false) return false;
	//ULOG(TEXT("%f"), m_fValue);
	m_fValue = UKismetMathLibrary::FInterpTo(m_fValue, 0.0f, fDeltaTime, 6.0f);
	m_pDynamicMaterial->SetScalarParameterValue("GlobalIntensity", m_fValue);
	if (m_fValue < 0.1f) End();

	return true;
}



