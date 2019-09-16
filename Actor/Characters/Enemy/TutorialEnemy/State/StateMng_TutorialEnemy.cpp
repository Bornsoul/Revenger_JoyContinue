// Fill out your copyright notice in the Description page of Project Settings.

#include "StateMng_TutorialEnemy.h"

UStateMng_TutorialEnemy::UStateMng_TutorialEnemy()
{

}

UStateMng_TutorialEnemy::~UStateMng_TutorialEnemy()
{

}

void UStateMng_TutorialEnemy::Init(class AGameCharacter* pRoot)
{
	Super::Init(pRoot);

	m_pRootCharacter_Override = Cast<ATutorialEnemy>(pRoot);
	if (m_pRootCharacter_Override == nullptr)
	{
		ULOG(TEXT("m_pRootCharacter_Override is nullptr"));
	}

	m_pStateClass.Add(static_cast<int32>(E_State_TutoEnemy::E_Idle), NewObject<UState_TutoEnemy_Idle>());
	m_pStateClass.Add(static_cast<int32>(E_State_TutoEnemy::E_Hit), NewObject<UState_TutoEnemy_Hit>());
	m_pStateClass.Add(static_cast<int32>(E_State_TutoEnemy::E_Die), NewObject<UState_TutoEnemy_Die>());
	m_pStateClass.Add(static_cast<int32>(E_State_TutoEnemy::E_Spawn), NewObject<UState_TutoEnemy_Spawn>());

	for (TMap<int, class UStateRoot_GC*>::TIterator it = m_pStateClass.CreateIterator(); it; ++it)
	{
		it->Value->Init(this);
	}
}

void UStateMng_TutorialEnemy::Destroy()
{
	Super::Destroy();
	m_pRootCharacter_Override = nullptr;
}
