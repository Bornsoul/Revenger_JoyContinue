// Fill out your copyright notice in the Description page of Project Settings.

#include "StateMng_AI.h"
#include "StateRoot_AI.h"

UStateMng_AI::UStateMng_AI()
{
}

UStateMng_AI::~UStateMng_AI()
{
	Destroy();
}

void UStateMng_AI::Init(AAIController * pRoot)
{
	m_pRootCharacter = pRoot;
	m_pCurrentState = nullptr;
	m_bDestroyed = false;
}

void UStateMng_AI::Destroy()
{
	if (m_bDestroyed) return;
	m_pRootCharacter = nullptr;
	m_pCurrentState = nullptr;

	for (TMap<int, class UStateRoot_AI*>::TIterator it = m_pStateClass.CreateIterator(); it; ++it)
	{
		it->Value->Exit();
		it->Value->ConditionalBeginDestroy();
	}

	m_pStateClass.Empty();
	m_bDestroyed = true;
}

void UStateMng_AI::Update(float fDeltaTime)
{
	if (m_pCurrentState != nullptr)
	{
		m_pCurrentState->Update(fDeltaTime);
	}
}

void UStateMng_AI::ChangeState(int eState)
{
	m_eState = eState;

	if (m_pCurrentState != nullptr)
	{
		m_pCurrentState->Exit();
	}

	for (TMap<int, class UStateRoot_AI*>::TIterator it = m_pStateClass.CreateIterator(); it; ++it)
	{
		if (it->Key == eState)
		{
			m_pCurrentState = it->Value;
			m_pCurrentState->Enter();
		}
	}
}

UStateRoot_AI * UStateMng_AI::GetStateClassRef(int eFindState)
{
	for (TMap<int, class UStateRoot_AI*>::TIterator it = m_pStateClass.CreateIterator(); it; ++it)
	{
		if (it->Key == eFindState)
		{
			return it->Value;
		}
	}
	return nullptr;
}

void UStateMng_AI::StateMessage(FString sMessage)
{
	if (m_pCurrentState != nullptr)
	{
		m_pCurrentState->StateMessage(sMessage);
	}
}
