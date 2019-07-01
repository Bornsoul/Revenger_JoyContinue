// Fill out your copyright notice in the Description page of Project Settings.

#include "StateMng_AI_EnemyE3.h"
#include "StateRoot_AI_EnemyE3.h"
#include "../AIC_EnemyE3.h"

UStateMng_AI_EnemyE3::UStateMng_AI_EnemyE3()
{

}

UStateMng_AI_EnemyE3::~UStateMng_AI_EnemyE3()
{

}

void UStateMng_AI_EnemyE3::Init(class AAIController* pRoot)
{
	Super::Init(pRoot);

	m_pRootCharacter_Override = Cast<AAIC_EnemyE3>(pRoot);
	if (m_pRootCharacter_Override == nullptr)
	{
		ULOG(TEXT("m_pRootCharacter_Override is nullptr"));
	}

	m_pStateClass.Add(static_cast<int32>(E_StateAI_EnemyE3::E_Normal), NewObject<UStateAI_EnemyE3_Normal>());
	m_pStateClass.Add(static_cast<int32>(E_StateAI_EnemyE3::E_Chase), NewObject<UState_AI_EnemyE3_Chase>());
	m_pStateClass.Add(static_cast<int32>(E_StateAI_EnemyE3::E_Combat), NewObject<UStateAI_EnemyE3_Combat>());
	m_pStateClass.Add(static_cast<int32>(E_StateAI_EnemyE3::E_Lost), NewObject<UStateAI_EnemyE3_Lost>());
	

	for (TMap<int, class UStateRoot_AI*>::TIterator it = m_pStateClass.CreateIterator(); it; ++it)
	{
		it->Value->Init(this);
	}
}

void UStateMng_AI_EnemyE3::Destroy()
{
	Super::Destroy();
	m_pRootCharacter_Override = nullptr;
}
