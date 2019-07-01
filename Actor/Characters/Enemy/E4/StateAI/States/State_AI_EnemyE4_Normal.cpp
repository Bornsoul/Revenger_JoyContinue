// Fill out your copyright notice in the Description page of Project Settings.

#include "State_AI_EnemyE4_Normal.h"
#include "Actor/Characters/StateRootAI/StateMng_AI.h"

void UState_AI_EnemyE4_Normal::Init(class UStateMng_AI* pMng)
{
	Super::Init(pMng);

}

void UState_AI_EnemyE4_Normal::Enter()
{
	Super::Enter();
}

void UState_AI_EnemyE4_Normal::Exit()
{
	Super::Exit();

}

void UState_AI_EnemyE4_Normal::Update(float fDeltaTime)
{
	Super::Update(fDeltaTime);

	AActor* pTarget = GetRootAI()->DetectInPerception();
	if (pTarget != nullptr)
	{
		
		UStateAI_EnemyE4_Chase* pState = Cast<UStateAI_EnemyE4_Chase>(m_pStateMng->GetStateClassRef(static_cast<int32>(E_StateAI_EnemyE4::E_Chase)));
		if (pState != nullptr)
		{
			pState->SetChaseTarget(pTarget);
			ChangeState(static_cast<int32>(E_StateAI_EnemyE4::E_Chase));
		}
	}
}

void UState_AI_EnemyE4_Normal::StateMessage(FString StateMessage)
{
	Super::StateMessage(StateMessage);
}

