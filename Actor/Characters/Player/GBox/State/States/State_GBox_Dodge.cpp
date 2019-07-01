// Fill out your copyright notice in the Description page of Project Settings.

#include "State_GBox_Dodge.h"
#include "Libraries/Components/AnimationMng/Cpt_AnimationMng.h"
#include "Kismet/KismetMathLibrary.h"
#include "Libraries/Components/GhostTrail/Cpt_GhostTrail.h"


void UState_GBox_Dodge::Init(class UStateMng_GC* pMng)
{
	Super::Init(pMng);

}

void UState_GBox_Dodge::Enter()
{
	Super::Enter();

	m_bMotionEnd = false;
	GetRootChar()->SetIgnoreCollision_Pawn(true);

	FVector vLookMousePos = GetRootChar()->GetMouseMng()->GetMouse_Location();
	vLookMousePos.Z = GetRootChar()->GetActorLocation().Z;
	GetRootChar()->SetActorRotation(UKismetMathLibrary::FindLookAtRotation(GetRootChar()->GetActorLocation(), vLookMousePos));

	/*FVector2D vKeyInput = GetRootChar()->GetKeyStateMng()->GetKeyInput();
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
	*/
	m_fDashTime = 0.0f;
	m_fFallingTime_Cur = 0.0f;

	FVector vPushDirection = GetRootChar()->GetActorForwardVector();
	vPushDirection.Normalize();
	vPushDirection.Z = 0.0f;
	GetRootChar()->GetCharacterMovement()->AddImpulse(vPushDirection * 20000.0f, true);

	GetRootChar()->GetAnimationMng()->PlayAnimationSequnceBase(TEXT("Dodge"), TEXT("DefaultSlot"), 0.0f, 0.2f, 1.0f);
	GetRootChar()->GetGhostTrail()->Active_TickGhostTrailEffect(TEXT("Dash"), 0.01f, 0.1f);
}

void UState_GBox_Dodge::Exit()
{
	Super::Exit();
	GetRootChar()->GetGhostTrail()->DeActive_TickGhostTrailEffect(TEXT("Dash"));
	GetRootChar()->SetIgnoreCollision_Pawn(false);
	GetRootChar()->GetAnimationMng()->StopAnimation_SequnceBaseSlot(TEXT("DefaultSlot"), 0.2f);

}

void UState_GBox_Dodge::Update(float fDeltaTime)
{
	Super::Update(fDeltaTime);

	m_fDashTime += fDeltaTime;
	if (m_fDashTime > 0.15f)
	{

		m_bMotionEnd = true;
	}

		
	if (GetRootChar()->GetCharacterMovement()->IsFalling() == true)
	{
		m_fFallingTime_Cur += fDeltaTime;
		if (m_fFallingTime_Cur >= 0.01f)
		{
			m_fFallingTime_Cur = 0.0f;
			ULOG(TEXT("Dash Falling ZeroVector!"));
			GetRootChar()->GetCharacterMovement()->Velocity = FVector::ZeroVector;
			ChangeState(static_cast<int32>(E_State_GBox::E_Idle));
			return;
		}		
	}
	else
	{
		m_fFallingTime_Cur = 0.0f;
	}

	if (m_bMotionEnd)
	{
		ChangeState(static_cast<int32>(E_State_GBox::E_Idle));
		return;
	}
}

void UState_GBox_Dodge::StateMessage(FString StateMessage)
{
	Super::StateMessage(StateMessage);

	if (StateMessage == "MotionEnd")
	{
		m_bMotionEnd = true;
	}
}
