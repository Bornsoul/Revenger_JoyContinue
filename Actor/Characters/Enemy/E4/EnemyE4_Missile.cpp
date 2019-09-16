// Fill out your copyright notice in the Description page of Project Settings.

#include "EnemyE4_Missile.h"
#include "Actor/SaveData/Cpt_GameSave.h"
#include "Components/StaticMeshComponent.h"
#include "Components/SphereComponent.h"
#include "Libraries/Components/ParticleMng/Cpt_ParticleMng.h"
#include "Kismet/KismetMathLibrary.h"

AEnemyE4_Missile::AEnemyE4_Missile()
{
	PrimaryActorTick.bCanEverTick = true;
	Tags.Add(FName("EnemyBullet"));

	m_pCollider = CreateDefaultSubobject<USphereComponent>(TEXT("Collider"));
	m_pCollider->OnComponentBeginOverlap.AddDynamic(this, &AEnemyE4_Missile::OnOverlapBegin);
	m_pCollider->SetCollisionProfileName(TEXT("EnemyBullet"));

	RootComponent = m_pCollider;

	m_pMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	m_pMesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	m_pMesh->SetupAttachment(RootComponent);

	m_pParticleMng = CreateDefaultSubobject<UCpt_ParticleMng>(TEXT("ParticleMng"));
	m_pParticleMng->AddParticleInstance(TEXT("Explosion"), TEXT("ParticleSystem'/Game/1_Project_Main/2_Contents/Effects/Ex/StandardExplosion/P_Explosion_Small.P_Explosion_Small'"));
	m_pParticleMng->AddParticleInstance(TEXT("Trail"), TEXT("ParticleSystem'/Game/0_Assets/MarketPlace/VFXS/VFX_Toolkit_V1/ParticleSystems/356Days/Par_Matra_01b_Trail.Par_Matra_01b_Trail'"));

	//m_pSaveData = CreateDefaultSubobject<UCpt_GameSave>(TEXT("SaveData"));

}

void AEnemyE4_Missile::BeginPlay()
{
	Super::BeginPlay();
	m_bShooted = false;
	m_bReflected = false;
	m_bReflectWaitTime = false;
	m_bChase = false;
	m_bSuccessHit = false;
	//m_pParticleMng->SpawnParticleAttachComponent(TEXT("Trail"), m_pMesh, NAME_None);
}

void AEnemyE4_Missile::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	Super::EndPlay(EndPlayReason);
	m_pShooter = nullptr;
}

void AEnemyE4_Missile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	m_fLifeTime += DeltaTime;
	if (m_fLifeTime > 2.0f)
	{
		Destroy();
		return;
	}

	if (m_bShooted == true)
	{
		if (m_bReflected == false)
		{
			if (m_bChase == false && m_pTarget!=nullptr)
			{
				FVector vDestLoc = m_pTarget->GetActorLocation();
				vDestLoc.Z = GetActorLocation().Z;
				FRotator vAngleRota = UKismetMathLibrary::FindLookAtRotation(GetActorLocation(), vDestLoc);
				//float fAngle = FMath::Abs(GetActorRotation().Yaw - vAngleRota.Yaw);
				float fAngle = GetActorRotation().Yaw - vAngleRota.Yaw;
				vAngleRota.Roll = 0.0f;
				vAngleRota.Pitch = 0.0f;
				//FRotator vDestRota = UKismetMathLibrary::RInterpTo(GetActorRotation(), vAngleRota, DeltaTime, 13.0f);
				FRotator vDestRota = GetActorRotation();
				if (fAngle < 0.0f)
				{
					vDestRota.Yaw += 100.0f*DeltaTime;
				}
				else
				{
					vDestRota.Yaw -= 100.0f*DeltaTime;
				}
				SetActorRotation(vDestRota);
				if (fAngle > 100.0f) m_bChase = true;
			}
		}


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

void AEnemyE4_Missile::Shoot(AActor* pShooter, FVector vLocation, FVector vDestLoc)
{
	m_bShooted = true;
	m_pShooter = pShooter;
	SetActorLocation(vLocation);
	vDestLoc.Z = GetActorLocation().Z;
	FRotator rView = UKismetMathLibrary::FindLookAtRotation(vLocation, vDestLoc);

	SetActorRotation(rView);
}

void AEnemyE4_Missile::ShootToTarget(AActor* pShooter, FVector vLocation, AActor* pTarget)
{
	m_bShooted = true;
	m_pShooter = pShooter;
	m_pTarget = pTarget;

	FVector vDestLoc = m_pTarget->GetActorLocation();

	SetActorLocation(vLocation);
	vDestLoc.Z = GetActorLocation().Z;
	FRotator rView = UKismetMathLibrary::FindLookAtRotation(vLocation, vDestLoc);

	SetActorRotation(rView);
}

void AEnemyE4_Missile::Reflect(FVector vDestLoc)
{
	m_bReflected = true;
	m_bReflectWaitTime = true;
	FVector vLocation = GetActorLocation();
	FRotator rView = UKismetMathLibrary::FindLookAtRotation(vLocation, vDestLoc);
	SetActorRotation(rView);
	m_bSuccessHit = true;
	//ULOG(TEXT("Ref"));
}

float AEnemyE4_Missile::TakeDamage(float DamageAmount, struct FDamageEvent const & DamageEvent, class AController * EventInstigator, AActor * DamageCauser)
{
	float fDamage = Super::TakeDamage(DamageAmount, DamageEvent, EventInstigator, DamageCauser);
	if (m_bReflected == true) return 0.0f;
	FDamageEvent_Hit* pDamageEvent = (FDamageEvent_Hit*)&DamageEvent;
	if (pDamageEvent != nullptr)
	{
		//m_pSaveData->Load_Data()->m_stPlayerData.m_nHitBulletCount += 1;

		m_pDamageCauser = DamageCauser;
		Reflect(pDamageEvent->m_vHitPoint);
		m_fReflectDamage = DamageAmount;
	}

	return 0.0f;
}

void AEnemyE4_Missile::Explosion()
{
	//m_pSaveData->Save_Data("Test01", 0, -1.0f);
	m_pParticleMng->SpawnParticleAtLocation(TEXT("Explosion"), GetWorld(), GetActorLocation(), FRotator::ZeroRotator, FVector::OneVector);
	Destroy();
}

void AEnemyE4_Missile::OnOverlapBegin(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OtherActor && (OtherActor != this) && OtherComp)
	{
		if (OtherActor->ActorHasTag(FName(TEXT("Enemy"))) == true)
		{
			if (m_bReflected == true)
			{
				FDamageEvent* DamageEvent = new FDamageEvent_Hit(3, GetActorLocation(), GetActorLocation());
				float fResultDamage = OtherActor->TakeDamage(3, *DamageEvent, nullptr, m_pDamageCauser);

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
				return;
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
			//m_pSaveData->Load_Data()->m_stPlayerData.m_nNonHitBulletCount += 1;
			//UALERT(TEXT("%s"), *OtherActor->GetName().Left(8));
			if (OtherActor->GetName().Left(8) == "BP_Spawn")
			{
				return;
			}
			Explosion();
		}

	}
}

