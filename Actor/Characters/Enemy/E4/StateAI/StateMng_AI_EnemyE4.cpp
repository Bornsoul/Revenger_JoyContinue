// Fill out your copyright notice in the Description page of Project Settings.

#include "StateMng_AI_EnemyE4.h"
#include "StateRoot_AI_EnemyE4.h"
#include "../AIC_EnemyE4.h"

UStateMng_AI_EnemyE4::UStateMng_AI_EnemyE4()
{

}

UStateMng_AI_EnemyE4::~UStateMng_AI_EnemyE4()
{

}

void UStateMng_AI_EnemyE4::Init(class AAIController* pRoot)
{
	Super::Init(pRoot);

	m_pRootCharacter_Override = Cast<AAIC_EnemyE4>(pRoot);
	if (m_pRootCharacter_Override == nullptr)
	{
		ULOG(TEXT("m_pRootCharacter_Override is nullptr"));
	}

	m_pStateClass.Add(static_cast<int32>(E_StateAI_EnemyE4::E_Normal), NewObject<UState_AI_EnemyE4_Normal>());
	m_pStateClass.Add(static_cast<int32>(E_StateAI_EnemyE4::E_Chase), NewObject<UStateAI_EnemyE4_Chase>());
	m_pStateClass.Add(static_cast<int32>(E_StateAI_EnemyE4::E_Combat), NewObject<UStateAI_EnemyE4_Combat>());
	m_pStateClass.Add(static_cast<int32>(E_StateAI_EnemyE4::E_Lost), NewObject<UStateAI_EnemyE4_Lost>());

	for (TMap<int, class UStateRoot_AI*>::TIterator it = m_pStateClass.CreateIterator(); it; ++it)
	{
		it->Value->Init(this);
	}
}

void UStateMng_AI_EnemyE4::Destroy()
{
	Super::Destroy();
	m_pRootCharacter_Override = nullptr;
}

