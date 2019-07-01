// Fill out your copyright notice in the Description page of Project Settings.

#include "StateMng_GBELong.h"

UStateMng_GBELong::UStateMng_GBELong()
{

}

UStateMng_GBELong::~UStateMng_GBELong()
{

}

void UStateMng_GBELong::Init(class AGameCharacter* pRoot)
{
	Super::Init(pRoot);
	m_pRootCharacter_Override = Cast<AGBoxEnemy_Long>(pRoot);
	if (m_pRootCharacter_Override == nullptr)
	{
		ULOG(TEXT("m_pRootCharacter_Override is nullptr"));
	}

	m_pStateClass.Add(static_cast<int32>(E_State_GBELong::E_Idle), NewObject<UState_GBEL_Idle>());
	m_pStateClass.Add(static_cast<int32>(E_State_GBELong::E_Attack), NewObject<UState_GBEL_Attack>());
	m_pStateClass.Add(static_cast<int32>(E_State_GBELong::E_Hit), NewObject<UState_GBEL_Hit>());
	m_pStateClass.Add(static_cast<int32>(E_State_GBELong::E_Die), NewObject<UState_GBEL_Die>());

	for (TMap<int, class UStateRoot_GC*>::TIterator it = m_pStateClass.CreateIterator(); it; ++it)
	{
		it->Value->Init(this);
	}
}

void UStateMng_GBELong::Destroy()
{
	Super::Destroy();
	m_pRootCharacter_Override = nullptr;
}
