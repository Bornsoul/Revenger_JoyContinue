// Fill out your copyright notice in the Description page of Project Settings.

#include "State_GBEL_Hit.h"
#include "Kismet/KismetMathLibrary.h"
#include "Libraries/Components/MaterialEffect/Cpt_MaterialEffect.h"
#include "Libraries/Components/AnimationMng/Cpt_AnimationMng.h"

void UState_GBEL_Hit::Init(class UStateMng_GC* pMng)
{
	Super::Init(pMng);

}

void UState_GBEL_Hit::Enter()
{
	Super::Enter();
	GetRootChar()->GetAnimationMng()->PlayAnimationSequnceBase("Hit", TEXT("DefaultSlot"), 0.0f, 0.2f, 1.0f);
	m_bMotionEnd = false;
	
	GetRootChar()->GetMaterialEffect()->ActiveEffect(E_MaterialEffect::E_Hit2);
	GetRootChar()->GetAnimationMng()->Active_Stiffen(0.3f, 0.001f);

	GetRootChar()->GetAI()->StopMovement();
	GetRootChar()->GetAI()->SetActiveAI(false);
}

void UState_GBEL_Hit::Exit()
{
	Super::Exit();
	GetRootChar()->GetAI()->SetActiveAI(true);
	GetRootChar()->GetAnimationMng()->StopAnimation_SequnceBaseSlot(TEXT("DefaultSlot"), 0.2f);
}

void UState_GBEL_Hit::Update(float fDeltaTime)
{
	Super::Update(fDeltaTime);

	if (m_bMotionEnd == true)
	{
		ChangeState(static_cast<int32>(E_State_GBELong::E_Idle));
		return;
	}

}

void UState_GBEL_Hit::StateMessage(FString StateMessage)
{
	Super::StateMessage(StateMessage);

	if (StateMessage == "MotionEnd")
	{
		m_bMotionEnd = true;
	}
}

FString UState_GBEL_Hit::GetHitDirection()
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

