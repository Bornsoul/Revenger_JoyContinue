// Fill out your copyright notice in the Description page of Project Settings.

#include "ME_FresnelHit.h"
#include "../Cpt_MaterialEffect.h"


UME_FresnelHit::UME_FresnelHit()
{

}

void UME_FresnelHit::ActiveEffect()
{
	Super::ActiveEffect();
	m_fCurrTime = 0.0f;
	m_fHitTime = 0.15f;
	m_fHitValue_Insensity = 25.0f;
	m_fHitValue_Exp = 5.0f;


	TArray<UMaterialInstanceDynamic*> pList = m_pRootComp->GetMaterials();

	for (int i = 0; i < pList.Num(); i++)
	{

		//pList[i]->SetScalarParameterValue("FresnelIntensity", m_fHitValue_Insensity);
		pList[i]->SetScalarParameterValue("Hit_Power", m_fHitValue_Insensity);
	}
}

void UME_FresnelHit::Tick_Effect(float fDeltaTime)
{
	//ULOG(TEXT("aaaa"));
	m_fCurrTime += fDeltaTime;
	if (m_fCurrTime > m_fHitTime)
	{
		EndEffect();
	}
}

void UME_FresnelHit::EndEffect()
{
	Super::EndEffect();


	TArray<UMaterialInstanceDynamic*> pList = m_pRootComp->GetMaterials();
	m_fHitValue_Insensity = 0.0f;
	m_fHitValue_Exp = 0.0f;
	for (int i = 0; i < pList.Num(); i++)
	{
		pList[i]->SetScalarParameterValue("Hit_Power", m_fHitValue_Insensity);
	}
}
