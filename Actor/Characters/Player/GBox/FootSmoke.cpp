// Fill out your copyright notice in the Description page of Project Settings.

#include "FootSmoke.h"
#include "Particles/ParticleSystemComponent.h"

// Sets default values
AFootSmoke::AFootSmoke()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	m_pParticle = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("Particle"));
	RootComponent = m_pParticle;

}

// Called when the game starts or when spawned
void AFootSmoke::BeginPlay()
{
	Super::BeginPlay();
	m_bStop = false;
}

// Called every frame
void AFootSmoke::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	if (m_bStop == true)
	{
		m_fTime += DeltaTime;
		if (m_fTime > 2.0f)
		{
			Destroy();
			m_bStop = false;
		}
	}
}

void AFootSmoke::Stop()
{
	m_bStop = true;
	m_pParticle->DeactivateSystem();
}