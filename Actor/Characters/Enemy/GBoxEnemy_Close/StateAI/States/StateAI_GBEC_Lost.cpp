// Fill out your copyright notice in the Description page of Project Settings.

#include "StateAI_GBEC_Lost.h"
#include "StateAI_GBEC_Chase.h"

#include "../StateRootAI_GBEClose.h"
#include "../../AIC_GBoxEnemy_Close.h"

#include "Actor/Characters/StateRootAI/StateMng_AI.h"
#include "Actor/Characters/Enemy/GBoxEnemy_Close/GBoxEnemy_Close.h"

void UStateAI_GBEC_Lost::Init(class UStateMng_AI* pMng)
{
	Super::Init(pMng);

}

void UStateAI_GBEC_Lost::Enter()
{
	Super::Enter();

	GetRootAI()->GetRootChar()->GetCharacterMovement()->MaxWalkSpeed = 800.0f;

	m_vStartPos = GetRootAI()->GetRootChar()->GetStartLoc();
	EPathFollowingRequestResult::Type pResult = GetRootAI()->MoveToLocation(m_vStartPos);	
		
	m_fReSearchTime_Curr = 0.0f;
	m_bReSearch = false;
}

void UStateAI_GBEC_Lost::Exit()
{
	Super::Exit();

	GetRootAI()->GetRootChar()->GetCharacterMovement()->MaxWalkSpeed = 300.0f;
}

void UStateAI_GBEC_Lost::Update(float fDeltaTime)
{
	Super::Update(fDeltaTime);

	FVector vEnemyPos = GetRootAI()->GetRootChar()->GetActorLocation();
	float fDistance = FVector::Distance(vEnemyPos, m_vStartPos);
	if (fDistance <= 100.0f)
	{
		ChangeState(static_cast<int32>(E_StateAI_GBEClose::E_Normal));
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
			UStateAI_GBEC_Chase* pState = Cast<UStateAI_GBEC_Chase>(m_pStateMng->GetStateClassRef(static_cast<int32>(E_StateAI_GBEClose::E_Chase)));
			if (pState != nullptr)
			{
				pState->SetChaseTarget(pTarget);
				ChangeState(static_cast<int32>(E_StateAI_GBEClose::E_Chase));
			}
		}
	}
}

void UStateAI_GBEC_Lost::StateMessage(FString StateMessage)
{
	Super::StateMessage(StateMessage);
}

