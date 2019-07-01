// Fill out your copyright notice in the Description page of Project Settings.

#include "GBoxEnemyLong_Bullet.h"
#include "Components/StaticMeshComponent.h"
#include "Components/SphereComponent.h"
#include "Libraries/Components/ParticleMng/Cpt_ParticleMng.h"
#include "Kismet/KismetMathLibrary.h"

AGBoxEnemyLong_Bullet::AGBoxEnemyLong_Bullet()
{
	PrimaryActorTick.bCanEverTick = true;
	Tags.Add(FName("EnemyBullet"));

	m_pCollider = CreateDefaultSubobject<USphereComponent>(TEXT("Collider"));
	m_pCollider->OnComponentBeginOverlap.AddDynamic(this, &AGBoxEnemyLong_Bullet::OnOverlapBegin);
	m_pCollider->SetCollisionProfileName(TEXT("EnemyBullet"));

	RootComponent = m_pCollider;

	m_pMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	m_pMesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	m_pMesh->SetupAttachment(RootComponent);

	m_pParticleMng = CreateDefaultSubobject<UCpt_ParticleMng>(TEXT("ParticleMng"));
	m_pParticleMng->AddParticleInstance(TEXT("Explosion"), TEXT("ParticleSystem'/Game/1_Project_Main/2_Contents/Effects/Ex/StandardExplosion/P_Explosion_Small.P_Explosion_Small'"));
}

void AGBoxEnemyLong_Bullet::BeginPlay()
{
	Super::BeginPlay();
	m_bShooted = false;
	m_bReflected = false;
	m_bReflectWaitTime = false;
}

void AGBoxEnemyLong_Bullet::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	Super::EndPlay(EndPlayReason);
	m_pShooter = nullptr;
}

void AGBoxEnemyLong_Bullet::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (m_bShooted == true)
	{
		if (m_bReflectWaitTime == false)
		{
			FVector vLoc = GetActorLocation();

			float fSpeed = m_fMoveSpeed;
			if (m_bReflected == true) fSpeed *= 2.0f;
			vLoc += GetActorForwardVector() * fSpeed * DeltaTime;

			SetActorLocation(vLoc);
		}

	}

	if (m_bReflected == true)
	{
		if (m_bReflectWaitTime == true)
		{
			m_fReflectWiatTime_Curr += DeltaTime;
			if (m_fReflectWiatTime_Curr >= m_fReflectWiatTime_Ago)
			{
				m_bReflectWaitTime = false;
			}
		}
	}
}

void AGBoxEnemyLong_Bullet::Shoot(AActor* pShooter, FVector vLocation, FVector vDestLoc)
{
	m_bShooted = true;
	m_pShooter = pShooter;
	SetActorLocation(vLocation);
	vDestLoc.Z = GetActorLocation().Z;
	FRotator rView = UKismetMathLibrary::FindLookAtRotation(vLocation, vDestLoc);

	SetActorRotation(rView);
}

void AGBoxEnemyLong_Bullet::Reflect(FVector vDestLoc)
{
	m_bReflected = true;
	m_bReflectWaitTime = true;
	FVector vLocation = GetActorLocation();
	FRotator rView = UKismetMathLibrary::FindLookAtRotation(vLocation, vDestLoc);
	SetActorRotation(rView);
}

float AGBoxEnemyLong_Bullet::TakeDamage(float DamageAmount, struct FDamageEvent const & DamageEvent, class AController * EventInstigator, AActor * DamageCauser)
{
	float fDamage = Super::TakeDamage(DamageAmount, DamageEvent, EventInstigator, DamageCauser);
	if (m_bReflected == true) return 0.0f;
	FDamageEvent_Hit* pDamageEvent = (FDamageEvent_Hit*)&DamageEvent;
	if (pDamageEvent != nullptr)
	{
		m_pDamageCauser = DamageCauser;
		Reflect(pDamageEvent->m_vHitPoint);
		m_fReflectDamage = DamageAmount;
	}

	return 0.0f;
}

void AGBoxEnemyLong_Bullet::Explosion()
{
	m_pParticleMng->SpawnParticleAtLocation(TEXT("Explosion"), GetWorld(), GetActorLocation(), FRotator::ZeroRotator, FVector::OneVector);
	Destroy();
}

void AGBoxEnemyLong_Bullet::OnOverlapBegin(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OtherActor && (OtherActor != this) && OtherComp)
	{
		if (OtherActor->ActorHasTag(FName(TEXT("Enemy"))) == true)
		{
			if (m_bReflected == true)
			{
				FDamageEvent* DamageEvent = new FDamageEvent_Hit(m_fReflectDamage, GetActorLocation(), GetActorLocation());
				float fResultDamage = OtherActor->TakeDamage(m_fReflectDamage, *DamageEvent, nullptr, m_pDamageCauser);

				Explosion();
			}
			else
			{
				return;
			}
		}

		if (OtherActor->ActorHasTag(FName(TEXT("Player"))) == true)
		{
			if (m_bReflected == true)
			{

			}
			else
			{
				FDamageEvent* DamageEvent = new FDamageEvent_Hit(3.0f, GetActorLocation(), GetActorLocation());
				float fResultDamage = OtherActor->TakeDamage(3.0f, *DamageEvent, nullptr, m_pShooter);
				if (fResultDamage != 0.0f)
				{
					Explosion();
				}
			}
		}
		else
		{
			Explosion();
		}

	}
}
