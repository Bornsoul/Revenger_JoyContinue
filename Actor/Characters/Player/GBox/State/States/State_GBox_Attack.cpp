// Fill out your copyright notice in the Description page of Project Settings.

#include "State_GBox_Attack.h"
#include "Libraries/Components/AnimationMng/Cpt_AnimationMng.h"
#include "Kismet/KismetMathLibrary.h"
#include "Libraries/Components/ParticleMng/Cpt_ParticleMng.h"
#include "Libraries/Components/CamShake/Cpt_CamShake.h"
#include "Libraries/Components/MouseMng/Cpt_MouseLandMng.h"
#include "Libraries/Components/SoundMng/Cpt_SoundMng.h"
#include "Libraries/Components/PostProcessEffect/Cpt_PostProcessEffect.h"

void UState_GBox_Attack::Init(class UStateMng_GC* pMng)
{
	Super::Init(pMng);

}

void UState_GBox_Attack::Enter()
{
	Super::Enter();

	m_bMotionEnd = false;
	m_bRotation = false;
	m_bAttack = false;
	m_bAttackMotionEnd = false;
	m_bAttackRetryEnd = false;

	m_fAttackTime = 0.0f;
	m_sOverlapName.Empty();

	FVector vLookMousePos = GetRootChar()->GetMouseMng()->GetMouse_Location();
	vLookMousePos.Z = GetRootChar()->GetActorLocation().Z;
	GetRootChar()->SetActorRotation(UKismetMathLibrary::FindLookAtRotation(GetRootChar()->GetActorLocation(), vLookMousePos));

	GetRootChar()->GetAnimationMng()->PlayAnimationSequnceBase(TEXT("Attack"), TEXT("DefaultSlot"), 0.0f, 0.2f, 1.0f);


	//FVector vPushDirection = GetRootChar()->GetActorForwardVector();
	//vPushDirection.Normalize();
	//vPushDirection.Z = 0.0f;
//	GetRootChar()->GetCharacterMovement()->AddImpulse(vPushDirection * 15000.0f, true);

}

void UState_GBox_Attack::Exit()
{
	Super::Exit();

	
	m_vMouseLoc = FVector::ZeroVector;
	GetRootChar()->GetAnimationMng()->StopAnimation_SequnceBaseSlot(TEXT("DefaultSlot"), 0.2f);
}

void UState_GBox_Attack::Update(float fDeltaTime)
{
	Super::Update(fDeltaTime);
	if (m_bRotation) SetRotateMotion(fDeltaTime, m_vMouseLoc, 100.0f);

	if (m_bMotionEnd)
	{
		ChangeState(static_cast<int32>(E_State_GBox::E_Idle));
		return;
	}

	if (m_bAttackMotionEnd == true)
	{
		if (GetRootChar()->GetKeyStateMng()->GetAnyKeyIsDown() == true)
		{
			ChangeState(static_cast<int32>(E_State_GBox::E_Idle));
			return;
		}
	}

	if (m_bAttackRetryEnd == true)
	{
		if (GetRootChar()->GetKeyStateMng()->GetKeyIsJustPress(EKeys::LeftMouseButton))
		{
			FVector vMouse = GetRootChar()->GetMouseMng()->GetMouse_Location();

			if (GetRootChar()->Control_Attack(vMouse))
			{
				return;
			}

		}
	}

	if (GetRootChar()->GetKeyStateMng()->GetKeyIsJustPress(EKeys::RightMouseButton))
	{
		if (GetRootChar()->Control_Dodge())
		{
			return;
		}
	}

	Tick_Attack(fDeltaTime);
}

void UState_GBox_Attack::StateMessage(FString StateMessage)
{
	Super::StateMessage(StateMessage);

	if (StateMessage == "MotionEnd")
	{
		
		m_bMotionEnd = true;
	}
	else if (StateMessage == "RotationStart")
	{
		m_bRotation = true;
	}
	else if (StateMessage == "RotationEnd")
	{
		m_bRotation = false;
	}
	else if (StateMessage == "AttackStart")
	{
		Attack();
	}
	else if (StateMessage == "AttackEnd")
	{
		AttackEnd();
	}
	else if (StateMessage == "AttackMotionEnd")
	{
		m_bAttackMotionEnd = true;
	}
	else if (StateMessage == "AttackRetry")
	{
		m_bAttackRetryEnd = true;
	}

}

