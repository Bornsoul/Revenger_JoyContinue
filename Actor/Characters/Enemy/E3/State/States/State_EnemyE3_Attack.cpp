// Fill out your copyright notice in the Description page of Project Settings.

#include "State_EnemyE3_Attack.h"
#include "Libraries/Components/AnimationMng/Cpt_AnimationMng.h"
#include "Kismet/KismetMathLibrary.h"
#include "Libraries/Components/ParticleMng/Cpt_ParticleMng.h"
#include "Libraries/Components/CamShake/Cpt_CamShake.h"
#include "Libraries/Components/WarningSpace/Cpt_WarningSpace.h"
#include "Libraries/Components/WarningSpace/WarningSpace_Root.h"


void UState_EnemyE3_Attack::Init(class UStateMng_GC* pMng)
{
	Super::Init(pMng);

}

void UState_EnemyE3_Attack::Enter()
{
	Super::Enter();
	m_fReadyTime = 0.0f;
	m_bMotion = false;
	m_bAttacked = false;
	GetRootChar()->GetAnimationMng()->PlayAnimationSequnceBase(TEXT("Attack"), TEXT("DefaultSlot"), 0.1f, 0.2f, 1.0f);
	//GetRootChar()->GetAnimationMng()->PlayAnimationMontage(TEXT("AttackMtg"), 1.0f, TEXT("Ready"));
	GetRootChar()->GetAI()->StopMovement();
	GetRootChar()->GetAI()->SetActiveAI(false);
}

void UState_EnemyE3_Attack::Exit()
{
	Super::Exit();

	if (m_pWarning != nullptr)
	{
		m_pWarning->StopSpace();
		m_pWarning = nullptr;
	}

	m_pTarget = nullptr;
	GetRootChar()->GetAI()->SetActiveAI(true);
//	GetRootChar()->GetAnimationMng()->StopAnimation_Montage(TEXT("AttackMtg"));
	GetRootChar()->GetAnimationMng()->StopAnimation_SequnceBaseSlot(TEXT("DefaultSlot"), 0.2f);

}

void UState_EnemyE3_Attack::Update(float fDeltaTime)
{
	Super::Update(fDeltaTime);

	if (m_bAttacked == false)
	{
		if (m_pTarget != nullptr)
		{
			FVector vLookMousePos = m_pTarget->GetActorLocation();
			vLookMousePos.Z = GetRootChar()->GetActorLocation().Z;
			FRotator vInter = UKismetMathLibrary::RInterpTo(GetRootChar()->GetActorRotation(),
				UKismetMathLibrary::FindLookAtRotation(GetRootChar()->GetActorLocation(), vLookMousePos), fDeltaTime, 13.0f);
			GetRootChar()->SetActorRotation(vInter);

			//ULOG(TEXT("aaa"));

		}
	}


	if (m_bMotion)
	{
		ChangeState(static_cast<int32>(E_State_EnemyE3::E_Idle));
		return;
	}



	//Tick_Attack(fDeltaTime);
}

void UState_EnemyE3_Attack::StateMessage(FString StateMessage)
{
	Super::StateMessage(StateMessage);

	if (StateMessage == "MotionEnd")
	{
		m_bMotion = true;
	}
	else if (StateMessage == "AttackOn")
	{
		m_bAttacked = true;
		m_pWarning = GetRootChar()->GetWarningSpace()->SpawnSpace_Circle(0.5f, 1.0f,
			GetRootChar()->GetActorLocation() - FVector::UpVector*100.0f  + GetRootChar()->GetActorForwardVector() * 250.0f
			, FRotator::ZeroRotator, FVector::OneVector*2.0f);
	}
	else if (StateMessage == "AttackStart")
	{
		Attack();//GetRootChar()->GetActorLocation() - FVector::UpVector*230.0f +
		
	}
	else if (StateMessage == "AttackEnd")
	{
		AttackEnd();
	}
	else if (StateMessage == "AttackReady")
	{
		//GetRootChar()->GetParticleMng()->SpawnParticleAtLocation(TEXT("EyeLight"), 
		//	GetRootChar()->GetWorld(), GetRootChar()->GetMesh()->GetSocketLocation(TEXT("Soc_EyeLight")), FRotator::ZeroRotator, FVector::OneVector*1.0f);

		
	}
}

