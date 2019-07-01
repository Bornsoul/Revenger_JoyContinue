// Fill out your copyright notice in the Description page of Project Settings.

#include "StateRoot_GBox.h"
#include "StateMng_GBox.h"

UStateRoot_GBox::UStateRoot_GBox()
{

}

UStateRoot_GBox::~UStateRoot_GBox()
{

}

void UStateRoot_GBox::Init(class UStateMng_GC* pMng)
{
	Super::Init(pMng);
	m_pStateMng_Override = Cast<UStateMng_GBox>(pMng);
	if (m_pStateMng_Override == nullptr)
	{
		ULOG(TEXT("m_pStateMng_Override is nullptr"));
	}
}

void UStateRoot_GBox::Enter()
{
	Super::Enter();
}

void UStateRoot_GBox::Exit()
{
	Super::Exit();
}

void UStateRoot_GBox::Update(float fDeltaTime)
{
	Super::Update(fDeltaTime);
}

void UStateRoot_GBox::StateMessage(FString sMessage)
{
	Super::StateMessage(sMessage);
}

AGBox* UStateRoot_GBox::GetRootChar()
{
	if (m_pStateMng_Override == nullptr)
	{
		return nullptr;
	}
	return m_pStateMng_Override->GetRootCharacter_Override();
}