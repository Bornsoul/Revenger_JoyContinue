// Fill out your copyright notice in the Description page of Project Settings.

#include "State_GBEC_DashAttack.h"
#include "Libraries/Components/AnimationMng/Cpt_AnimationMng.h"
#include "Kismet/KismetMathLibrary.h"
#include "Libraries/Components/ParticleMng/Cpt_ParticleMng.h"
#include "Libraries/Components/CamShake/Cpt_CamShake.h"
#include "Libraries/Components/WarningSpace/Cpt_WarningSpace.h"
#include "Libraries/Components/WarningSpace/WarningSpace_Root.h"

void UState_GBEC_DashAttack::Init(class UStateMng_GC* pMng)
{
	Super::Init(pMng);

}

void UState_GBEC_DashAttack::Enter()
{
	Super::Enter();
	m_bMotion = false;
	m_bRotation = true;
	m_bAttackAgo = false;
	m_bAttack = false;
	m_fAttackAgoTime = 0.0f;
	m_fAttackAgoTime_Ago = UKismetMathLibrary::RandomFloatInRange(0.5f, 1.5f);

	GetRootChar()->GetAnimationMng()->PlayAnimationMontage(TEXT("DashAttack"), 1.0f, TEXT("Start"));
	

	GetRootChar()->GetAI()->StopMovement();
	GetRootChar()->GetAI()->SetActiveAI(false);
}

void UState_GBEC_DashAttack::Exit()
{
	Super::Exit();
	GetRootChar()->GetAI()->SetActiveAI(true);
	GetRootChar()->SetIgnoreCollision_Pawn(false);
	GetRootChar()->GetAnimationMng()->StopAnimation_Montage(TEXT("DashAttack"));
	if (m_pWarning != nullptr)
	{
		m_pWarning->StopSpace();
		m_pWarning = nullptr;
	}

}

void UState_GBEC_DashAttack::Update(float fDeltaTime)
{
	Super::Update(fDeltaTime);

	if (m_bRotation == true)
	{
		FVector vLookMousePos = m_pTarget->GetActorLocation();
		vLookMousePos.Z = GetRootChar()->GetActorLocation().Z;
		FRotator vInter = UKismetMathLibrary::RInterpTo(GetRootChar()->GetActorRotation(),
			UKismetMathLibrary::FindLookAtRotation(GetRootChar()->GetActorLocation(), vLookMousePos), fDeltaTime, 7.0f);
		GetRootChar()->SetActorRotation(vInter);
	}


	if (m_bMotion)
	{
		ChangeState(static_cast<int32>(E_State_GBEClose::E_Idle));
		return;
	}


	if (m_bAttackAgo == true)
	{
		m_fAttackAgoTime += fDeltaTime;
		if (m_fAttackAgoTime > m_fAttackAgoTime_Ago)
		{
			m_bRotation = false;
			m_bAttackAgo = false;
			m_fAttackAgoTime = 0.0f;
			GetRootChar()->GetAnimationMng()->PlayAnimationMontage(TEXT("DashAttack"), 1.0f, TEXT("Shoot"));
		}
	}


	//Tick_Attack(fDeltaTime);
}

void UState_GBEC_DashAttack::StateMessage(FString StateMessage)
{
	Super::StateMessage(StateMessage);

	if (StateMessage == "MotionEnd")
	{
		m_bMotion = true;
	}
	else if (StateMessage == "AttackReady")
	{

		FRotator pRota = UKismetMathLibrary::FindLookAtRotation(GetRootChar()->GetActorLocation(), m_pTarget->GetActorLocation());
		pRota.Roll = 0.0f;
		pRota.Pitch = 0.0f;
		m_pAttackRotator = pRota;

		m_pStartPOs = GetRootChar()->GetActorLocation();
		m_pWarning = GetRootChar()->GetWarningSpace()->SpawnSpace_Dash(0.7f,
			GetRootChar()->GetActorLocation() + GetRootChar()->GetActorForwardVector()*400.0f - FVector::UpVector*230.0f
			, pRota, FVector::OneVector*15.0f);
	}
	else if (StateMessage == "AttackAgo")
	{
		m_bAttackAgo = true;
	}
	else if (StateMessage == "AttackStart")
	{
		m_bAttack = true;
		GetRootChar()->SetIgnoreCollision_Pawn(true);

		EDrawDebugTrace::Type eDebug = EDrawDebugTrace::None;
		bool bDebug = false;
		if (bDebug == true)
		{
			eDebug = EDrawDebugTrace::ForDuration;
		}
		TArray<FHitResult> pHitResults;
		TArray<AActor*> pIgnore;
		pIgnore.Add(GetRootChar());

		FVector pTraceStart = m_pStartPOs - (FVector::UpVector*230.0f) + (GetRootChar()->GetActorForwardVector()*100.0f);// +GetRootChar()->GetActorForwardVector();
		FVector pTraceEnd = pTraceStart + GetRootChar()->GetActorForwardVector() * 850.0f;


		UKismetSystemLibrary::BoxTraceMulti(GetRootChar()->GetWorld(), pTraceStart, pTraceEnd, FVector::OneVector*200.0f,
			m_pAttackRotator, UEngineTypes::ConvertToTraceType(ECC_GameTraceChannel1), true, pIgnore, eDebug, pHitResults, true);

		if (pHitResults.Num() <= 0) return;

		for (int i = 0; i < pHitResults.Num(); i++)
		{
			AActor* pHitActor = pHitResults[i].GetActor();
			if (pHitActor == nullptr) continue;
			if (pHitActor->ActorHasTag(FName(TEXT("Enemy"))) == true) continue;

			if (pHitActor->ActorHasTag(FName(TEXT("Player"))) == true)
			{
				//ULOG(TEXT("Hit"));
				FDamageEvent* DamageEvent = new FDamageEvent_Hit(1.0f, GetRootChar()->GetActorLocation(), pHitResults[i].ImpactPoint);
				float fResultDamage = pHitActor->TakeDamage(1.0f, *DamageEvent, GetRootChar()->GetController(), GetRootChar());
				if (fResultDamage == 0.0f) continue;

				FRotator pLookRotation = UKismetMathLibrary::FindLookAtRotation(GetRootChar()->GetActorLocation(), pHitResults[i].ImpactPoint);
				GetRootChar()->GetParticleMng()->SpawnParticleAtLocation(TEXT("Hit"), GetRootChar()->GetWorld(), pHitResults[i].ImpactPoint, FRotator::ZeroRotator, FVector::OneVector*3.0f);
				//GetRootChar()->GetParticleMng()->SpawnParticleAtLocation(TEXT("Hit_Back"), GetRootChar()->GetWorld(), pHitResults[i].ImpactPoint, pLookRotation, FVector::OneVector*1.5f);
				//GetRootChar()->GetCamShake()->PlayCameraShake(TEXT("AttackHit"), 1.0f);

				GetRootChar()->GetAnimationMng()->Active_Stiffen(0.3f, 0.001f);

				//ULOG(TEXT("Attack Hit"));

			}
		}

	//	UKismetSystemLibrary::SphereTraceMulti(GetRootChar()->GetWorld(), pTraceStart, pTraceStart,
		//	400.0f, UEngineTypes::ConvertToTraceType(ECC_GameTraceChannel1), true, pIgnore, eDebug, pHitResults, true);


	}
	else if (StateMessage == "AttackEnd")
	{
		m_bAttack = false;
		GetRootChar()->SetIgnoreCollision_Pawn(false);
	}

}
