// Fill out your copyright notice in the Description page of Project Settings.

#include "ME_CharacterHit.h"
#include "../Cpt_MaterialEffect.h"


UME_CharacterHit::UME_CharacterHit()
{

}

void UME_CharacterHit::ActiveEffect()
{
	Super::ActiveEffect();
	m_fCurrTime = 0.0f;
	m_fHitTime = 0.3f;
	m_fHitValue_Insensity = 1.0f;

	TArray<UMaterialInstanceDynamic*> pList = m_pRootComp->GetMaterials();

	for (int i = 0; i < pList.Num(); i++)
	{

		//pList[i]->SetScalarParameterValue("FresnelIntensity", m_fHitValue_Insensity);
		pList[i]->SetScalarParameterValue("HitIntensity", m_fHitValue_Insensity);
	}

	//ULOG(TEXT("Start"));
}

void UME_CharacterHit::Tick_Effect(float fDeltaTime)
{
//	ULOG(TEXT("Dog"));
	m_fCurrTime += fDeltaTime;
	if (m_fCurrTime > m_fHitTime)
	{
		EndEffect();
	}
}

void UME_CharacterHit::EndEffect()
{
	Super::EndEffect();
	//ULOG(TEXT("End"));
	TArray<UMaterialInstanceDynamic*> pList = m_pRootComp->GetMaterials();
	m_fHitValue_Insensity = 0.0f;
	for (int i = 0; i < pList.Num(); i++)
	{
		pList[i]->SetScalarParameterValue("HitIntensity", m_fHitValue_Insensity);
	}
}
