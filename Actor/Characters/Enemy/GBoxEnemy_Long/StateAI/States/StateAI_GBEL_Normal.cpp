// Fill out your copyright notice in the Description page of Project Settings.

#include "StateAI_GBEL_Normal.h"
#include "StateAI_GBEL_Chase.h"
#include "Actor/Characters/StateRootAI/StateMng_AI.h"

void UStateAI_GBEL_Normal::Init(class UStateMng_AI* pMng)
{
	Super::Init(pMng);

}

void UStateAI_GBEL_Normal::Enter()
{
	Super::Enter();
}

void UStateAI_GBEL_Normal::Exit()
{
	Super::Exit();

}

void UStateAI_GBEL_Normal::Update(float fDeltaTime)
{
	Super::Update(fDeltaTime);

	AActor* pTarget = GetRootAI()->DetectInPerception();
	if (pTarget != nullptr)
	{
		UStateAI_GBEL_Chase* pState = Cast<UStateAI_GBEL_Chase>(m_pStateMng->GetStateClassRef(static_cast<int32>(E_StateAI_GBELong::E_Chase)));
		if (pState != nullptr)
		{
			pState->SetChaseTarget(pTarget);
			ChangeState(static_cast<int32>(E_StateAI_GBELong::E_Chase));
		}
	}
}

void UStateAI_GBEL_Normal::StateMessage(FString StateMessage)
{
	Super::StateMessage(StateMessage);
}

