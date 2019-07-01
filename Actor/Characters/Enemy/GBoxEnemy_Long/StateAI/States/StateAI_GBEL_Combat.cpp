// Fill out your copyright notice in the Description page of Project Settings.

#include "StateAI_GBEL_Combat.h"

void UStateAI_GBEL_Combat::Init(class UStateMng_AI* pMng)
{
	Super::Init(pMng);

	m_pStateClass.Add(static_cast<int32>(E_StateAI_GBEL_Combat::E_Combat_Attack), NewObject<UStateAI_GBEL_Combat_Attack>());
	m_pStateClass.Add(static_cast<int32>(E_StateAI_GBEL_Combat::E_Combat_DistMove), NewObject<UStateAI_GBEL_Combat_DistMove>());

	for (TMap<int32, class UStateRootAI_GBELong*>::TIterator it = m_pStateClass.CreateIterator(); it; ++it)
	{
		it->Value->Init(pMng);
	}
}

void UStateAI_GBEL_Combat::Enter()
{
	Super::Enter();

	float fRand = FMath::RandRange(0.0f, 100.0f);

	if (fRand < 60)
		ChangeCombatState(static_cast<int32>(E_StateAI_GBEL_Combat::E_Combat_Attack));
	else
		ChangeCombatState(static_cast<int32>(E_StateAI_GBEL_Combat::E_Combat_DistMove));

}

void UStateAI_GBEL_Combat::Exit()
{
	Super::Exit();

}

void UStateAI_GBEL_Combat::Update(float fDeltaTime)
{
	Super::Update(fDeltaTime);

	if (m_pCurrentState != nullptr)
		m_pCurrentState->Update(fDeltaTime);
}

void UStateAI_GBEL_Combat::StateMessage(FString StateMessage)
{
	Super::StateMessage(StateMessage);

	if (m_pCurrentState != nullptr)
		m_pCurrentState->StateMessage(StateMessage);
}

void UStateAI_GBEL_Combat::ChangeCombatState(int32 eState)
{
	m_eState = eState;

	if (m_pCurrentState != nullptr)
		m_pCurrentState->Exit();

	for (TMap<int32, class UStateRootAI_GBELong*>::TIterator it = m_pStateClass.CreateIterator(); it; ++it)
	{
		if (it->Key == eState)
		{
			m_pCurrentState = it->Value;
			m_pCurrentState->Enter();
		}
	}
}


