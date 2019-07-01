// Fill out your copyright notice in the Description page of Project Settings.

#include "StateAI_GBEC_Normal.h"
#include "StateAI_GBEC_Chase.h"
#include "Actor/Characters/StateRootAI/StateMng_AI.h"

void UStateAI_GBEC_Normal::Init(class UStateMng_AI* pMng)
{
	Super::Init(pMng);

}

void UStateAI_GBEC_Normal::Enter()
{
	Super::Enter();
}

void UStateAI_GBEC_Normal::Exit()
{
	Super::Exit();

}

void UStateAI_GBEC_Normal::Update(float fDeltaTime)
{
	Super::Update(fDeltaTime);

	AActor* pTarget = GetRootAI()->DetectInPerception();
	if (pTarget != nullptr)
	{
		UStateAI_GBEC_Chase* pState = Cast<UStateAI_GBEC_Chase>(
			m_pStateMng->GetStateClassRef(static_cast<int32>(E_StateAI_GBEClose::E_Chase)));

		if (pState != nullptr)
		{
			pState->SetChaseTarget(pTarget);
			ChangeState(static_cast<int32>(E_StateAI_GBEClose::E_Chase));
		}
	}
}

void UStateAI_GBEC_Normal::StateMessage(FString StateMessage)
{
	Super::StateMessage(StateMessage);
}
