// Fill out your copyright notice in the Description page of Project Settings.

#include "StateAI_EnemyE3_Lost.h"
#include "State_AI_EnemyE3_Chase.h"

#include "../StateRoot_AI_EnemyE3.h"
#include "../../AIC_EnemyE3.h"
#include "Actor/Characters/Enemy/E3/EnemyE3.h"

#include "Actor/Characters/StateRootAI/StateMng_AI.h"



void UStateAI_EnemyE3_Lost::Init(class UStateMng_AI* pMng)
{
	Super::Init(pMng);

}

void UStateAI_EnemyE3_Lost::Enter()
{
	Super::Enter();


	m_vStartPos = GetRootAI()->GetRootChar()->GetStartLoc();
	EPathFollowingRequestResult::Type pResult = GetRootAI()->MoveToLocation(m_vStartPos);

	m_fReSearchTime_Curr = 0.0f;
	m_bReSearch = false;
}

void UStateAI_EnemyE3_Lost::Exit()
{
	Super::Exit();

}

void UStateAI_EnemyE3_Lost::Update(float fDeltaTime)
{
	Super::Update(fDeltaTime);

	FVector vEnemyPos = GetRootAI()->GetRootChar()->GetActorLocation();
	float fDistance = FVector::Distance(vEnemyPos, m_vStartPos);
	if (fDistance <= 300.0f)
	{
		ChangeState(static_cast<int32>(E_StateAI_EnemyE3::E_Normal));
		return;
	}

	if (m_bReSearch == false)
	{
		m_fReSearchTime_Curr += fDeltaTime;
		if (m_fReSearchTime_Curr >= m_fReSearchTime_End)
		{
			m_bReSearch = true;
		}
	}
	else
	{
		AActor* pTarget = GetRootAI()->DetectInPerception();
		if (pTarget != nullptr)
		{
			UState_AI_EnemyE3_Chase* pState = Cast<UState_AI_EnemyE3_Chase>(m_pStateMng->GetStateClassRef(static_cast<int32>(E_StateAI_EnemyE3::E_Chase)));
			if (pState != nullptr)
			{
				pState->SetChaseTarget(pTarget);
				ChangeState(static_cast<int32>(E_StateAI_EnemyE3::E_Chase));
			}
		}
	}
}

void UStateAI_EnemyE3_Lost::StateMessage(FString StateMessage)
{
	Super::StateMessage(StateMessage);
}


