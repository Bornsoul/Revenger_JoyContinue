// Fill out your copyright notice in the Description page of Project Settings.

#include "StateRootAI_GBELong.h"

#include "StateMngAI_GBELong.h"

UStateRootAI_GBELong::UStateRootAI_GBELong()
{

}

UStateRootAI_GBELong::~UStateRootAI_GBELong()
{

}

void UStateRootAI_GBELong::Init(class UStateMng_AI* pMng)
{
	Super::Init(pMng);
	m_pStateMng_Override = Cast<UStateMngAI_GBELong>(pMng);
	if (m_pStateMng_Override == nullptr)
	{
		ULOG(TEXT("m_pStateMng_Override is nullptr"));
	}
}

void UStateRootAI_GBELong::Enter()
{
	Super::Enter();
}

void UStateRootAI_GBELong::Exit()
{
	Super::Exit();
}

void UStateRootAI_GBELong::Update(float fDeltaTime)
{
	Super::Update(fDeltaTime);
}

void UStateRootAI_GBELong::StateMessage(FString sMessage)
{
	Super::StateMessage(sMessage);
}

AAIC_GBoxEnemy_Long* UStateRootAI_GBELong::GetRootAI()
{
	if (m_pStateMng_Override == nullptr)
	{
		return nullptr;
	}
	return m_pStateMng_Override->GetRootAI_Override();
}


