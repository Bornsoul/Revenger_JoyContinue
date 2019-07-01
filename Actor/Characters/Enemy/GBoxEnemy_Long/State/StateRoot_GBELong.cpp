// Fill out your copyright notice in the Description page of Project Settings.

#include "StateRoot_GBELong.h"
#include "StateMng_GBELong.h"

UStateRoot_GBELong::UStateRoot_GBELong()
{

}

UStateRoot_GBELong::~UStateRoot_GBELong()
{

}

void UStateRoot_GBELong::Init(class UStateMng_GC* pMng)
{
	Super::Init(pMng);
	m_pStateMng_Override = Cast<UStateMng_GBELong>(pMng);
	if (m_pStateMng_Override == nullptr)
	{
		ULOG(TEXT("m_pStateMng_Override is nullptr"));
	}
}

void UStateRoot_GBELong::Enter()
{
	Super::Enter();
}

void UStateRoot_GBELong::Exit()
{
	Super::Exit();
}

void UStateRoot_GBELong::Update(float fDeltaTime)
{
	Super::Update(fDeltaTime);
}

void UStateRoot_GBELong::StateMessage(FString sMessage)
{
	Super::StateMessage(sMessage);
}

AGBoxEnemy_Long* UStateRoot_GBELong::GetRootChar()
{
	if (m_pStateMng_Override == nullptr)
	{
		return nullptr;
	}
	return m_pStateMng_Override->GetRootCharacter_Override();
}