void UState_EnemyE3_Attack::Attack()
{
	//ULOG(TEXT("Attack Start"));
	m_bAttacked = true;
	m_bAttack = true;
	m_fAttackTime = 0.0f;
	m_sOverlapName.Empty();

}

void UState_EnemyE3_Attack::AttackEnd()
{
	//ULOG(TEXT("Attack End"));
	m_bAttack = false;
	m_fAttackTime = 0.0f;
	m_sOverlapName.Empty();
	GetRootChar()->GetParticleMng()->SpawnParticleAtLocation(TEXT("GroundHit"), GetRootChar()->GetWorld(), GetRootChar()->GetActorLocation() - FVector::UpVector*100.0f + GetRootChar()->GetActorForwardVector() * 150.0f
		, FRotator::ZeroRotator, FVector::OneVector*0.5f);
	Tick_Attack(0.0f);
}

void UState_EnemyE3_Attack::Tick_Attack(float fDeltaTime)
{
	//if (m_bAttack == false) return;
	EDrawDebugTrace::Type eDebug = EDrawDebugTrace::None;
	bool bDebug = false;
	if (bDebug == true)
	{
		eDebug = EDrawDebugTrace::ForDuration;
	}
	TArray<FHitResult> pHitResults;
	TArray<AActor*> pIgnore;
	pIgnore.Add(GetRootChar());

	//m_fAttackTime += fDeltaTime;
	//if (m_fAttackTime > 0.03f)
	{
		m_fAttackTime = 0.0f;

		FVector pTraceStart = GetRootChar()->GetActorLocation() + GetRootChar()->GetActorForwardVector();
		FVector pTraceEnd = pTraceStart + GetRootChar()->GetActorForwardVector() * 200.0f;

		UKismetSystemLibrary::BoxTraceMulti(GetRootChar()->GetWorld(), pTraceStart, pTraceEnd,
			FVector(20.0f, 100.0f, 50.0f), GetRootChar()->GetActorRotation(),
			UEngineTypes::ConvertToTraceType(ECC_GameTraceChannel1), true, pIgnore, eDebug, pHitResults, true);

		if (pHitResults.Num() <= 0) return;

		for (int i = 0; i < pHitResults.Num(); i++)
		{
			AActor* pHitActor = pHitResults[i].GetActor();
			if (pHitActor == nullptr) continue;
			if (pHitActor->ActorHasTag(FName(TEXT("Enemy"))) == true) continue;

			bool bOverlap = false;
			for (int j = 0; j < m_sOverlapName.Num(); j++)
			{
				if (m_sOverlapName[j] == pHitActor->GetName())
				{
					bOverlap = true;
					//	ULOG(TEXT("Overlap"));
					break;
				}
			}
			if (bOverlap == true) continue;
			m_sOverlapName.Add(pHitActor->GetName());

			if (pHitActor->ActorHasTag(FName(TEXT("Player"))) == true)
			{
				//ULOG(TEXT("Hit"));
				FDamageEvent* DamageEvent = new FDamageEvent_Hit(1.0f, GetRootChar()->GetActorLocation(), pHitResults[i].ImpactPoint);
				float fResultDamage = pHitActor->TakeDamage(1.0f, *DamageEvent, GetRootChar()->GetController(), GetRootChar());
				if (fResultDamage == 0.0f) continue;

				FRotator pLookRotation = UKismetMathLibrary::FindLookAtRotation(GetRootChar()->GetActorLocation(), pHitResults[i].ImpactPoint);
				GetRootChar()->GetParticleMng()->SpawnParticleAtLocation(TEXT("Hit"), GetRootChar()->GetWorld(), pHitResults[i].ImpactPoint, FRotator::ZeroRotator, FVector::OneVector*3.0f);
				
				//GetRootChar()->GetCamShake()->PlayCameraShake(TEXT("AttackHit"), 1.0f);

				GetRootChar()->GetAnimationMng()->Active_Stiffen(0.3f, 0.001f);

				//ULOG(TEXT("Attack Hit"));

			}
		}
	}
}
