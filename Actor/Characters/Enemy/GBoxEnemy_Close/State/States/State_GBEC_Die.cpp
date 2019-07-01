// Fill out your copyright notice in the Description page of Project Settings.

#include "State_GBEC_Die.h"
#include "Kismet/KismetMathLibrary.h"
#include "Libraries/Components/MaterialEffect/Cpt_MaterialEffect.h"
#include "Libraries/Components/AnimationMng/Cpt_AnimationMng.h"

void UState_GBEC_Die::Init(class UStateMng_GC* pMng)
{
	Super::Init(pMng);

}

void UState_GBEC_Die::Enter()
{
	Super::Enter();

	GetRootChar()->GetAI()->SetActiveAI(false);
//	GetRootChar()->GetAnimationMng()->PlayAnimationSequnceBase(TEXT("Dead"), TEXT("DefaultSlot"), 0.0f, 0.2f, 1.0f);
	//GetRootChar()->GetAnimationMng()->PlayAnimationSequnceBase("Die", TEXT("DefaultSlot"), 0.2f, 0.2f, 1.0f);

	GetRootChar()->GetAnimationMng()->PlayAnimationMontage(TEXT("Die"), 1.0f, TEXT("Default"));
	GetRootChar()->GetMaterialEffect()->ActiveEffect(E_MaterialEffect::E_Hit2);
	GetRootChar()->GetAnimationMng()->Active_Stiffen(0.3f, 0.001f);
	m_bMotionEnd = false;

	m_bRagdoll = false;
	m_fStiffenTime = 0.0f;

}

void UState_GBEC_Die::Exit()
{
	Super::Exit();
	//GetRootChar()->GetAnimationMng()->StopAnimation_SequnceBaseSlot(TEXT("DefaultSlot"), 0.2f);
}

void UState_GBEC_Die::Update(float fDeltaTime)
{
	Super::Update(fDeltaTime);

	if (m_bRagdoll == false)
	{
		m_fStiffenTime += fDeltaTime;
		if (m_fStiffenTime >= 0.3f)
		{
			m_bRagdoll = true;
			//FVector pHitDirection = m_vHitDirection - GetRootCharacter()->GetActorLocation();
		//	pHitDirection.Normalize();
		//	GetRootChar()->SetRagdollPhysics(m_vHitDirection, 800000.0f);
			m_fStiffenTime = 0.0f;
			//GetRootChar()->GetAnimationMng()->PlayAnimationSequnceBase("Die", TEXT("DefaultSlot"), 0.1f, 0.2f, 1.0f);
		}
	}
	else
	{
		m_fStiffenTime += fDeltaTime;
		if (m_fStiffenTime > 1.5f)
		{
			//GetRootChar()->Destroy();
		}
	}



}

void UState_GBEC_Die::StateMessage(FString StateMessage)
{
	Super::StateMessage(StateMessage);

	if (StateMessage == "MotionEnd")
	{
		m_bMotionEnd = true;
	}
}

FString UState_GBEC_Die::GetHitDirection()
{
	FVector pHitDirection = m_vHitDirection - GetRootCharacter()->GetActorLocation();
	pHitDirection.Normalize();

	FRotator pRota_Capsule = GetRootCharacter()->GetCapsuleComponent()->GetComponentRotation();
	FRotator pRota_Hit = UKismetMathLibrary::NormalizedDeltaRotator(pRota_Capsule, UKismetMathLibrary::MakeRotFromX(pHitDirection));

	float fDirection = pRota_Hit.Yaw;
	FString sDirectionStr = "Front";

	if (fDirection > -45.0f && fDirection <= 45.0f)
	{
		sDirectionStr = "Front";
	}
	else if (fDirection > -135.0f && fDirection <= -45.0f)
	{
		sDirectionStr = "Right";
	}
	else if (fDirection > 45.0f && fDirection <= 135.0f)
	{
		sDirectionStr = "Left";
	}
	else if ((fDirection > 135.0f && fDirection <= 180.0f) || (fDirection <= -135.0f && fDirection >= -180.0f))
	{
		sDirectionStr = "Back";
	}

	return sDirectionStr;
}

