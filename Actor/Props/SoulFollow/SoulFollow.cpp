// Fill out your copyright notice in the Description page of Project Settings.

#include "SoulFollow.h"
#include "Particles/ParticleSystemComponent.h"
// Sets default values
ASoulFollow::ASoulFollow()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	m_pParticle = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("Particle"));
	RootComponent = m_pParticle;

	static ConstructorHelpers::FClassFinder<AActor> Const_Bullet(TEXT("/Game/1_Project_Main/2_Contents/Effects/SmokeBoom/BP_SmokeExFoot.BP_SmokeExFoot_C"));
	if (Const_Bullet.Succeeded()) m_pInst_Foot = Const_Bullet.Class;
}

// Called when the game starts or when spawned
void ASoulFollow::BeginPlay()
{
	Super::BeginPlay();
	if (m_pInst_Foot == nullptr) return;

	int nCount = rand() % 3 + 4;
	for (int i = 0; i < nCount; i++)
	{

		AActor* pSrc = GetWorld()->SpawnActor<AActor>(m_pInst_Foot, GetActorLocation(), FRotator::ZeroRotator);
		if (pSrc == nullptr) return;

		

	}
	m_fDieTime = 0.0f;
}

// Called every frame
void ASoulFollow::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	m_fDieTime += DeltaTime;
	if (m_fDieTime > 2.0f) Destroy();

}

