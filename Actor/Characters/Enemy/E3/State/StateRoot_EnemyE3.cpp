// Fill out your copyright notice in the Description page of Project Settings.

#include "StateRoot_EnemyE3.h"
#include "StateMng_EnemyE3.h"

UStateRoot_EnemyE3::UStateRoot_EnemyE3()
{

}

UStateRoot_EnemyE3::~UStateRoot_EnemyE3()
{

}

void UStateRoot_EnemyE3::Init(class UStateMng_GC* pMng)
{
	Super::Init(pMng);
	m_pStateMng_Override = Cast<UStateMng_EnemyE3>(pMng);
	if (m_pStateMng_Override == nullptr)
	{
		ULOG(TEXT("m_pStateMng_Override is nullptr"));
	}
}

void UStateRoot_EnemyE3::Enter()
{
	Super::Enter();
}

void UStateRoot_EnemyE3::Exit()
{
	Super::Exit();
}

void UStateRoot_EnemyE3::Update(float fDeltaTime)
{
	Super::Update(fDeltaTime);
}

void UStateRoot_EnemyE3::StateMessage(FString sMessage)
{
	Super::StateMessage(sMessage);
}

AEnemyE3* UStateRoot_EnemyE3::GetRootChar()
{
	if (m_pStateMng_Override == nullptr)
	{
		return nullptr;
	}
	return m_pStateMng_Override->GetRootCharacter_Override();
}
