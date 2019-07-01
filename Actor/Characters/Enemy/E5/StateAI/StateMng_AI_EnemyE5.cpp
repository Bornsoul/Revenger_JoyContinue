// Fill out your copyright notice in the Description page of Project Settings.

#include "StateMng_AI_EnemyE5.h"
#include "StateRoot_AI_EnemyE5.h"
#include "../AIC_EnemyE5.h"

UStateMng_AI_EnemyE5::UStateMng_AI_EnemyE5()
{

}

UStateMng_AI_EnemyE5::~UStateMng_AI_EnemyE5()
{

}

void UStateMng_AI_EnemyE5::Init(class AAIController* pRoot)
{
	Super::Init(pRoot);

	m_pRootCharacter_Override = Cast<AAIC_EnemyE5>(pRoot);
	if (m_pRootCharacter_Override == nullptr)
	{
		ULOG(TEXT("m_pRootCharacter_Override is nullptr"));
	}

	m_pStateClass.Add(static_cast<int32>(E_StateAI_EnemyE5::E_Normal), NewObject<UStateAI_EnemyE5_Normal>());
	m_pStateClass.Add(static_cast<int32>(E_StateAI_EnemyE5::E_Chase), NewObject<UStateAI_EnemyE5_Chase>());
	m_pStateClass.Add(static_cast<int32>(E_StateAI_EnemyE5::E_Combat), NewObject<UStateAI_EnemyE5_Combat>());
	m_pStateClass.Add(static_cast<int32>(E_StateAI_EnemyE5::E_Lost), NewObject<UStateAI_EnemyE5_Lost>());

	for (TMap<int, class UStateRoot_AI*>::TIterator it = m_pStateClass.CreateIterator(); it; ++it)
	{
		it->Value->Init(this);
	}
}

void UStateMng_AI_EnemyE5::Destroy()
{
	Super::Destroy();
	m_pRootCharacter_Override = nullptr;
}


