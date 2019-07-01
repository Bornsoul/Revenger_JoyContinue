// Fill out your copyright notice in the Description page of Project Settings.

#include "StateAI_EnemyE3_Normal.h"
#include "Actor/Characters/StateRootAI/StateMng_AI.h"

void UStateAI_EnemyE3_Normal::Init(class UStateMng_AI* pMng)
{
	Super::Init(pMng);

}

void UStateAI_EnemyE3_Normal::Enter()
{
	Super::Enter();
}

void UStateAI_EnemyE3_Normal::Exit()
{
	Super::Exit();

}

void UStateAI_EnemyE3_Normal::Update(float fDeltaTime)
{
	Super::Update(fDeltaTime);

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

void UStateAI_EnemyE3_Normal::StateMessage(FString StateMessage)
{
	Super::StateMessage(StateMessage);
}
