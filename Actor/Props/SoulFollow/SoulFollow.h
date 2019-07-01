// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Revenger.h"
#include "GameFramework/Actor.h"
#include "SoulFollow.generated.h"

UCLASS()
class REVENGER_API ASoulFollow : public AActor
{
	GENERATED_BODY()
	
public:	
	UPROPERTY(VisibleAnywhere)
		class UParticleSystemComponent* m_pParticle;

	UPROPERTY()
		TSubclassOf<class AActor> m_pInst_Foot;

	float m_fDieTime;

public:	
	ASoulFollow();
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;

};
