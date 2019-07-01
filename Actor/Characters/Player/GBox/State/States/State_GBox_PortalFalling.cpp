// Fill out your copyright notice in the Description page of Project Settings.

#include "State_GBox_PortalFalling.h"
#include "Components/ArrowComponent.h"
#include "Kismet/KismetMathLibrary.h"

void UState_GBox_PortalFalling::Init(class UStateMng_GC* pMng)
{
	Super::Init(pMng);

}

void UState_GBox_PortalFalling::Enter()
{
	Super::Enter();

	if (m_pStartPortal == nullptr)
	{
		ULOG(TEXT("StartPortal is Nullptr"));
		return;
	}
	
	m_vStartLoc = m_pStartPortal->GetComponentLocation();
	GetRootChar()->SetActorRotation(FRotator(0.0f, m_pStartPortal->GetComponentRotation().Yaw, 0.0f));
	GetRootChar()->SetActorLocation(m_vStartLoc);
	GetRootChar()->GetAnimationMng()->PlayAnimationSequnceBase(TEXT("Portal_Falling"), TEXT("DefaultSlot"), 0.0f, 0.2f, 1.0f);
	m_bMotionEnd = false;
}

void UState_GBox_PortalFalling::Exit()
{
	Super::Exit();
	GetRootChar()->GetSpringArm()->CameraLagSpeed = 10.0f;

	//GetRootChar()->GetSlowGage()->SetInit(GetRootChar(), GetRootChar()->m_vSlowGagePos);

	m_pStartPortal = nullptr;
	GetRootChar()->SetVisibleHUD(true);
	GetRootChar()->GetAnimationMng()->StopAnimation_SequnceBaseSlot(TEXT("DefaultSlot"), 0.2f);

	if (GetRootChar()->GetStick() != nullptr)
	{
		GetRootChar()->GetStick()->Control_Portal(false);
	}

}

void UState_GBox_PortalFalling::Update(float fDeltaTime)
{
	Super::Update(fDeltaTime);

	if (m_pStartPortal == nullptr) return;

	if (m_bMotionEnd == true)
	{		
		ChangeState(static_cast<int32>(E_State_GBox::E_Idle));
		return;
	}
}

void UState_GBox_PortalFalling::StateMessage(FString StateMessage)
{
	Super::StateMessage(StateMessage);

	if (StateMessage == "MotionEnd")
	{
		m_bMotionEnd = true;
	}
}

void UState_GBox_PortalFalling::SetPortal(UArrowComponent * pPortal)
{
	m_pStartPortal = pPortal;
}