void UState_GBox_Attack::SetDirection(FVector vLoc)
{
	m_vMouseLoc = vLoc;
}

void UState_GBox_Attack::SetRotateMotion(float fDeltaTime, FVector vLook, float fSpeed)
{
	FRotator pLookRotation = UKismetMathLibrary::FindLookAtRotation(GetRootChar()->GetActorLocation(), vLook);
	pLookRotation.Pitch = 0.0f;
	pLookRotation.Roll = 0.0f;
	FRotator pInterp = UKismetMathLibrary::RInterpTo(GetRootChar()->GetActorRotation(), pLookRotation, fDeltaTime, fSpeed);

	GetRootChar()->SetActorRotation(pInterp);
}


void UState_GBox_Attack::Attack()
{
	//ULOG(TEXT("Attack Start"));
	m_bAttack = true;
	m_fAttackTime = 0.0f;
	m_sOverlapName.Empty();
}

void UState_GBox_Attack::AttackEnd()
{
	//ULOG(TEXT("Attack End"));
	m_bAttack = false;
	m_fAttackTime = 0.0f;
	m_sOverlapName.Empty();
}

void UState_GBox_Attack::Tick_Attack(float fDeltaTime)
{
	if (m_bAttack == false) return;
	EDrawDebugTrace::Type eDebug = EDrawDebugTrace::None;
	bool bDebug = false;
	if (bDebug == true)
	{
		eDebug = EDrawDebugTrace::ForDuration;
	}
	TArray<FHitResult> pHitResults;
	TArray<AActor*> pIgnore;
	pIgnore.Add(GetRootChar());

	m_fAttackTime += fDeltaTime;
	bool bHited = false;
	if (m_fAttackTime > 0.03f)
	{
		m_fAttackTime = 0.0f;

		FVector pTraceStart = GetRootChar()->GetActorLocation() + GetRootChar()->GetActorForwardVector();
		FVector pTraceEnd = pTraceStart + GetRootChar()->GetActorForwardVector() * 200.0f;

		UKismetSystemLibrary::BoxTraceMulti(GetRootChar()->GetWorld(), pTraceStart, pTraceEnd,
			FVector(20.0f, 160.0f, 50.0f), GetRootChar()->GetActorRotation(),
			UEngineTypes::ConvertToTraceType(ECC_GameTraceChannel1), true, pIgnore, eDebug, pHitResults, true);

		if (pHitResults.Num() <= 0) return;

		for (int i = 0; i < pHitResults.Num(); i++)
		{
			AActor* pHitActor = pHitResults[i].GetActor();
			if (pHitActor == nullptr) continue;
			if (pHitActor->ActorHasTag(FName(TEXT("Player"))) == true) continue;

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

			if (pHitActor->ActorHasTag(FName(TEXT("Enemy"))) == true)
			{
				FDamageEvent* DamageEvent = new FDamageEvent_Hit(1.0f, GetRootChar()->GetActorLocation(), pHitResults[i].ImpactPoint);
				float fResultDamage = pHitActor->TakeDamage(1.0f, *DamageEvent, GetRootChar()->GetController(), GetRootChar());
				if (fResultDamage == 0.0f) continue;

				FRotator pLookRotation = UKismetMathLibrary::FindLookAtRotation(GetRootChar()->GetActorLocation(), pHitResults[i].ImpactPoint);
				pLookRotation.Roll = 0.0f;
				pLookRotation.Pitch = 0.0f;


				if (fResultDamage != 999.0f)
				{
					GetRootChar()->GetParticleMng()->SpawnParticleAtLocation(TEXT("Hit_Back"), GetRootChar()->GetWorld(), pHitActor->GetActorLocation(), pLookRotation, FVector::OneVector*1.5f);
					GetRootChar()->GetSoundMng()->Play(TEXT("AttackHit"));

				}
				else
				{
					GetRootChar()->GetSoundMng()->Play(TEXT("BarrierHit"));
				}

				GetRootChar()->GetParticleMng()->SpawnParticleAtLocation(TEXT("HitSlash"), GetRootChar()->GetWorld(), pHitActor->GetActorLocation(), FRotator::ZeroRotator, FVector::OneVector*1.5f);
				
				
				//GetRootChar()->GetCamShake()->PlayCameraShake(TEXT("AttackHit"), 1.0f);
				//GetRootChar()->GetAnimationMng()->Active_Stiffen(0.3f, 0.001f);

			
				bHited = true;
				//ULOG(TEXT("Attack Hit"));	
			}
			else if (pHitActor->ActorHasTag(FName(TEXT("EnemyBullet"))) == true)
			{
				FVector vMousePos = GetRootChar()->GetMouseMng()->GetMouse_Location();
				vMousePos.Z = pHitActor->GetActorLocation().Z;
				FDamageEvent* DamageEvent = new FDamageEvent_Hit(105.0f, GetRootChar()->GetActorLocation(), vMousePos);
				float fResultDamage = pHitActor->TakeDamage(105.0f, *DamageEvent, GetRootChar()->GetController(), GetRootChar());
				//if (fResultDamage == 0.0f) continue;

				FRotator pLookRotation = UKismetMathLibrary::FindLookAtRotation(GetRootChar()->GetActorLocation(), pHitResults[i].ImpactPoint);
				pLookRotation.Roll = 0.0f;
				pLookRotation.Pitch = 0.0f;

				GetRootChar()->GetParticleMng()->SpawnParticleAtLocation(TEXT("Hit"), GetRootChar()->GetWorld(), pHitResults[i].ImpactPoint, FRotator::ZeroRotator, FVector::OneVector*2.0f);
				GetRootChar()->GetParticleMng()->SpawnParticleAtLocation(TEXT("Hit_Back"), GetRootChar()->GetWorld(), pHitResults[i].ImpactPoint, pLookRotation, FVector::OneVector*1.0f);
				//GetRootChar()->GetCamShake()->PlayCameraShake(TEXT("AttackHit"), 1.0f);

			//	GetRootChar()->GetAnimationMng()->Active_Stiffen(0.3f, 0.001f);

				//GetRootChar()->GetSoundMng()->Play(TEXT("AttackHit"));
				GetRootChar()->GetSoundMng()->Play(TEXT("Parring"));

				bHited = true;

			}
		}


	}
	if (bHited == true)
	{
		GetRootChar()->GetCamShake()->PlayCameraShake(TEXT("AttackHit"), 1.0f);
		GetRootChar()->GetAnimationMng()->Active_Stiffen(0.3f, 0.001f);
		GetRootChar()->GetPostProcessEffect()->Active_Effect(TEXT("HitSlash"));
	}
}

