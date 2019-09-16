// Fill out your copyright notice in the Description page of Project Settings.

#include "StateAI_EnemyE5_Normal.h"
#include "Actor/Characters/StateRootAI/StateMng_AI.h"

void UStateAI_EnemyE5_Normal::Init(class UStateMng_AI* pMng)
{
	Super::Init(pMng);

}

void UStateAI_EnemyE5_Normal::Enter()
{
	Super::Enter();

	//ULOG(TEXT("E5 Normal"));
}

void UStateAI_EnemyE5_Normal::Exit()
{
	Super::Exit();

}

void UStateAI_EnemyE5_Normal::Update(float fDeltaTime)
{
	Super::Update(fDeltaTime);

	AActor* pTarget = GetRootAI()->DetectInPerception();
	if (pTarget != nullptr)
	{

		UStateAI_EnemyE5_Chase* pState = Cast<UStateAI_EnemyE5_Chase>(m_pStateMng->GetStateClassRef(static_cast<int32>(E_StateAI_EnemyE5::E_Chase)));
		if (pState != nullptr)
		{
			pState->SetChaseTarget(pTarget);
			ChangeState(static_cast<int32>(E_StateAI_EnemyE5::E_Chase));
		}
	}
}

void UStateAI_EnemyE5_Normal::StateMessage(FString StateMessage)
{
	Super::StateMessage(StateMessage);
}


