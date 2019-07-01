// Fill out your copyright notice in the Description page of Project Settings.

#include "StateAI_GBEC_Combat_Attack.h"
#include "Kismet/KismetMathLibrary.h"

void UStateAI_GBEC_Combat_Attack::Init(class UStateMng_AI* pMng)
{
	Super::Init(pMng);

}

void UStateAI_GBEC_Combat_Attack::Enter()
{
	Super::Enter();

	m_bMovement = true;
}

void UStateAI_GBEC_Combat_Attack::Exit()
{
	Super::Exit();

}

void UStateAI_GBEC_Combat_Attack::Update(float fDeltaTime)
{
	Super::Update(fDeltaTime);

	AActor* pTarget = GetRootAI()->DetectInPerception();
	if ( pTarget == nullptr ) 
	{
		ULOG(TEXT("Combat Attack DetectIn is nullptr"));
		return;
	}

	FVector vEnemyPos = GetRootAI()->GetRootChar()->GetActorLocation();
	FVector vTargetPos = pTarget->GetActorLocation();

	float fDistance = FVector::Distance(vEnemyPos, vTargetPos);
	if (fDistance <= m_fDist_Attack)
	{
		m_bMovement = false;
		float fRand = UKismetMathLibrary::RandomFloatInRange(0.0f, 100.0f);

		if (fRand < 30.0f)
		{
			if (GetRootAI()->GetRootChar()->Controll_Attack(pTarget))
			{
				ChangeState(static_cast<int32>(E_StateAI_GBEClose::E_Combat));
				return;
			}
		}
		else if(fRand < 60.0f)
		{
			if (GetRootAI()->GetRootChar()->Controll_Attack2(pTarget))
			{
				ChangeState(static_cast<int32>(E_StateAI_GBEClose::E_Combat));
				return;
			}
		}
		else 
		{
			if (GetRootAI()->GetRootChar()->Controll_Spin(pTarget))
			{
				ChangeState(static_cast<int32>(E_StateAI_GBEClose::E_Combat));
				return;
			}
		}

	}

	if (m_bMovement == true )
	{
		EPathFollowingRequestResult::Type pResult = GetRootAI()->MoveToLocation(vTargetPos);
	}
}

void UStateAI_GBEC_Combat_Attack::StateMessage(FString StateMessage)
{
	Super::StateMessage(StateMessage);
}

