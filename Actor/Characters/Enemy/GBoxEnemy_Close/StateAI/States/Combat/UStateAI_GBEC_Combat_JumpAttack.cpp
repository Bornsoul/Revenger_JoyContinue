// Fill out your copyright notice in the Description page of Project Settings.

#include "UStateAI_GBEC_Combat_JumpAttack.h"
#include "Kismet/KismetMathLibrary.h"

void UUStateAI_GBEC_Combat_JumpAttack::Init(class UStateMng_AI* pMng)
{
	Super::Init(pMng);

}

void UUStateAI_GBEC_Combat_JumpAttack::Enter()
{
	Super::Enter();

	m_bMovement = true;
}

void UUStateAI_GBEC_Combat_JumpAttack::Exit()
{
	Super::Exit();

}

void UUStateAI_GBEC_Combat_JumpAttack::Update(float fDeltaTime)
{
	Super::Update(fDeltaTime);

	AActor* pTarget = GetRootAI()->DetectInPerception();
	if (pTarget == nullptr)
	{
		ChangeState(static_cast<int32>(E_StateAI_GBEClose::E_Chase));
		return;
	}

	FVector vEnemyPos = GetRootAI()->GetRootChar()->GetActorLocation();
	FVector vTargetPos = pTarget->GetActorLocation();

	
	m_bMovement = false;


	float fDistance = FVector::Distance(vEnemyPos, vTargetPos);
	if (fDistance <= 1000.0f)
	{
		if (GetRootAI()->GetRootChar()->Controll_Dash(pTarget))
		{
			ChangeState(static_cast<int32>(E_StateAI_GBEClose::E_Combat));
			return;
		}
	}
	else
	{
		if (GetRootAI()->GetRootChar()->Controll_JumpAttack(pTarget))
		{
			ChangeState(static_cast<int32>(E_StateAI_GBEClose::E_Combat));
			return;
		}
	}


	

	if (m_bMovement == true)
	{
		EPathFollowingRequestResult::Type pResult = GetRootAI()->MoveToLocation(vTargetPos);
	}
}

void UUStateAI_GBEC_Combat_JumpAttack::StateMessage(FString StateMessage)
{
	Super::StateMessage(StateMessage);
}


