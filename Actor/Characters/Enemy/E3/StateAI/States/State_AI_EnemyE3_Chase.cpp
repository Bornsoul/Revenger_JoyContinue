// Fill out your copyright notice in the Description page of Project Settings.

#include "State_AI_EnemyE3_Chase.h"
#include "../StateRoot_AI_EnemyE3.h"
#include "../../AIC_EnemyE3.h"
#include "Actor/Characters/Enemy/E3/EnemyE3.h"

void UState_AI_EnemyE3_Chase::Init(class UStateMng_AI* pMng)
{
	Super::Init(pMng);

}

void UState_AI_EnemyE3_Chase::Enter()
{
	Super::Enter();

	/*if (m_pChaseTarget == nullptr)
	{
		ULOG(TEXT("[Chase] Target is nullptr"));

		return;
	}*/


	m_fTargetTime_Curr = 0.0f;
	m_fDist_Combat = GetRootAI()->m_fAISightRadius;
	m_fDist_Lost = GetRootAI()->m_fAILoseSightRadius;
	//m_fDist_Lost = GetRootAI()->m_fAILoseSightRadius;
	//m_vTargetPos = m_pChaseTarget->GetActorLocation();
}

void UState_AI_EnemyE3_Chase::Exit()
{
	Super::Exit();

	m_pChaseTarget = nullptr;
}

void UState_AI_EnemyE3_Chase::Update(float fDeltaTime)
{
	Super::Update(fDeltaTime);

	/*m_fTargetTime_Curr += fDeltaTime;
	if (m_fTargetTime_Curr >= m_fTargetTime_End)
	{
		m_fTargetTime_Curr = 0.0f;

		m_vTargetPos = m_pChaseTarget->GetActorLocation();
	}*/

	if (m_pChaseTarget == nullptr)
	{
		AActor* pTarget = GetRootAI()->DetectInPerception();
		if (pTarget != nullptr)
			m_pChaseTarget = pTarget;

		return;
	}

	m_vTargetPos = m_pChaseTarget->GetActorLocation();
	m_vEnemyPos = GetRootAI()->GetRootChar()->GetActorLocation();
	EPathFollowingRequestResult::Type pResult = GetRootAI()->MoveToLocation(m_vTargetPos);

	if (pResult == EPathFollowingRequestResult::Failed)
	{
		//ULOG(TEXT("Player is Lost"));
	}

	float fDistance = FVector::Distance(m_vEnemyPos, m_vTargetPos);
	if (fDistance <= m_fDist_Combat)
	{
		ChangeState(static_cast<int32>(E_StateAI_EnemyE3::E_Combat));
		return;
	}

	if (fDistance > m_fDist_Lost)
	{
		ChangeState(static_cast<int32>(E_StateAI_EnemyE3::E_Lost));
		return;
	}

}

void UState_AI_EnemyE3_Chase::StateMessage(FString StateMessage)
{
	Super::StateMessage(StateMessage);
}

void UState_AI_EnemyE3_Chase::SetChaseTarget(AActor* pTarget)
{
	m_pChaseTarget = pTarget;
}
