// Fill out your copyright notice in the Description page of Project Settings.

#include "State_GBEC_Hit.h"
#include "Kismet/KismetMathLibrary.h"
#include "Libraries/Components/MaterialEffect/Cpt_MaterialEffect.h"
#include "Libraries/Components/AnimationMng/Cpt_AnimationMng.h"

void UState_GBEC_Hit::Init(class UStateMng_GC* pMng)
{
	Super::Init(pMng);

}

void UState_GBEC_Hit::Enter()
{
	Super::Enter();

	//GetRootCharacter()->GetAnimationMng()->PlayAnimationSequnceBase("Hit_" + GetHitDirection(), TEXT("DefaultSlot"), 0.0f, 0.2f, 1.0f);
	GetRootChar()->GetAnimationMng()->PlayAnimationSequnceBase("Hit", TEXT("DefaultSlot"), 0.0f, 0.2f, 1.0f);
	m_bMotionEnd = false;

	GetRootChar()->GetMaterialEffect()->ActiveEffect(E_MaterialEffect::E_Hit2);
	GetRootChar()->GetAnimationMng()->Active_Stiffen(0.3f, 0.001f);

	GetRootChar()->GetAI()->SetActiveAI(false);
	GetRootChar()->GetAI()->StopMovement();
	m_fKnockBackTIme = 0.0f;
	m_bKnockBacked = false;

	
}

void UState_GBEC_Hit::Exit()
{
	Super::Exit();
	GetRootChar()->GetAI()->SetActiveAI(true);
	GetRootChar()->GetAnimationMng()->StopAnimation_SequnceBaseSlot(TEXT("DefaultSlot"), 0.2f);

}

void UState_GBEC_Hit::Update(float fDeltaTime)
{
	Super::Update(fDeltaTime);
	
	/*if (m_bKnockBacked == false)
	{
		m_fKnockBackTIme += fDeltaTime;
		if (m_fKnockBackTIme >= 0.3f)
		{
			ULOG(TEXT("aaa"));
			FVector vPushDirection = GetRootChar()->GetActorLocation() - m_vHitDirection;
			vPushDirection.Normalize();
			vPushDirection.Z = 0.0f;
			//GetRootChar()->GetCapsuleComponent()->AddImpulse(vPushDirection *fDeltaTime*500000.0f);
			GetRootChar()->GetCharacterMovement()->AddImpulse(vPushDirection *fDeltaTime*500000.0f, true);
			m_bKnockBacked = true;
		}
	}*/

	if (m_bMotionEnd == true)
	{
		ChangeState(static_cast<int32>(E_State_GBEClose::E_Idle));
		return;
	}

}

void UState_GBEC_Hit::StateMessage(FString StateMessage)
{
	Super::StateMessage(StateMessage);

	if (StateMessage == "MotionEnd")
	{
		m_bMotionEnd = true;
	}
}

FString UState_GBEC_Hit::GetHitDirection()
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
