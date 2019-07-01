// Fill out your copyright notice in the Description page of Project Settings.

#include "State_GBox_PortalJump.h"
#include "State_GBox_PortalFalling.h"
#include "Components/ArrowComponent.h"
#include "Kismet/KismetMathLibrary.h"

void UState_GBox_PortalJump::Init(class UStateMng_GC* pMng)
{
	Super::Init(pMng);

}

void UState_GBox_PortalJump::Enter()
{
	Super::Enter();

	if (m_pStartPortal == nullptr)
	{
		ULOG(TEXT("Protal Actor is Nullptr"));
		return;
	}

	m_vStartLoc = m_pStartPortal->GetComponentLocation();
		
	GetRootChar()->GetAnimationMng()->PlayAnimationSequnceBase(TEXT("Portal_Jump"), TEXT("DefaultSlot"), 0.0f, 0.2f, 1.0f);
	m_bMotionEnd = false;
	GetRootChar()->GetSpringArm()->CameraLagSpeed = 5.0f;
	ULOG(TEXT("Joy Jumping"));
}

void UState_GBox_PortalJump::Exit()
{
	Super::Exit();

	m_pStartPortal = nullptr;
	m_pEndPortal = nullptr;
	//GetRootChar()->SetVisibleHUD(true);
	//GetRootChar()->GetAnimationMng()->StopAnimation_SequnceBaseSlot(TEXT("DefaultSlot"), 0.2f);

}

void UState_GBox_PortalJump::Update(float fDeltaTime)
{
	Super::Update(fDeltaTime);

	if (m_pStartPortal == nullptr) return;

	FRotator rView = UKismetMathLibrary::FindLookAtRotation(GetRootChar()->GetActorLocation(), m_vStartLoc);
	rView.Roll = 0.0f;
	rView.Pitch = 0.0f;
	GetRootChar()->SetActorRotation(rView);

	FVector vLoc = GetRootChar()->GetActorLocation();
	for (float i = 0.0f; i <= 4.0f; i += fDeltaTime)
	{
		vLoc = FMath::Lerp(GetRootChar()->GetActorLocation(), m_vStartLoc, i * fDeltaTime);
	}
	GetRootChar()->SetActorLocation(vLoc);

	if (m_bMotionEnd == true)
	{
		UState_GBox_PortalFalling* pState = Cast<UState_GBox_PortalFalling>(GetRootChar()->GetStateMng()->GetStateClassRef(static_cast<int32>(E_State_GBox::E_PortalFalling)));
		if (pState != nullptr)
		{
			pState->SetPortal(m_pEndPortal);
			ChangeState(static_cast<int32>(E_State_GBox::E_PortalFalling));
			return;
		}		
	}
}

void UState_GBox_PortalJump::StateMessage(FString StateMessage)
{
	Super::StateMessage(StateMessage);

	if (StateMessage == "MotionEnd")
	{
		m_bMotionEnd = true;
	}
}

void UState_GBox_PortalJump::SetPortalActor(UArrowComponent* pStartPortal, UArrowComponent* pEndPortal)
{
	m_pStartPortal = pStartPortal;
	m_pEndPortal = pEndPortal;
}