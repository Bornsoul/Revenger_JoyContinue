// Fill out your copyright notice in the Description page of Project Settings.

#include "GT_AlphaDown.h"
#include "Kismet/KismetMathLibrary.h"

AGT_AlphaDown::AGT_AlphaDown()
{

}

void AGT_AlphaDown::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	m_fOpacity = UKismetMathLibrary::FInterpTo(m_fOpacity, 0.0f, DeltaTime, m_fInterp_Opcaity);
	for (int i = 0; i < m_pSpawnMaterial.Num(); i++)
	{
		m_pSpawnMaterial[i]->SetScalarParameterValue(FName(*m_sMaterialValueStr_Opacity), m_fOpacity);
	}

	if (m_fOpacity <= 0.0f) Destroy();
}

void AGT_AlphaDown::Spawn(USkeletalMeshComponent * pMesh)
{
	Super::Spawn(pMesh);
	m_fOpacity = m_fStart_Opcaity;

	for (int i = 0; i < m_pSpawnMaterial.Num(); i++)
	{
		m_pSpawnMaterial[i]->SetScalarParameterValue(FName(*m_sMaterialValueStr_Opacity), m_fOpacity);
	}
}


