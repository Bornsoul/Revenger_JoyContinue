// Fill out your copyright notice in the Description page of Project Settings.

#include "State_EnemyE5_Attack.h"
#include "Actor/Characters/Enemy/E5/AIC_EnemyE5.h"
#include "Libraries/Components/ParticleMng/Cpt_ParticleMng.h"
#include "Libraries/Components/MaterialEffect/Cpt_MaterialEffect.h"
#include "Libraries/Components/AnimationMng/Cpt_AnimationMng.h"
#include "Kismet/KismetMathLibrary.h"

void UState_EnemyE5_Attack::Init(class UStateMng_GC* pMng)
{
	Super::Init(pMng);

}

void UState_EnemyE5_Attack::Enter()
{
	Super::Enter();

	if (m_pTargetActor == nullptr)
	{
		ChangeState(static_cast<int32>(E_State_EnemyE5::E_Idle));
		return;
	}

	m_bLaserTime = true;
	m_bAttackTime = false;
	m_fLaserTime = 0.0f;
	m_nFireCount = 0;
	m_fAttackTime_Cur = 0.0f;

	//GetRootChar()->SetCombatState(true);
	//GetRootChar()->GetAnimationMng()->PlayAnimationMontage(TEXT("Attack"), 1.0f, TEXT("Ready"));
	//GetRootChar()->GetAI()->StopMovement();
	//GetRootChar()->GetAI()->SetActiveAI(false);
	GetRootChar()->SetShoot(true);
}

void UState_EnemyE5_Attack::Exit()
{
	Super::Exit();

	m_bLeft = !m_bLeft;
	GetRootChar()->SetCombatState(false);
	//GetRootChar()->GetAI()->SetActiveAI(true);
	GetRootChar()->SetShoot(false);

	GetRootChar()->GetAnimationMng()->StopAnimation_Montage(TEXT("Attack"));

	m_pTargetActor = nullptr;
	if (m_pLaserParticle != nullptr) m_pLaserParticle->DestroyComponent();
	m_pLaserParticle = nullptr;

	if (m_pLaserParticleL != nullptr) m_pLaserParticleL->DestroyComponent();
	m_pLaserParticleL = nullptr;
}

void UState_EnemyE5_Attack::Update(float fDeltaTime)
{
	Super::Update(fDeltaTime);

	if (m_bAttackTime == false)
	{
		m_fAttackTime_Cur += fDeltaTime;
		if (m_fAttackTime_Cur >= m_fAttackTime_End)
		{
			m_fAttackTime_Cur = 0.0f;

			GetRootChar()->GetAnimationMng()->PlayAnimationMontage(TEXT("Attack"), 1.0f, TEXT("Ready"));
			GetRootChar()->GetAI()->StopMovement();
			GetRootChar()->SetCombatState(true);
			m_bAttackTime = true;
		}
	}

	if (m_pTargetActor == nullptr) return;
	FVector vLookMousePos = m_pTargetActor->GetActorLocation();

	vLookMousePos.Z = GetRootChar()->GetActorLocation().Z;
	GetRootChar()->SetActorRotation(UKismetMathLibrary::FindLookAtRotation(GetRootChar()->GetActorLocation(), vLookMousePos));

	if (m_pLaserParticle != nullptr)
	{
		m_pLaserParticle->SetBeamEndPoint(0, m_pTargetActor->GetActorLocation());
	}

	if (m_pLaserParticleL != nullptr)
	{
		m_pLaserParticleL->SetBeamEndPoint(0, m_pTargetActor->GetActorLocation());
	}
}

void UState_EnemyE5_Attack::StateMessage(FString StateMessage)
{
	Super::StateMessage(StateMessage);

	if (StateMessage == "MotionEnd")
	{
		ChangeState(static_cast<int32>(E_State_EnemyE5::E_Idle));
		//m_bMotion = true;
	}
	else if (StateMessage == "AttackL")
	{
		if (m_pLaserParticle != nullptr)
		{
			m_pLaserParticle->DestroyComponent();
			m_pLaserParticle = nullptr;
		}

		if (m_pLaserParticleL != nullptr)
		{
			m_pLaserParticleL->DestroyComponent();
			m_pLaserParticleL = nullptr;
		}

		FVector vTargetPos = m_pTargetActor->GetActorLocation();

		FString sDirectionStr = "Soc_FireL";

		FVector vShootLoc = GetRootChar()->GetMesh()->GetSocketLocation(*sDirectionStr);
		vTargetPos.Z = vShootLoc.Z;

		GetRootChar()->CreateBullet(vShootLoc, m_pTargetActor);
	}
	else if (StateMessage == "AttackR")
	{
		if (m_pLaserParticle != nullptr)
		{
			m_pLaserParticle->DestroyComponent();
			m_pLaserParticle = nullptr;
		}

		if (m_pLaserParticleL != nullptr)
		{
			m_pLaserParticleL->DestroyComponent();
			m_pLaserParticleL = nullptr;
		}

		FVector vTargetPos = m_pTargetActor->GetActorLocation();

		FString sDirectionStr = "Soc_FireR";

		FVector vShootLoc = GetRootChar()->GetMesh()->GetSocketLocation(*sDirectionStr);
		vTargetPos.Z = vShootLoc.Z;

		GetRootChar()->CreateBullet(vShootLoc, m_pTargetActor);
	}
	else if (StateMessage == "AttackReady")
	{
		m_pLaserParticle = GetRootChar()->GetParticleMng()->SpawnParticleAttachComponent(TEXT("Laser"), GetRootChar()->GetMesh(),
			TEXT("Soc_FireR"), FVector::ZeroVector, FRotator::ZeroRotator, FVector::OneVector);

		m_pLaserParticleL = GetRootChar()->GetParticleMng()->SpawnParticleAttachComponent(TEXT("Laser"), GetRootChar()->GetMesh(),
			TEXT("Soc_FireL"), FVector::ZeroVector, FRotator::ZeroRotator, FVector::OneVector);
	}
	else if (StateMessage == "AttackEnd")
	{
		if (m_nFireCount >= 2) return;
		GetRootChar()->GetAnimationMng()->PlayAnimationMontage(TEXT("Attack"), 1.0f, TEXT("loop"));
		
		m_nFireCount += 1; 
	}
}
