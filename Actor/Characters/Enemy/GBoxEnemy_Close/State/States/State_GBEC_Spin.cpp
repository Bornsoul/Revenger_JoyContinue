// Fill out your copyright notice in the Description page of Project Settings.

#include "State_GBEC_Spin.h"
#include "Libraries/Components/AnimationMng/Cpt_AnimationMng.h"
#include "Kismet/KismetMathLibrary.h"
#include "Libraries/Components/ParticleMng/Cpt_ParticleMng.h"
#include "Libraries/Components/CamShake/Cpt_CamShake.h"
#include "Libraries/Components/WarningSpace/Cpt_WarningSpace.h"
#include "Libraries/Components/WarningSpace/WarningSpace_Root.h"


void UState_GBEC_Spin::Init(class UStateMng_GC* pMng)
{
	Super::Init(pMng);

}

void UState_GBEC_Spin::Enter()
{
	Super::Enter();
	m_bMotion = false;
	GetRootChar()->GetAnimationMng()->PlayAnimationSequnceBase(TEXT("Spin"), TEXT("DefaultSlot"), 0.1f, 0.2f, 1.0f);
	GetRootChar()->GetAI()->StopMovement();
	GetRootChar()->GetAI()->SetActiveAI(false);
}

void UState_GBEC_Spin::Exit()
{
	Super::Exit();
	GetRootChar()->GetAI()->SetActiveAI(true);
	GetRootChar()->SetIgnoreCollision_Pawn(false);
	GetRootChar()->GetAnimationMng()->StopAnimation_SequnceBaseSlot(TEXT("DefaultSlot"), 0.2f);

	if (m_pWarning != nullptr)
	{
		m_pWarning->StopSpace();
		m_pWarning = nullptr;
	}

}

void UState_GBEC_Spin::Update(float fDeltaTime)
{
	Super::Update(fDeltaTime);




	if (m_bMotion)
	{
		ChangeState(static_cast<int32>(E_State_GBEClose::E_Idle));
		return;
	}



	//Tick_Attack(fDeltaTime);
}

void UState_GBEC_Spin::StateMessage(FString StateMessage)
{
	Super::StateMessage(StateMessage);

	if (StateMessage == "MotionEnd")
	{
		m_bMotion = true;
	}
	else if (StateMessage == "Attack")
	{
		EDrawDebugTrace::Type eDebug = EDrawDebugTrace::None;
		bool bDebug = false;
		if (bDebug == true)
		{
			eDebug = EDrawDebugTrace::ForDuration;
		}
		TArray<FHitResult> pHitResults;
		TArray<AActor*> pIgnore;
		pIgnore.Add(GetRootChar());


		{


			FVector pTraceStart = GetRootChar()->GetActorLocation() - FVector::UpVector*230.0f;// +GetRootChar()->GetActorForwardVector();
			FVector pTraceEnd = pTraceStart + GetRootChar()->GetActorForwardVector() * 250.0f;

			UKismetSystemLibrary::SphereTraceMulti(GetRootChar()->GetWorld(), pTraceStart, pTraceStart,
				400.0f, UEngineTypes::ConvertToTraceType(ECC_GameTraceChannel1), true, pIgnore, eDebug, pHitResults, true);

		//	UKismetSystemLibrary::BoxTraceMulti(GetRootChar()->GetWorld(), pTraceStart, pTraceEnd,
		//		FVector(20.0f, 200.0f, 50.0f), GetRootChar()->GetActorRotation(),
			//	UEngineTypes::ConvertToTraceType(ECC_GameTraceChannel1), true, pIgnore, eDebug, pHitResults, true);

			if (pHitResults.Num() <= 0) return;

			for (int i = 0; i < pHitResults.Num(); i++)
			{
				AActor* pHitActor = pHitResults[i].GetActor();
				if (pHitActor == nullptr) continue;
				if (pHitActor->ActorHasTag(FName(TEXT("Enemy"))) == true) continue;

				if (pHitActor->ActorHasTag(FName(TEXT("Player"))) == true)
				{
					FDamageEvent* DamageEvent = new FDamageEvent_Hit(1.0f, GetRootChar()->GetActorLocation(), pHitResults[i].ImpactPoint);
					float fResultDamage = pHitActor->TakeDamage(1.0f, *DamageEvent, GetRootChar()->GetController(), GetRootChar());
					if (fResultDamage == 0.0f) continue;

					FRotator pLookRotation = UKismetMathLibrary::FindLookAtRotation(GetRootChar()->GetActorLocation(), pHitResults[i].ImpactPoint);
					GetRootChar()->GetParticleMng()->SpawnParticleAtLocation(TEXT("Hit"), GetRootChar()->GetWorld(), pHitResults[i].ImpactPoint, FRotator::ZeroRotator, FVector::OneVector*3.0f);
					//GetRootChar()->GetParticleMng()->SpawnParticleAtLocation(TEXT("Hit_Back"), GetRootChar()->GetWorld(), pHitResults[i].ImpactPoint, pLookRotation, FVector::OneVector*1.5f);
					//GetRootChar()->GetCamShake()->PlayCameraShake(TEXT("AttackHit"), 1.0f);

					GetRootChar()->GetAnimationMng()->Active_Stiffen(0.3f, 0.001f);

				}
			}
		}

	}
	else if (StateMessage == "AttackReady")
	{
		//GetRootChar()->GetParticleMng()->SpawnParticleAtLocation(TEXT("EyeLight"), 
		//	GetRootChar()->GetWorld(), GetRootChar()->GetMesh()->GetSocketLocation(TEXT("Soc_EyeLight")), FRotator::ZeroRotator, FVector::OneVector*1.0f);
		m_pWarning = GetRootChar()->GetWarningSpace()->SpawnSpace_Circle(0.7f, 1.0f,
			GetRootChar()->GetActorLocation() - FVector::UpVector*230.0f
			, FRotator::ZeroRotator, FVector::OneVector*8.5f);
		GetRootChar()->GetParticleMng()->SpawnParticleAttachComponent(TEXT("EyeLight"), GetRootChar()->GetMesh(),
			TEXT("Soc_EyeLight"), FVector::ZeroVector, FRotator::ZeroRotator, FVector::OneVector*1.0f);
	}
}