// Fill out your copyright notice in the Description page of Project Settings.

#include "StateAI_GBEC_Combat.h"

void UStateAI_GBEC_Combat::Init(class UStateMng_AI* pMng)
{
	Super::Init(pMng);

	m_pStateClass.Add(static_cast<int32>(E_StateAI_GBEC_Combat::E_Combat_Attack), NewObject<UStateAI_GBEC_Combat_Attack>());
	m_pStateClass.Add(static_cast<int32>(E_StateAI_GBEC_Combat::E_Combat_DistMove), NewObject<UStateAI_GBEC_Combat_DistMove>());
	m_pStateClass.Add(static_cast<int32>(E_StateAI_GBEC_Combat::E_Combat_JumpAttack), NewObject<UUStateAI_GBEC_Combat_JumpAttack>());

	for (TMap<int32, class UStateRootAI_GBEClose*>::TIterator it = m_pStateClass.CreateIterator(); it; ++it)
	{
		it->Value->Init(pMng);
	}
}

void UStateAI_GBEC_Combat::Enter()
{
	Super::Enter();

	float fRand = FMath::RandRange(0.0f, 100.0f);

	if (fRand < 80)
	{
		AActor* pTarget = GetRootAI()->DetectInPerception();
		if (pTarget == nullptr)
		{
			ULOG(TEXT("Combat Attack DetectIn is nullptr"));
			return;
		}
		FVector vEnemyPos = GetRootAI()->GetRootChar()->GetActorLocation();
		FVector vTargetPos = pTarget->GetActorLocation();

		float fDistance = FVector::Distance(vEnemyPos, vTargetPos);
		//ULOG(TEXT("%f"), fDistance);
		if (fDistance <= 1000.0f)
		{
			fRand = FMath::RandRange(0.0f, 100.0f);
			if (fRand < 70)
			{
				ChangeCombatState(static_cast<int32>(E_StateAI_GBEC_Combat::E_Combat_Attack));
			}
			else
			{
				ChangeCombatState(static_cast<int32>(E_StateAI_GBEC_Combat::E_Combat_DistMove));
			}
			
		}
		else
		{
			ChangeCombatState(static_cast<int32>(E_StateAI_GBEC_Combat::E_Combat_JumpAttack));
		}
		
	}
	else
		ChangeCombatState(static_cast<int32>(E_StateAI_GBEC_Combat::E_Combat_DistMove));

}

void UStateAI_GBEC_Combat::Exit()
{
	Super::Exit();

}

void UStateAI_GBEC_Combat::Update(float fDeltaTime)
{
	Super::Update(fDeltaTime);

	if (m_pCurrentState != nullptr)
		m_pCurrentState->Update(fDeltaTime);
}

void UStateAI_GBEC_Combat::StateMessage(FString StateMessage)
{
	Super::StateMessage(StateMessage);

	if (m_pCurrentState != nullptr)
		m_pCurrentState->StateMessage(StateMessage);
}

void UStateAI_GBEC_Combat::ChangeCombatState(int32 eState)
{
	m_eState = eState;

	if (m_pCurrentState != nullptr)
		m_pCurrentState->Exit();

	for (TMap<int32, class UStateRootAI_GBEClose*>::TIterator it = m_pStateClass.CreateIterator(); it; ++it)
	{
		if (it->Key == eState)
		{
			m_pCurrentState = it->Value;
			m_pCurrentState->Enter();
		}
	}
}

