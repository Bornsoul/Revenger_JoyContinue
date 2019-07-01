// Fill out your copyright notice in the Description page of Project Settings.

#include "State_EnemyE4_Attack.h"
#include "Libraries/Components/ParticleMng/Cpt_ParticleMng.h"
#include "Kismet/KismetMathLibrary.h"
#include "Libraries/Components/MaterialEffect/Cpt_MaterialEffect.h"
#include "Libraries/Components/AnimationMng/Cpt_AnimationMng.h"

void UState_EnemyE4_Attack::Init(class UStateMng_GC* pMng)
{
	Super::Init(pMng);

}

void UState_EnemyE4_Attack::Enter()
{
	Super::Enter();
	if (m_pTargetActor == nullptr)
	{
		ChangeState(static_cast<int32>(E_State_EnemyE4::E_Idle));
		return;
	}



	//m_pLaserParticle = GetRootChar()->GetParticleMng()->SpawnParticleAtLocation(
	//	TEXT("Laser"), GetRootChar()->GetWorld(), GetRootCharacter()->GetActorLocation(), FRotator::ZeroRotator, FVector::OneVector);

	m_bLaserTime = false;
	m_fLaserTime = 0.0f;

	//GetRootChar()->GetAnimationMng()->PlayAnimationSequnceBase(TEXT("Attack"), TEXT("DefaultSlot"), 0.1f, 0.2f, 1.0f);
	//GetRootChar()->GetAnimationMng()->PlayAnimationMontage(TEXT("Attack"), 1.0f, *sDirectionStr);
	GetRootChar()->GetAnimationMng()->PlayAnimationMontage(TEXT("Attack"), 1.0f, TEXT("Ready"));

	//GetRootChar()->GetParticleMng()->SpawnParticleAttachComponent(TEXT("EyeLight"), GetRootChar()->GetMesh(),
	//	TEXT("Soc_EyeLight"), FVector::ZeroVector, FRotator::ZeroRotator, FVector::OneVector*1.0f);

	//GetRootChar()->GetAI()->StopMovement();
	//GetRootChar()->GetAI()->SetActiveAI(false);
}

void UState_EnemyE4_Attack::Exit()
{
	Super::Exit();
	m_bLeft = !m_bLeft;
	//GetRootChar()->GetAI()->SetActiveAI(true);
	GetRootChar()->GetAnimationMng()->StopAnimation_Montage(TEXT("Attack"));
	//GetRootChar()->GetAnimationMng()->StopAnimation_SequnceBaseSlot(TEXT("DefaultSlot"), 0.2f);
	m_pTargetActor = nullptr;
	if (m_pLaserParticle != nullptr) m_pLaserParticle->DestroyComponent();
	m_pLaserParticle = nullptr;

}

void UState_EnemyE4_Attack::Update(float fDeltaTime)
{
	Super::Update(fDeltaTime);

	if (m_pTargetActor == nullptr) return;
	FVector vLookMousePos = m_pTargetActor->GetActorLocation();

	vLookMousePos.Z = GetRootChar()->GetActorLocation().Z;
	GetRootChar()->SetActorRotation(UKismetMathLibrary::FindLookAtRotation(GetRootChar()->GetActorLocation(), vLookMousePos));
	//GetRootChar()->HeadRotator_Use(UKismetMathLibrary::FindLookAtRotation(GetRootChar()->GetActorLocation(), vLookMousePos), fDeltaTime);

	if (m_pLaserParticle != nullptr)
	{
		m_pLaserParticle->SetBeamEndPoint(0, m_pTargetActor->GetActorLocation());
	}

	if (m_bLaserTime == true)
	{
		m_fLaserTime += fDeltaTime; 
		if (m_fLaserTime >= m_fLaserTime_Ago)
		{
			GetRootChar()->GetAI()->StopMovement();			
			GetRootChar()->GetAnimationMng()->PlayAnimationMontage(TEXT("Attack"), 1.0f, TEXT("Shoot"));
			m_bLaserTime = false;
			m_fLaserTime = 0.0f;
		}
	}

	//Tick_Attack(fDeltaTime);
}

void UState_EnemyE4_Attack::StateMessage(FString StateMessage)
{
	Super::StateMessage(StateMessage);

	if (StateMessage == "MotionEnd")
	{
		ChangeState(static_cast<int32>(E_State_EnemyE4::E_Idle));
		//m_bMotion = true;
	}
	else if (StateMessage == "Attack")
	{
		if (m_pLaserParticle != nullptr)
		{
			m_pLaserParticle->DestroyComponent();
			m_pLaserParticle = nullptr;
		}

		FVector vTargetPos = m_pTargetActor->GetActorLocation();
		FString sDirectionStr = "Soc_Fire";

		FVector vShootLoc = GetRootChar()->GetMesh()->GetSocketLocation(*sDirectionStr);
		vTargetPos.Z = vShootLoc.Z;
			
		GetRootChar()->CreateBullet(vShootLoc, m_pTargetActor);
	}
	else if (StateMessage == "AttackReady")
	{
		m_pLaserParticle = GetRootChar()->GetParticleMng()->SpawnParticleAttachComponent(TEXT("Laser"), GetRootChar()->GetMesh(),
			TEXT("Soc_Fire"), FVector::ZeroVector, FRotator::ZeroRotator, FVector::OneVector);
		m_bLaserTime = true;
	}
	
}


