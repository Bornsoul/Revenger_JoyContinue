// Fill out your copyright notice in the Description page of Project Settings.

#include "StateAI_EnemyE4_Combat.h"
#include "Actor/Characters/Enemy/E4/AIC_EnemyE4.h"

void UStateAI_EnemyE4_Combat::Init(class UStateMng_AI* pMng)
{
	Super::Init(pMng);

	m_pStateClass.Add(static_cast<int32>(E_StateAI_EnemyE4_Combat::E_Combat_Attack), NewObject<UStateAI_EnemyE4_Combat_Attack>());
	m_pStateClass.Add(static_cast<int32>(E_StateAI_EnemyE4_Combat::E_Combat_DistMove), NewObject<UStateAI_EnemyE4_Combat_DistMove>());


	for (TMap<int32, class UStateRoot_AI_EnemyE4*>::TIterator it = m_pStateClass.CreateIterator(); it; ++it)
	{
		it->Value->Init(pMng);
	}
}

void UStateAI_EnemyE4_Combat::Enter()
{
	Super::Enter();

	//ChangeCombatState(static_cast<int32>(E_StateAI_EnemyE4_Combat::E_Combat_Attack));


	float fRand = FMath::RandRange(0.0f, 100.0f);

	if (fRand < 75)
	{
		AActor* pTarget = GetRootAI()->DetectInPerception();

		if (pTarget != nullptr)
		{
			FVector vEnemyPos = GetRootAI()->GetRootChar()->GetActorLocation();
			FVector vTargetPos = pTarget->GetActorLocation();

			float fDistance = FVector::Distance(vEnemyPos, vTargetPos);
			if (fDistance <= 400.0f)
			{
				ChangeCombatState(static_cast<int32>(E_StateAI_EnemyE4_Combat::E_Combat_DistMove));
			}
			else
			{
				ChangeCombatState(static_cast<int32>(E_StateAI_EnemyE4_Combat::E_Combat_Attack));
			}
		}
	}
	else
	{
		ChangeCombatState(static_cast<int32>(E_StateAI_EnemyE4_Combat::E_Combat_DistMove));

	}

	/*if (fRand < 70)
		ChangeCombatState(static_cast<int32>(E_StateAI_EnemyE4_Combat::E_Combat_Attack));
	else
		ChangeCombatState(static_cast<int32>(E_StateAI_EnemyE4_Combat::E_Combat_DistMove));
*/

}

void UStateAI_EnemyE4_Combat::Exit()
{
	Super::Exit();

}

void UStateAI_EnemyE4_Combat::Update(float fDeltaTime)
{
	Super::Update(fDeltaTime);

	/*AActor* pTarget = GetRootAI()->DetectInPerception();

	if (pTarget != nullptr)
	{
		FVector vEnemyPos = GetRootAI()->GetRootChar()->GetActorLocation();
		FVector vTargetPos = pTarget->GetActorLocation();

		float fDistance = FVector::Distance(vEnemyPos, vTargetPos);
		if (fDistance <= 400.0f)
		{
			ChangeCombatState(static_cast<int32>(E_StateAI_EnemyE4_Combat::E_Combat_DistMove));
		}
	}*/

	if (m_pCurrentState != nullptr)
		m_pCurrentState->Update(fDeltaTime);
}

void UStateAI_EnemyE4_Combat::StateMessage(FString StateMessage)
{
	Super::StateMessage(StateMessage);

	if (m_pCurrentState != nullptr)
		m_pCurrentState->StateMessage(StateMessage);
}

void UStateAI_EnemyE4_Combat::ChangeCombatState(int32 eState)
{
	m_eState = eState;

	if (m_pCurrentState != nullptr)
		m_pCurrentState->Exit();

	for (TMap<int32, class UStateRoot_AI_EnemyE4*>::TIterator it = m_pStateClass.CreateIterator(); it; ++it)
	{
		if (it->Key == eState)
		{
			m_pCurrentState = it->Value;
			m_pCurrentState->Enter();
		}
	}
}
