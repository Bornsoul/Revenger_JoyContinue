// Fill out your copyright notice in the Description page of Project Settings.

#include "State_GBox_MoveDash.h"
#include "Actor/Characters/GameCharacter.h"
#include "Actor/Characters/Player/GBox/GBox.h"

#include "Libraries/Components/AnimationMng/Cpt_AnimationMng.h"
#include "Kismet/KismetMathLibrary.h"

void UState_GBox_MoveDash::Init(class UStateMng_GC* pMng)
{
	Super::Init(pMng);

}

void UState_GBox_MoveDash::Enter()
{
	Super::Enter();

	FVector2D vKeyInput = GetRootChar()->GetKeyStateMng()->GetKeyInput();
	if (vKeyInput != FVector2D::ZeroVector)
	{
		FRotator pRota_Cam = GetRootChar()->GetCamera()->GetComponentRotation();
		FRotator pRota_Capsule = GetRootChar()->GetCapsuleComponent()->GetComponentRotation();
		FVector pMovementVector = FVector(GetRootChar()->GetKeyStateMng()->GetKeyInput().X, GetRootChar()->GetKeyStateMng()->GetKeyInput().Y*-1.0f, 0.0f);
		FRotator pRota_Normal = UKismetMathLibrary::NormalizedDeltaRotator(pRota_Cam, pRota_Capsule);
		FRotator pRota_Movement = UKismetMathLibrary::NormalizedDeltaRotator(pRota_Cam, UKismetMathLibrary::MakeRotFromX(pMovementVector));
		FRotator pDashRotator = FRotator::ZeroRotator;
		pDashRotator.Yaw = pRota_Movement.Yaw;
		GetRootChar()->SetActorRotation(pDashRotator);
	}

	GetRootChar()->GetAnimationMng()->PlayAnimationSequnceBase(TEXT("MoveDash"), "DefaultSlot", 0.1f, 0.2f, 1.0f);


	m_bMotionEnd = false;
	m_bAttack = false;
}

void UState_GBox_MoveDash::Exit()
{
	Super::Exit();

	GetRootChar()->GetAnimationMng()->StopAnimation_SequnceBaseSlot("DefaultSlot", 0.2f);

}

void UState_GBox_MoveDash::Update(float fDeltaTime)
{
	Super::Update(fDeltaTime);

	if (m_bMotionEnd == true)
	{
		if (GetRootChar()->GetKeyStateMng()->GetAnyKeyIsDown() == true)
		{
			ChangeState(static_cast<int32>(E_State_GBox::E_Move));
			return;
		}
	}
	else
	{
		FVector2D vKeyInput = GetRootChar()->GetKeyStateMng()->GetKeyInput();
		if (vKeyInput != FVector2D::ZeroVector)
		{
			FRotator pRota_Cam = GetRootChar()->GetCamera()->GetComponentRotation();
			FRotator pRota_Capsule = GetRootChar()->GetCapsuleComponent()->GetComponentRotation();
			FVector pMovementVector = FVector(GetRootChar()->GetKeyStateMng()->GetKeyInput().X, GetRootChar()->GetKeyStateMng()->GetKeyInput().Y*-1.0f, 0.0f);
			FRotator pRota_Normal = UKismetMathLibrary::NormalizedDeltaRotator(pRota_Cam, pRota_Capsule);
			FRotator pRota_Movement = UKismetMathLibrary::NormalizedDeltaRotator(pRota_Cam, UKismetMathLibrary::MakeRotFromX(pMovementVector));
			FRotator pDashRotator = FRotator::ZeroRotator;
			pDashRotator.Yaw = pRota_Movement.Yaw;
			GetRootChar()->SetActorRotation(pDashRotator);
		}
	}

	if (GetRootChar()->GetKeyStateMng()->GetKeyIsJustPress(EKeys::LeftMouseButton))
	{
		FVector vMouse = GetRootChar()->GetMouseMng()->GetMouse_Location();
		if (GetRootChar()->Control_Attack(vMouse) == true)
		{
			return;
		}
	}

	if (GetRootChar()->GetKeyStateMng()->GetKeyIsJustPress(EKeys::SpaceBar))
	{
		if (GetRootChar()->Control_Dodge() == true)
		{
			return;
		}
	}
}

void UState_GBox_MoveDash::StateMessage(FString StateMessage)
{
	Super::StateMessage(StateMessage);

	if (StateMessage == "MotionEnd")
	{
		m_bMotionEnd = true;
	}
	else if (StateMessage == "AniEnd")
	{
		ChangeState(static_cast<int32>(E_State_GBox::E_Idle));
	}
}
