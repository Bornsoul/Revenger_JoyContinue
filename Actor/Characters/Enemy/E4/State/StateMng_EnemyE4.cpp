// Fill out your copyright notice in the Description page of Project Settings.

#include "StateMng_EnemyE4.h"

UStateMng_EnemyE4::UStateMng_EnemyE4()
{

}

UStateMng_EnemyE4::~UStateMng_EnemyE4()
{

}

void UStateMng_EnemyE4::Init(class AGameCharacter* pRoot)
{
	Super::Init(pRoot);
	m_pRootCharacter_Override = Cast<AEnemyE4>(pRoot);
	if (m_pRootCharacter_Override == nullptr)
	{
		ULOG(TEXT("m_pRootCharacter_Override is nullptr"));
	}

	m_pStateClass.Add(static_cast<int32>(E_State_EnemyE4::E_Idle), NewObject<UState_EnemyE4_Idle>());
	m_pStateClass.Add(static_cast<int32>(E_State_EnemyE4::E_Hit), NewObject<UState_EnemyE4_Hit>());
	m_pStateClass.Add(static_cast<int32>(E_State_EnemyE4::E_Attack), NewObject<UState_EnemyE4_Attack>());
	m_pStateClass.Add(static_cast<int32>(E_State_EnemyE4::E_Die), NewObject<UState_EnemyE4_Die>());
	m_pStateClass.Add(static_cast<int32>(E_State_EnemyE4::E_Spawn), NewObject<UState_EnemyE4_Spawn>());

	for (TMap<int, class UStateRoot_GC*>::TIterator it = m_pStateClass.CreateIterator(); it; ++it)
	{
		it->Value->Init(this);
	}
}

void UStateMng_EnemyE4::Destroy()
{
	Super::Destroy();
	m_pRootCharacter_Override = nullptr;
}