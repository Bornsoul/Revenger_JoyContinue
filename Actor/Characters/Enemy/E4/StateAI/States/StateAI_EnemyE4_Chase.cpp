// Fill out your copyright notice in the Description page of Project Settings.

#include "StateAI_EnemyE4_Chase.h"
#include "../StateRoot_AI_EnemyE4.h"
#include "../../AIC_EnemyE4.h"
#include "Actor/Characters/Enemy/E4/EnemyE4.h"

void UStateAI_EnemyE4_Chase::Init(class UStateMng_AI* pMng)
{
	Super::Init(pMng);

}

void UStateAI_EnemyE4_Chase::Enter()
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

void UStateAI_EnemyE4_Chase::Exit()
{
	Super::Exit();

	m_pChaseTarget = nullptr;
}

void UStateAI_EnemyE4_Chase::Update(float fDeltaTime)
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
		ULOG(TEXT("Player is Lost"));
	}

	float fDistance = FVector::Distance(m_vEnemyPos, m_vTargetPos);
	if (fDistance <= m_fDist_Combat)
	{
		ChangeState(static_cast<int32>(E_StateAI_EnemyE4::E_Combat));
		return;
	}

	if (fDistance > m_fDist_Lost)
	{
		ChangeState(static_cast<int32>(E_StateAI_EnemyE4::E_Lost));
		return;
	}

}

void UStateAI_EnemyE4_Chase::StateMessage(FString StateMessage)
{
	Super::StateMessage(StateMessage);
}

void UStateAI_EnemyE4_Chase::SetChaseTarget(AActor* pTarget)
{
	m_pChaseTarget = pTarget;
}

