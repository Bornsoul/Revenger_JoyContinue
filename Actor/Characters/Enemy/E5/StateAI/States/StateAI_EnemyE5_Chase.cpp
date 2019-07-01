// Fill out your copyright notice in the Description page of Project Settings.

#include "StateAI_EnemyE5_Chase.h"
#include "Actor/Characters/StateRootAI/StateMng_AI.h"

void UStateAI_EnemyE5_Chase::Init(class UStateMng_AI* pMng)
{
	Super::Init(pMng);

}

void UStateAI_EnemyE5_Chase::Enter()
{
	Super::Enter();

	m_fTargetTime_Curr = 0.0f;
	m_fDist_Combat = GetRootAI()->m_fAISightRadius;
	m_fDist_Lost = GetRootAI()->m_fAILoseSightRadius;

	ULOG(TEXT("E5 Chase"));
}

void UStateAI_EnemyE5_Chase::Exit()
{
	Super::Exit();

	m_pChaseTarget = nullptr;
}

void UStateAI_EnemyE5_Chase::Update(float fDeltaTime)
{
	Super::Update(fDeltaTime);

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
		ChangeState(static_cast<int32>(E_StateAI_EnemyE5::E_Combat));
		return;
	}

	if (fDistance > m_fDist_Lost)
	{
		ChangeState(static_cast<int32>(E_StateAI_EnemyE5::E_Lost));
		return;
	}
}

void UStateAI_EnemyE5_Chase::StateMessage(FString StateMessage)
{
	Super::StateMessage(StateMessage);
}


void UStateAI_EnemyE5_Chase::SetChaseTarget(AActor* pTarget)
{
	m_pChaseTarget = pTarget;
}

