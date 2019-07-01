// Fill out your copyright notice in the Description page of Project Settings.

#include "StateRoot_AI_EnemyE5.h"
#include "StateMng_AI_EnemyE5.h"

UStateRoot_AI_EnemyE5::UStateRoot_AI_EnemyE5()
{

}

UStateRoot_AI_EnemyE5::~UStateRoot_AI_EnemyE5()
{

}

void UStateRoot_AI_EnemyE5::Init(class UStateMng_AI* pMng)
{
	Super::Init(pMng);
	m_pStateMng_Override = Cast<UStateMng_AI_EnemyE5>(pMng);
	if (m_pStateMng_Override == nullptr)
	{
		ULOG(TEXT("m_pStateMng_Override is nullptr"));
	}
}

void UStateRoot_AI_EnemyE5::Enter()
{
	Super::Enter();


}

void UStateRoot_AI_EnemyE5::Exit()
{
	Super::Exit();
}

void UStateRoot_AI_EnemyE5::Update(float fDeltaTime)
{
	Super::Update(fDeltaTime);
}

void UStateRoot_AI_EnemyE5::StateMessage(FString sMessage)
{
	Super::StateMessage(sMessage);
}

AAIC_EnemyE5* UStateRoot_AI_EnemyE5::GetRootAI()
{
	if (m_pStateMng_Override == nullptr)
	{
		return nullptr;
	}
	return m_pStateMng_Override->GetRootAI_Override();
}



