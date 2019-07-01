// Fill out your copyright notice in the Description page of Project Settings.

#include "StateMng_GBEClose.h"

UStateMng_GBEClose::UStateMng_GBEClose()
{

}

UStateMng_GBEClose::~UStateMng_GBEClose()
{

}

void UStateMng_GBEClose::Init(class AGameCharacter* pRoot)
{
	Super::Init(pRoot);
	m_pRootCharacter_Override = Cast<AGBoxEnemy_Close>(pRoot);
	if (m_pRootCharacter_Override == nullptr)
	{
		ULOG(TEXT("m_pRootCharacter_Override is nullptr"));
	}

	m_pStateClass.Add(static_cast<int32>(E_State_GBEClose::E_Idle), NewObject<UState_GBEC_Idle>());
	m_pStateClass.Add(static_cast<int32>(E_State_GBEClose::E_Attack), NewObject<UState_GBEC_Attack>());
	m_pStateClass.Add(static_cast<int32>(E_State_GBEClose::E_Hit), NewObject<UState_GBEC_Hit>());
	m_pStateClass.Add(static_cast<int32>(E_State_GBEClose::E_Die), NewObject<UState_GBEC_Die>());
	m_pStateClass.Add(static_cast<int32>(E_State_GBEClose::E_Spawn), NewObject<UStateRoot_GBEC_Spawn>());
	m_pStateClass.Add(static_cast<int32>(E_State_GBEClose::E_Attack2), NewObject<UState_GBEC_Attack2>());
	m_pStateClass.Add(static_cast<int32>(E_State_GBEClose::E_JumpAttack), NewObject<UState_GBEC_JumpAttack>());
	m_pStateClass.Add(static_cast<int32>(E_State_GBEClose::E_Spin), NewObject<UState_GBEC_Spin>());
	m_pStateClass.Add(static_cast<int32>(E_State_GBEClose::E_DashAttack), NewObject<UState_GBEC_DashAttack>());
	m_pStateClass.Add(static_cast<int32>(E_State_GBEClose::E_Panic), NewObject<UState_GBEC_Panic>());

	for (TMap<int, class UStateRoot_GC*>::TIterator it = m_pStateClass.CreateIterator(); it; ++it)
	{
		it->Value->Init(this);
	}
}

void UStateMng_GBEClose::Destroy()
{
	Super::Destroy();
	m_pRootCharacter_Override = nullptr;
}
