// Fill out your copyright notice in the Description page of Project Settings.

#include "StateMng_GBox.h"
#include "../GBox.h"

UStateMng_GBox::UStateMng_GBox()
{

}

UStateMng_GBox::~UStateMng_GBox()
{

}

void UStateMng_GBox::Init(class AGameCharacter* pRoot)
{
	Super::Init(pRoot);
	m_pRootCharacter_Override = Cast<AGBox>(pRoot);
	if (m_pRootCharacter_Override == nullptr)
	{
		ULOG(TEXT("m_pRootCharacter_Override is nullptr"));
	}

	m_pStateClass.Add(static_cast<int32>(E_State_GBox::E_Idle), NewObject<UState_GBox_Idle>());
	m_pStateClass.Add(static_cast<int32>(E_State_GBox::E_Move), NewObject<UState_GBox_Move>());
	m_pStateClass.Add(static_cast<int32>(E_State_GBox::E_Dodge), NewObject<UState_GBox_Dodge>());
	m_pStateClass.Add(static_cast<int32>(E_State_GBox::E_Attack), NewObject<UState_GBox_Attack>());
	m_pStateClass.Add(static_cast<int32>(E_State_GBox::E_MoveDash), NewObject<UState_GBox_MoveDash>());
	m_pStateClass.Add(static_cast<int32>(E_State_GBox::E_Die), NewObject<UState_GBox_Die>());
	m_pStateClass.Add(static_cast<int32>(E_State_GBox::E_Landing), NewObject<UState_GBox_Landing>());
	m_pStateClass.Add(static_cast<int32>(E_State_GBox::E_PortalJump), NewObject<UState_GBox_PortalJump>());
	m_pStateClass.Add(static_cast<int32>(E_State_GBox::E_PortalFalling), NewObject<UState_GBox_PortalFalling>());

	m_pStateClass.Add(static_cast<int32>(E_State_GBox::E_SimpleMenu), NewObject<UState_GBox_SimpleMenu>());

	for (TMap<int, class UStateRoot_GC*>::TIterator it = m_pStateClass.CreateIterator(); it; ++it)
	{
		it->Value->Init(this);
	}
}

void UStateMng_GBox::Destroy()
{
	Super::Destroy();
	if (m_pRootCharacter_Override)
	{
		m_pRootCharacter_Override = nullptr;
	}
}