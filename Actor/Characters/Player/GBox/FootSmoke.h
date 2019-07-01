// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "FootSmoke.generated.h"

UCLASS()
class REVENGER_API AFootSmoke : public AActor
{
	GENERATED_BODY()
	
public:	
	UPROPERTY(VisibleAnywhere)
		class UParticleSystemComponent* m_pParticle;

	float m_fTime;
	bool m_bStop = false;
public:	
	AFootSmoke();
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;

	void Stop();
};
