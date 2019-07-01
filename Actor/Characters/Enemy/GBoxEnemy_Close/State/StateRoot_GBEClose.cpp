// Fill out your copyright notice in the Description page of Project Settings.

#include "StateRoot_GBEClose.h"
#include "StateMng_GBEClose.h"

UStateRoot_GBEClose::UStateRoot_GBEClose()
{
}

UStateRoot_GBEClose::~UStateRoot_GBEClose()
{
}

void UStateRoot_GBEClose::Init(class UStateMng_GC* pMng)
{
	Super::Init(pMng);
	m_pStateMng_Override = Cast<UStateMng_GBEClose>(pMng);
	if (m_pStateMng_Override == nullptr)
	{
		ULOG(TEXT("m_pStateMng_Override is nullptr"));
	}
}

void UStateRoot_GBEClose::Enter()
{
	Super::Enter();
}

void UStateRoot_GBEClose::Exit()
{
	Super::Exit();
}

void UStateRoot_GBEClose::Update(float fDeltaTime)
{
	Super::Update(fDeltaTime);
}

void UStateRoot_GBEClose::StateMessage(FString sMessage)
{
	Super::StateMessage(sMessage);
}

AGBoxEnemy_Close* UStateRoot_GBEClose::GetRootChar()
{
	if (m_pStateMng_Override == nullptr)
	{
		return nullptr;
	}
	return m_pStateMng_Override->GetRootCharacter_Override();
}
