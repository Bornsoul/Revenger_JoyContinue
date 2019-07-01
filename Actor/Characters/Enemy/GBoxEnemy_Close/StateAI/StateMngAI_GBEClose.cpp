// Fill out your copyright notice in the Description page of Project Settings.

#include "StateMngAI_GBEClose.h"
#include "StateRootAI_GBEClose.h"
#include "../AIC_GBoxEnemy_Close.h"

UStateMngAI_GBEClose::UStateMngAI_GBEClose()
{

}

UStateMngAI_GBEClose::~UStateMngAI_GBEClose()
{

}

void UStateMngAI_GBEClose::Init(class AAIController* pRoot)
{
	Super::Init(pRoot);

	m_pRootCharacter_Override = Cast<AAIC_GBoxEnemy_Close>(pRoot);
	if (m_pRootCharacter_Override == nullptr)
	{
		ULOG(TEXT("m_pRootCharacter_Override is nullptr"));
	}

	m_pStateClass.Add(static_cast<int32>(E_StateAI_GBEClose::E_Normal), NewObject<UStateAI_GBEC_Normal>());
	m_pStateClass.Add(static_cast<int32>(E_StateAI_GBEClose::E_Chase), NewObject<UStateAI_GBEC_Chase>());
	m_pStateClass.Add(static_cast<int32>(E_StateAI_GBEClose::E_Combat), NewObject<UStateAI_GBEC_Combat>());
	m_pStateClass.Add(static_cast<int32>(E_StateAI_GBEClose::E_Lost), NewObject<UStateAI_GBEC_Lost>());

	for (TMap<int, class UStateRoot_AI*>::TIterator it = m_pStateClass.CreateIterator(); it; ++it)
	{
		it->Value->Init(this);
	}
}

void UStateMngAI_GBEClose::Destroy()
{
	Super::Destroy();
	m_pRootCharacter_Override = nullptr;
}