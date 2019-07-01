// Fill out your copyright notice in the Description page of Project Settings.

#include "WarningSpace_Circle.h"

void AWarningSpace_Circle::SpawnSpace_Circle(float fWarningTime, float fAngle, FVector vLocation, FRotator vRotation, FVector vScale)
{
	Super::SpawnSpace(fWarningTime, vLocation, vRotation, vScale);
	if (m_pMaterial == nullptr) return;

	m_pMaterial->SetScalarParameterValue("Angle", fAngle);
}