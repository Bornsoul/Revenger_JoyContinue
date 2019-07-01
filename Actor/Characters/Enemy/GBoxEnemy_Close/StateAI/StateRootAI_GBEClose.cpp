// Fill out your copyright notice in the Description page of Project Settings.

#include "StateRootAI_GBEClose.h"
#include "StateMngAI_GBEClose.h"

UStateRootAI_GBEClose::UStateRootAI_GBEClose()
{

}

UStateRootAI_GBEClose::~UStateRootAI_GBEClose()
{

}

void UStateRootAI_GBEClose::Init(class UStateMng_AI* pMng)
{
	Super::Init(pMng);
	m_pStateMng_Override = Cast<UStateMngAI_GBEClose>(pMng);
	if (m_pStateMng_Override == nullptr)
	{
		ULOG(TEXT("m_pStateMng_Override is nullptr"));
	}
}

void UStateRootAI_GBEClose::Enter()
{
	Super::Enter();
}

void UStateRootAI_GBEClose::Exit()
{
	Super::Exit();
}

void UStateRootAI_GBEClose::Update(float fDeltaTime)
{
	Super::Update(fDeltaTime);
}

void UStateRootAI_GBEClose::StateMessage(FString sMessage)
{
	Super::StateMessage(sMessage);
}

AAIC_GBoxEnemy_Close* UStateRootAI_GBEClose::GetRootAI()
{
	if (m_pStateMng_Override == nullptr)
	{
		return nullptr;
	}
	return m_pStateMng_Override->GetRootAI_Override();
}

