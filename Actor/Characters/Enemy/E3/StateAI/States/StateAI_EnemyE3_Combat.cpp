// Fill out your copyright notice in the Description page of Project Settings.

#include "StateAI_EnemyE3_Combat.h"
#include "Actor/Characters/Enemy/E3/AIC_EnemyE3.h"

void UStateAI_EnemyE3_Combat::Init(class UStateMng_AI* pMng)
{
	Super::Init(pMng);

	m_pStateClass.Add(static_cast<int32>(E_StateAI_EnemyE3_Combat::E_Combat_Attack), NewObject<UStateAI_EnemyE3_Combat_Attack>());
	m_pStateClass.Add(static_cast<int32>(E_StateAI_EnemyE3_Combat::E_Combat_DistMove), NewObject<UStateAI_EnemyE3_Combat_DistMove>());
	m_pStateClass.Add(static_cast<int32>(E_StateAI_EnemyE3_Combat::E_Combat_Crazy), NewObject<UStateAI_EnemyE3_Combat_Crazy>());	

	for (TMap<int32, class UStateRoot_AI_EnemyE3*>::TIterator it = m_pStateClass.CreateIterator(); it; ++it)
	{
		it->Value->Init(pMng);
	}
}

void UStateAI_EnemyE3_Combat::Enter()
{
	Super::Enter();

	float fRand = FMath::RandRange(0.0f, 100.0f);

	if (m_bDistCombat == false)
	{
		if (fRand < 90.0f)
		{
			// 		AActor* pTarget = GetRootAI()->DetectInPerception();
			// 		if (pTarget == nullptr)
			// 		{
			// 			ULOG(TEXT("Combat Attack DetectIn is nullptr"));
			// 			return;
			// 		}
			// 		FVector vEnemyPos = GetRootAI()->GetRootChar()->GetActorLocation();
			// 		FVector vTargetPos = pTarget->GetActorLocation();
			// 
			// 		float fDistance = FVector::Distance(vEnemyPos, vTargetPos);

			ChangeCombatState(static_cast<int32>(E_StateAI_EnemyE3_Combat::E_Combat_Attack));

		}
		else
		{
			ChangeCombatState(static_cast<int32>(E_StateAI_EnemyE3_Combat::E_Combat_DistMove));

		}
		//ULOG(TEXT("Combat2"));
	}
	else
	{
		ChangeCombatState(static_cast<int32>(E_StateAI_EnemyE3_Combat::E_Combat_Crazy));
	}

	//m_bDistCombat = true;
}

void UStateAI_EnemyE3_Combat::Exit()
{
	Super::Exit();
	//m_bDistCombat = false;
}

void UStateAI_EnemyE3_Combat::Update(float fDeltaTime)
{
	Super::Update(fDeltaTime);

	if (m_pCurrentState != nullptr)
		m_pCurrentState->Update(fDeltaTime);
}

void UStateAI_EnemyE3_Combat::StateMessage(FString StateMessage)
{
	Super::StateMessage(StateMessage);

	if (m_pCurrentState != nullptr)
		m_pCurrentState->StateMessage(StateMessage);
}

void UStateAI_EnemyE3_Combat::ChangeCombatState(int32 eState)
{
	m_eState = eState;

	if (m_pCurrentState != nullptr)
		m_pCurrentState->Exit();

	for (TMap<int32, class UStateRoot_AI_EnemyE3*>::TIterator it = m_pStateClass.CreateIterator(); it; ++it)
	{
		if (it->Key == eState)
		{
			m_pCurrentState = it->Value;
			m_pCurrentState->Enter();
		}
	}
}
void UStateAI_EnemyE3_Combat::SetDistanceCombat()
{
	//ULOG(TEXT("Combat"));
	//ChangeCombatState(static_cast<int32>(E_StateAI_EnemyE3_Combat::E_Combat_Crazy));
	m_bDistCombat = true;	
}
