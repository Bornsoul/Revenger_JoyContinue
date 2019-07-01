// Fill out your copyright notice in the Description page of Project Settings.

#include "StateRoot_AI.h"
#include "StateMng_AI.h"

UStateRoot_AI::UStateRoot_AI()
{
}

UStateRoot_AI::~UStateRoot_AI()
{
	m_pStateMng = nullptr;
}

void UStateRoot_AI::Init(UStateMng_AI * pMng)
{
	m_pStateMng = pMng;
}

void UStateRoot_AI::Enter()
{
}

void UStateRoot_AI::Exit()
{
}

void UStateRoot_AI::Update(float fDeltaTime)
{
}

void UStateRoot_AI::StateMessage(FString sMessage)
{
}

AAIController * UStateRoot_AI::GetRootAI()
{
	if (m_pStateMng == nullptr) return nullptr;
	return m_pStateMng->GetRootAI();
}

void UStateRoot_AI::ChangeState(int eState)
{
	if (m_pStateMng != nullptr)
		m_pStateMng->ChangeState(eState);
}
