// Fill out your copyright notice in the Description page of Project Settings.

#include "ME_DisintEffect.h"
#include "../Cpt_MaterialEffect.h"
#include "Kismet/KismetMathLibrary.h"
#include "Kismet/KismetSystemLibrary.h"

UME_DisintEffect::UME_DisintEffect()
{

}

void UME_DisintEffect::ActiveEffect()
{
	Super::ActiveEffect();

	m_fInterF = 0.0f;
	TArray<UMaterialInstanceDynamic*> pList = m_pRootComp->GetMaterials();

	for (int i = 0; i < pList.Num(); i++)
	{
		//pList[i]->SetScalarParameterValue("FresnelIntensity", m_fHitValue_Insensity);
		pList[i]->SetScalarParameterValue("DisInt_Amount", 0.0f);
	}
}

void UME_DisintEffect::Tick_Effect(float fDeltaTime)
{
	m_fInterF = UKismetMathLibrary::FInterpTo(m_fInterF, 1.0f, fDeltaTime, 1.5f);

//	ULOG(TEXT("%f"), m_fInterF);

	TArray<UMaterialInstanceDynamic*> pList = m_pRootComp->GetMaterials();
	for (int i = 0; i < pList.Num(); i++)
	{
		pList[i]->SetScalarParameterValue("DisInt_Amount", m_fInterF);
	}
	

	if (m_fInterF >= 1.0f)
	{
		EndEffect();
	}
}

void UME_DisintEffect::EndEffect()
{
	Super::EndEffect();

	TArray<UMaterialInstanceDynamic*> pList = m_pRootComp->GetMaterials();
	for (int i = 0; i < pList.Num(); i++)
	{
		pList[i]->SetScalarParameterValue("DisInt_Amount", 1.0f);
	}
}

