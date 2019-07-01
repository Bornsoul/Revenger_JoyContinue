// Fill out your copyright notice in the Description page of Project Settings.

#include "PPE_Gray.h"
#include "Components/PostProcessComponent.h"
#include "Materials/MaterialInstanceDynamic.h"
#include "Materials/Material.h"
#include "Materials/MaterialInterface.h"
#include "Kismet/KismetMaterialLibrary.h"
#include "Kismet/KismetMathLibrary.h"

UPPE_Gray::UPPE_Gray()
{

}

UPPE_Gray::~UPPE_Gray()
{

}

void UPPE_Gray::Enter()
{
	Super::Enter();

	if (m_pDynamicMaterial == nullptr)
	{
		ULOG(TEXT("DynamicMaterial is nullptr"));
		m_bActive = false;
		return;
	}
	m_fValue = 0.0f;
	m_fValueCur = 1.0f;
	m_fValueTime = 0.0f;
	m_pDynamicMaterial->SetScalarParameterValue("Fraction", m_fValue);

	m_pPostProcess->Settings.AddBlendable(m_pDynamicMaterial, 1.0f);
}

void UPPE_Gray::End()
{
	Super::End();

	//m_fValueCur = 0.0f;
	//m_pDynamicMaterial->SetScalarParameterValue("Fraction", 0.0f);
	m_pPostProcess->Settings.RemoveBlendable(m_pDynamicMaterial);
}

bool UPPE_Gray::Tick_Effect(float fDeltaTime)
{
	if (Super::Tick_Effect(fDeltaTime) == false) return false;

	m_fValueTime = UKismetMathLibrary::FInterpTo(m_fValueTime, 1.0f, fDeltaTime, 1.0f);
	m_pDynamicMaterial->SetScalarParameterValue("Fraction", m_fValueTime);

	/*if (m_fValueTime >= 0.95f)
	{
		m_fValueTime = 1.0f;
		End();
	}
	ULOG(TEXT("Fraction : %f"), m_fValueTime);*/

	return true;
}



