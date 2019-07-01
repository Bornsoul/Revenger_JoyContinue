// Fill out your copyright notice in the Description page of Project Settings.

#include "StateAI_GBEL_Chase.h"
#include "../StateRootAI_GBELong.h"
#include "../../AIC_GBoxEnemy_Long.h"
#include "Actor/Characters/Enemy/GBoxEnemy_Long/GBoxEnemy_Long.h"

void UStateAI_GBEL_Chase::Init(class UStateMng_AI* pMng)
{
	Super::Init(pMng);

}

void UStateAI_GBEL_Chase::Enter()
{
	Super::Enter();


	/*if (m_pChaseTarget == nullptr)
	{
		ULOG(TEXT("[Chase] Target is nullptr"));
		ChangeState(static_cast<int32>(E_StateAI_GBELong::E_Normal));
		return;
	}*/

	m_fTargetTime_Curr = 0.0f;
	m_fDist_Combat = GetRootAI()->m_fAISightRadius;
	m_fDist_Lost = GetRootAI()->m_fAILoseSightRadius;
	//m_vTargetPos = m_pChaseTarget->GetActorLocation();

}

void UStateAI_GBEL_Chase::Exit()
{
	Super::Exit();

	m_pChaseTarget = nullptr;
}

void UStateAI_GBEL_Chase::Update(float fDeltaTime)
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

	float fDistance = FVector::Distance(m_vEnemyPos, m_vTargetPos);

	if (pResult == EPathFollowingRequestResult::Failed)
	{
		ULOG(TEXT("Chase Player is Lost"));
	}

	if (fDistance <= m_fDist_Combat)
	{
		ChangeState(static_cast<int32>(E_StateAI_GBELong::E_Combat));
		return;
	}
	

	if (fDistance > m_fDist_Lost)
	{
		ChangeState(static_cast<int32>(E_StateAI_GBELong::E_Lost));
		return;
	}

}

void UStateAI_GBEL_Chase::StateMessage(FString StateMessage)
{
	Super::StateMessage(StateMessage);
}

void UStateAI_GBEL_Chase::SetChaseTarget(AActor* pTarget)
{
	m_pChaseTarget = pTarget;
}

