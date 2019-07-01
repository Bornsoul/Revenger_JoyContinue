// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Revenger.h"
#include "GameFramework/Actor.h"
#include "WarningSpace_Root.generated.h"

UCLASS()
class REVENGER_API AWarningSpace_Root : public AActor
{
	GENERATED_BODY()
	
public:	
	
protected :
	UPROPERTY(VisibleAnywhere, meta = (AllowPrivateAccess = "true"))
		class UStaticMeshComponent* m_pMesh;

	UPROPERTY()
		class UMaterialInstanceDynamic* m_pMaterial;

	float m_fWarningTime;
	float m_fWarningTime_Curr;
	
	bool m_bActive;

public:	
	AWarningSpace_Root();
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;

	virtual void SpawnSpace(float fWarningTime, FVector vLocation, FRotator vRotation = FRotator::ZeroRotator, FVector vScale = FVector::OneVector);
	virtual void StopSpace();

	virtual void Tick_Space(float fDeltaTime);
};
