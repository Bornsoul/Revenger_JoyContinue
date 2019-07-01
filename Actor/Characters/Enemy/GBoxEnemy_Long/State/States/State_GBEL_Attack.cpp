// Fill out your copyright notice in the Description page of Project Settings.

#include "State_GBEL_Attack.h"
#include "Libraries/Components/ParticleMng/Cpt_ParticleMng.h"
#include "Kismet/KismetMathLibrary.h"
#include "Libraries/Components/MaterialEffect/Cpt_MaterialEffect.h"
#include "Libraries/Components/AnimationMng/Cpt_AnimationMng.h"
#include "../../AnimInst_GBoxEnemy_Long.h"

void UState_GBEL_Attack::Init(class UStateMng_GC* pMng)
{
	Super::Init(pMng);
	m_bLeft = false;
}

void UState_GBEL_Attack::Enter()
{
	Super::Enter();

	if (m_pTargetActor == nullptr)
	{
		ChangeState(static_cast<int32>(E_State_GBELong::E_Idle));
		return;
	}

	m_pLaserParticle = GetRootChar()->GetParticleMng()->SpawnParticleAttachComponent(TEXT("Laser"), GetRootChar()->GetMesh(),
		TEXT("Bip001-Neck"), FVector::ZeroVector, FRotator::ZeroRotator, FVector::OneVector);

	//m_pLaserParticle = GetRootChar()->GetParticleMng()->SpawnParticleAtLocation(
	//	TEXT("Laser"), GetRootChar()->GetWorld(), GetRootCharacter()->GetActorLocation(), FRotator::ZeroRotator, FVector::OneVector);

	m_bLaserTime = true;
	m_fLaserTime = 0.0f;

	//GetRootChar()->GetAnimationMng()->PlayAnimationSequnceBase(sDirectionStr, TEXT("DefaultSlot"), 0.1f, 0.2f, 1.0f);
	//GetRootChar()->GetAnimationMng()->PlayAnimationMontage(TEXT("Attack"), 1.0f, *sDirectionStr);
	GetRootChar()->GetAnimationMng()->PlayAnimationMontage(TEXT("Attack"), 1.0f, TEXT("Ready"));

	GetRootChar()->GetParticleMng()->SpawnParticleAttachComponent(TEXT("EyeLight"), GetRootChar()->GetMesh(),
		TEXT("Soc_EyeLight"), FVector::ZeroVector, FRotator::ZeroRotator, FVector::OneVector*1.0f);

	GetRootChar()->GetAI()->StopMovement();
	GetRootChar()->GetAI()->SetActiveAI(false);

}

void UState_GBEL_Attack::Exit()
{
	Super::Exit();

	m_bLeft = !m_bLeft;
	GetRootChar()->GetAI()->SetActiveAI(true);
	GetRootChar()->GetAnimationMng()->StopAnimation_SequnceBaseSlot(TEXT("DefaultSlot"), 0.2f);
	m_pTargetActor = nullptr;
	if (m_pLaserParticle != nullptr) m_pLaserParticle->DestroyComponent();
	m_pLaserParticle = nullptr;
}

void UState_GBEL_Attack::Update(float fDeltaTime)
{
	Super::Update(fDeltaTime);

	if (m_pTargetActor == nullptr) return;
	FVector vLookMousePos = m_pTargetActor->GetActorLocation();

	vLookMousePos.Z = GetRootChar()->GetActorLocation().Z;
	//GetRootChar()->SetActorRotation(UKismetMathLibrary::FindLookAtRotation(GetRootChar()->GetActorLocation(), vLookMousePos));
	GetRootChar()->HeadRotator_Use(UKismetMathLibrary::FindLookAtRotation(GetRootChar()->GetActorLocation(), vLookMousePos), fDeltaTime);

	//GetRootChar()->GetMesh()->BoneSpaceTransforms


	if (m_bLaserTime == true)
	{
		if (m_pLaserParticle != nullptr)
		{
			m_pLaserParticle->SetBeamEndPoint(0, m_pTargetActor->GetActorLocation());
		}
		m_fLaserTime += fDeltaTime;
		if (m_fLaserTime > m_fLaserTime_Ago)
		{
			m_bLaserTime = false;
			if (m_pLaserParticle != nullptr)
			{
				m_pLaserParticle->DestroyComponent();
				m_pLaserParticle = nullptr;
			}

			FString sDirectionStr = "Attack_L";
			if (m_bLeft == false)
			{
				sDirectionStr = "Attack_R";
			}

			GetRootChar()->GetAnimationMng()->PlayAnimationMontage(TEXT("Attack"), 1.0f, *sDirectionStr);
			
		}
	}
}

void UState_GBEL_Attack::StateMessage(FString StateMessage)
{
	Super::StateMessage(StateMessage);
	if (StateMessage == "MotionEnd")
	{
		ChangeState(static_cast<int32>(E_State_GBELong::E_Idle));
	}
	else  if (StateMessage == "Attack")
	{
		if (m_pTargetActor == nullptr) return;
		FVector vTargetPos = m_pTargetActor->GetActorLocation();
		
		FString sDirectionStr = "Soc_Fire_L";
		if (m_bLeft == false)
		{
			sDirectionStr = "Soc_Fire_R";
		}
		FVector vShootLoc = GetRootChar()->GetMesh()->GetSocketLocation(*sDirectionStr);
		vTargetPos.Z = vShootLoc.Z;
		GetRootChar()->CreateBullet(vShootLoc, m_pTargetActor->GetActorLocation());
	}
	else if (StateMessage == "ShellOut")
	{

	}

}

void UState_GBEL_Attack::SetTarget(class AActor* pTarget)
{
	m_pTargetActor = pTarget;
}