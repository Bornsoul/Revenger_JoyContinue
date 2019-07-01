// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Revenger.h"
#include "Libraries/Components/WarningSpace/WarningSpace_Root.h"
#include "WarningSpace_Dash.generated.h"

/**
 * 
 */
UCLASS()
class REVENGER_API AWarningSpace_Dash : public AWarningSpace_Root
{
	GENERATED_BODY()
	
private :
	float m_fValue;

public :
	virtual void SpawnSpace(float fWarningTime, FVector vLocation, FRotator vRotation = FRotator::ZeroRotator, FVector vScale = FVector::OneVector) override;
	virtual void StopSpace() override;
	virtual void Tick(float DeltaTime) override;
	virtual void Tick_Space(float fDeltaTime) override;
};