bool UState_GBox_Attack::CheckParring(FVector vAttackLoc)
{
	return false;
	if (m_bAttack == false) return false;
	FVector pHitDirection = vAttackLoc - GetRootCharacter()->GetActorLocation();
	pHitDirection.Normalize();

	FRotator pRota_Capsule = GetRootCharacter()->GetCapsuleComponent()->GetComponentRotation();
	FRotator pRota_Hit = UKismetMathLibrary::NormalizedDeltaRotator(pRota_Capsule, UKismetMathLibrary::MakeRotFromX(pHitDirection));

	float fDirection = pRota_Hit.Yaw;
	FString sDirectionStr = "Front";

	if (fDirection > -45.0f && fDirection <= 45.0f)
	{
		FVector vParticleLoc = GetRootChar()->GetActorLocation() + GetRootChar()->GetActorForwardVector() * 100.0f;
		FRotator pLookRotation = UKismetMathLibrary::FindLookAtRotation(GetRootChar()->GetActorLocation(), vParticleLoc);

		GetRootChar()->GetParticleMng()->SpawnParticleAtLocation(TEXT("Hit"), GetRootChar()->GetWorld()
			, vParticleLoc
			, FRotator::ZeroRotator, FVector::OneVector*3.0f);
		GetRootChar()->GetParticleMng()->SpawnParticleAtLocation(TEXT("Hit_Back"), GetRootChar()->GetWorld(), vParticleLoc, pLookRotation, FVector::OneVector*1.5f);
		GetRootChar()->GetCamShake()->PlayCameraShake(TEXT("AttackHit"), 1.0f);
		GetRootChar()->GetAnimationMng()->Active_Stiffen(0.3f, 0.001f);

		return true;
	}
	return false;
}