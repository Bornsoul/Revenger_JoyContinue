// Fill out your copyright notice in the Description page of Project Settings.

#include "StateRoot_TutorialEnemy.h"
#include "StateMng_TutorialEnemy.h"

UStateRoot_TutorialEnemy::UStateRoot_TutorialEnemy()
{
}

UStateRoot_TutorialEnemy::~UStateRoot_TutorialEnemy()
{
}

void UStateRoot_TutorialEnemy::Init(class UStateMng_GC* pMng)
{
	Super::Init(pMng);
	m_pStateMng_Override = Cast<UStateMng_TutorialEnemy>(pMng);
	if (m_pStateMng_Override == nullptr)
	{
		ULOG(TEXT("m_pStateMng_Override is nullptr"));
	}
}

void UStateRoot_TutorialEnemy::Enter()
{
	Super::Enter();
}

void UStateRoot_TutorialEnemy::Exit()
{
	Super::Exit();
}

void UStateRoot_TutorialEnemy::Update(float fDeltaTime)
{
	Super::Update(fDeltaTime);
}

void UStateRoot_TutorialEnemy::StateMessage(FString sMessage)
{
	Super::StateMessage(sMessage);
}

ATutorialEnemy* UStateRoot_TutorialEnemy::GetRootChar()
{
	if (m_pStateMng_Override == nullptr)
	{
		return nullptr;
	}
	return m_pStateMng_Override->GetRootCharacter_Override();
}

