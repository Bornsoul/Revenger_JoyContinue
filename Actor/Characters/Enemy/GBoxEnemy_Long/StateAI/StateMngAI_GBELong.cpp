// Fill out your copyright notice in the Description page of Project Settings.

#include "StateMngAI_GBELong.h"
#include "StateRootAI_GBELong.h"
#include "../AIC_GBoxEnemy_Long.h"

UStateMngAI_GBELong::UStateMngAI_GBELong()
{

}

UStateMngAI_GBELong::~UStateMngAI_GBELong()
{

}

void UStateMngAI_GBELong::Init(class AAIController* pRoot)
{
	Super::Init(pRoot);

	m_pRootCharacter_Override = Cast<AAIC_GBoxEnemy_Long>(pRoot);
	if (m_pRootCharacter_Override == nullptr)
	{
		ULOG(TEXT("m_pRootCharacter_Override is nullptr"));
	}

	m_pStateClass.Add(static_cast<int32>(E_StateAI_GBELong::E_Normal), NewObject<UStateAI_GBEL_Normal>());
	m_pStateClass.Add(static_cast<int32>(E_StateAI_GBELong::E_Chase), NewObject<UStateAI_GBEL_Chase>());
	m_pStateClass.Add(static_cast<int32>(E_StateAI_GBELong::E_Combat), NewObject<UStateAI_GBEL_Combat>());
	m_pStateClass.Add(static_cast<int32>(E_StateAI_GBELong::E_Lost), NewObject<UStateAI_GBEL_Lost>());

	for (TMap<int, class UStateRoot_AI*>::TIterator it = m_pStateClass.CreateIterator(); it; ++it)
	{
		it->Value->Init(this);
	}
}

void UStateMngAI_GBELong::Destroy()
{
	Super::Destroy();
	m_pRootCharacter_Override = nullptr;
}
