// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Libraries/Components/WarningSpace/WarningSpace_Root.h"
#include "WarningSpace_Circle.generated.h"

/**
 * 
 */
UCLASS()
class REVENGER_API AWarningSpace_Circle : public AWarningSpace_Root
{
	GENERATED_BODY()
	
public :
	void SpawnSpace_Circle(float fWarningTime, float fAngle, FVector vLocation, FRotator vRotation = FRotator::ZeroRotator, FVector vScale = FVector::OneVector);
};
