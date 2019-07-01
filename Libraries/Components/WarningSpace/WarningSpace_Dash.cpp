// Fill out your copyright notice in the Description page of Project Settings.

#include "WarningSpace_Dash.h"
#include "Kismet/KismetMathLibrary.h"

void AWarningSpace_Dash::SpawnSpace(float fWarningTime, FVector vLocation, FRotator vRotation, FVector vScale)
{
	Super::SpawnSpace(fWarningTime, vLocation, vRotation, vScale);
	m_fValue = 0.5f;
	vRotation.Yaw += 90.0f;
	SetActorRotation(vRotation );
}

void AWarningSpace_Dash::StopSpace()
{
	//if (m_pMaterial == nullptr) return;
	m_bActive = false;

	//Destroy();
}

void AWarningSpace_Dash::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	Tick_Space(DeltaTime);
}

void AWarningSpace_Dash::Tick_Space(float fDeltaTime)
{
	//if (m_bActive == false) return;
	//Super::Tick_Space(fDeltaTime);
	ULOG(TEXT("adsa"));
	if (m_bActive == true)
	{
		m_pMaterial->SetScalarParameterValue("Opacity", 0.5f);
		m_fWarningTime_Curr += fDeltaTime;
	//	m_pMaterial->SetScalarParameterValue("ProgressValue", m_fWarningTime_Curr / m_fWarningTime * 1.0f);
		if (m_fWarningTime_Curr >= m_fWarningTime)
		{

			StopSpace();
		}
	}
	else
	{
		m_fValue = UKismetMathLibrary::FInterpTo(m_fValue, 0.0f, fDeltaTime, 7.0f);
		m_pMaterial->SetScalarParameterValue("Opacity", m_fValue);
		if (m_fValue < 0.1f)
		{
			m_fValue = 0.0f;
			Super::StopSpace();
		}

	}

}

