// Fill out your copyright notice in the Description page of Project Settings.

#include "State_TutoEnemy_Hit.h"

void UState_TutoEnemy_Hit::Init(class UStateMng_GC* pMng)
{
	Super::Init(pMng);

}

void UState_TutoEnemy_Hit::Enter()
{
	Super::Enter();

	GetRootChar()->GetAnimationMng()->PlayAnimationSequnceBase(TEXT("Hit"), TEXT("DefaultSlot"), 0.2f, 0.2f, 1.0f);
	GetRootChar()->GetMaterialEffect()->ActiveEffect(E_MaterialEffect::E_Hit2);
	GetRootChar()->GetAnimationMng()->Active_Stiffen(0.3f, 0.001f);

	FRotator vRota = UKismetMathLibrary::FindLookAtRotation(GetRootChar()->GetActorLocation(), m_vHitDirection);
	GetRootChar()->SetActorRotation(vRota);

	m_fKnockBackTIme = 0.0f;
	m_bMotionEnd = false;
	m_bKnockBacked = false;
}

void UState_TutoEnemy_Hit::Exit()
{
	Super::Exit();

	GetRootChar()->GetAnimationMng()->StopAnimation_SequnceBaseSlot(TEXT("DefaultSlot"), 0.2f);

}

void UState_TutoEnemy_Hit::Update(float fDeltaTime)
{
	Super::Update(fDeltaTime);

	if (m_bKnockBacked == false)
	{
		m_fKnockBackTIme += fDeltaTime;
		if (m_fKnockBackTIme >= 0.3f)
		{
			FVector vPushDirection = GetRootChar()->GetActorLocation() - m_vHitDirection;
			vPushDirection.Normalize();
			vPushDirection.Z = 0.0f;
		
			GetRootChar()->GetCharacterMovement()->AddImpulse(vPushDirection *fDeltaTime*500000.0f, true);
			m_bKnockBacked = true;
		}
	}

}

void UState_TutoEnemy_Hit::StateMessage(FString StateMessage)
{
	Super::StateMessage(StateMessage);

	if (StateMessage == "MotionEnd")
	{
		ChangeState(static_cast<int32>(E_State_TutoEnemy::E_Idle));
		return;
	}
}

FString UState_TutoEnemy_Hit::GetHitDirection()
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


