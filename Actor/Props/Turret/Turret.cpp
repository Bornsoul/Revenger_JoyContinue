// Fill out your copyright notice in the Description page of Project Settings.

#include "Turret.h"
#include "Actor/Characters/Enemy/E4/EnemyE4_Missile.h"
#include "Libraries/Components/ParticleMng/Cpt_ParticleMng.h"
#include "Libraries/Components/MaterialEffect/Cpt_MaterialEffect.h"
#include "Kismet/KismetMathLibrary.h"
// Sets default values
ATurret::ATurret()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	static ConstructorHelpers::FClassFinder<AEnemyE4_Missile> Const_Bullet(TEXT("/Game/1_Project_Main/1_Blueprints/Actor/Characters/Enemy/EnemyE4/BP_EnemyE4_Missile.BP_EnemyE4_Missile_C"));
	if (Const_Bullet.Succeeded()) m_pInstance_Bullet = Const_Bullet.Class;

	m_pSceneComp = CreateDefaultSubobject<USceneComponent>(TEXT("ASdasd"));
	m_pSceneComp->SetWorldLocation(FVector::ZeroVector);
	m_pSceneComp->SetupAttachment(RootComponent);
		

	m_pBulletArrowComp = CreateDefaultSubobject<UArrowComponent>(TEXT("BulletArrowComp"));
	m_pBulletArrowComp->SetWorldLocation(FVector::ZeroVector);
	m_pBulletArrowComp->SetupAttachment(m_pSceneComp);

	m_pArrowComp = CreateDefaultSubobject<UArrowComponent>(TEXT("ArrowComp"));
	m_pArrowComp->SetWorldLocation(FVector::ZeroVector);
	m_pArrowComp->SetupAttachment(m_pSceneComp);

	m_pParticleMng = CreateDefaultSubobject<UCpt_ParticleMng>(TEXT("ParticleMng"));
	m_pParticleMng->AddParticleInstance(TEXT("EyeLight"), TEXT("ParticleSystem'/Game/1_Project_Main/2_Contents/Effects/EyeLight/V_EyeLight.V_EyeLight'"));
	m_pParticleMng->AddParticleInstance(TEXT("Laser"), TEXT("ParticleSystem'/Game/1_Project_Main/2_Contents/Effects/Laser/V_Laser.V_Laser'"));
}

// Called when the game starts or when spawned
void ATurret::BeginPlay()
{
	Super::BeginPlay();
	//SetTurretActive(true);
}

void ATurret::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	Super::EndPlay(EndPlayReason);

	if (m_pSceneComp != nullptr)
	{
		if (m_pSceneComp->IsValidLowLevel())
		{
			m_pSceneComp->DestroyComponent();
			m_pSceneComp = nullptr;
		}
	}

	if (m_pParticleMng != nullptr)
	{
		if (m_pParticleMng->IsValidLowLevel())
		{
			m_pParticleMng->DestroyComponent();
			m_pParticleMng = nullptr;
		}
	}

	if (m_pLaserParticle != nullptr)
	{
		if (m_pLaserParticle->IsValidLowLevel())
		{
			m_pLaserParticle->DestroyComponent();
			m_pLaserParticle = nullptr;
		}
	}

	if (m_pBulletArrowComp != nullptr)
	{
		if (m_pBulletArrowComp->IsValidLowLevel())
		{
			m_pBulletArrowComp->DestroyComponent();
			m_pBulletArrowComp = nullptr;
		}
	}

	if (m_pArrowComp != nullptr)
	{
		if (m_pArrowComp->IsValidLowLevel())
		{
			m_pArrowComp->DestroyComponent();
			m_pArrowComp = nullptr;
		}
	}
}

void ATurret::SetTurretActive(bool bActive)
{
	m_bActive = bActive;
	m_bLaser = bActive;
	m_fTime = 0.0f;
	nState = 0;
	if (bActive == false)
	{
		if (m_pLaserParticle != nullptr)
		{
			m_pLaserParticle->DestroyComponent();
			m_pLaserParticle = nullptr;
		}
	}
}

// Called every frame
void ATurret::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	if (m_bActive == true)
	{		

		switch (nState)
		{
		case 0:
			m_pLaserParticle = m_pParticleMng->SpawnParticleAtLocation(TEXT("Laser"), GetWorld(), m_pBulletArrowComp->GetComponentLocation(), m_pBulletArrowComp->GetComponentRotation(), FVector::OneVector);
			nState = 1;
			break;
		case 1:
			m_fTime += DeltaTime;
			if (m_fTime >= m_fLaserTime)
			{
				if (m_pLaserParticle != nullptr)
				{
					m_pLaserParticle->DestroyComponent();
					m_pLaserParticle = nullptr;
				}
				m_fTime = 0.0f;
				nState = 2;
			}
			break;
		case 2:
			m_fTime += DeltaTime;
			if (m_fTime >= 0.2f)
			{				
				m_pBullet = CreateBullet(m_pBulletArrowComp->GetComponentLocation(), m_pArrowComp->GetComponentLocation());
				m_fTime = 0.0f;
				nState = 3;
			}
			break;
		case 3:
			m_fTime += DeltaTime;
			if (m_fTime >= 0.8f)
			{
				m_pLaserParticle = m_pParticleMng->SpawnParticleAtLocation(TEXT("Laser"), GetWorld(), m_pBulletArrowComp->GetComponentLocation(), m_pBulletArrowComp->GetComponentRotation(), FVector::OneVector);
				m_fTime = 0.0f;
				nState = 1;
			}
			break;
		}

		if (m_pLaserParticle != nullptr)
		{
			m_pLaserParticle->SetBeamEndPoint(0, m_pArrowComp->GetComponentLocation());
		}		
	}

	if (m_pBullet != nullptr)
	{
		if (m_pBullet->GetSuccessHit())
		{
			m_bSuccessHit = true;
			m_pBullet = nullptr;
			return;
		}
	}
}

AEnemyE4_Missile * ATurret::CreateBullet(FVector vShootLoc, FVector vTargetLoc)
{
	if (m_pInstance_Bullet == nullptr) return nullptr;
	m_pBullet = nullptr;

	AEnemyE4_Missile* pBullet = GetWorld()->SpawnActor<AEnemyE4_Missile>(m_pInstance_Bullet);
	if (pBullet == nullptr) return nullptr;
	
	pBullet->Shoot(this, vShootLoc, vTargetLoc);
	return pBullet;
}
