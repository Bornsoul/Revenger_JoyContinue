// Fill out your copyright notice in the Description page of Project Settings.

#include "State_GBox_Move.h"
#include "Kismet/KismetMathLibrary.h"
#include "Libraries/Components/ParticleMng/Cpt_ParticleMng.h"
#include "../../AnimInst_GBox.h"
#include "../../FootSmoke.h"

void UState_GBox_Move::Init(class UStateMng_GC* pMng)
{
	Super::Init(pMng);
}

void UState_GBox_Move::Enter()
{
	Super::Enter();

	GetRootChar()->GetAnimInstance()->SetStat_MoveDir(true);
	GetRootChar()->SetHitState(false); //µµÅä¸®´Ù¶÷ÁãÄñÃ´ÄñÃ´
	
	m_pSmoke = GetRootChar()->CreateFootSmoke();


}

void UState_GBox_Move::Exit()
{
	Super::Exit();

	if (GetRootChar()->GetAnimInstance() != nullptr)
	{
		GetRootChar()->GetAnimInstance()->SetStat_MoveDir(false);
		//GetRootChar()->GetAnimInstance()->SetStat_MovementDirection(0.0f);
	}
	if (m_pSmoke != nullptr)
	{
		m_pSmoke->Stop();
		//m_pSmokeParticle->DestroyComponent();
		//m_pSmokeParticle = nullptr;
	}
}

void UState_GBox_Move::Update(float fDeltaTime)
{
	Super::Update(fDeltaTime);

/*	FVector vLookMousePos = GetRootChar()->GetMouseMng()->GetMouse_Location();
	vLookMousePos.Z = GetRootChar()->GetActorLocation().Z;
	GetRootChar()->SetActorRotation(UKismetMathLibrary::FindLookAtRotation(GetRootChar()->GetActorLocation(), vLookMousePos));
	*/
	
	if (m_pSmoke != nullptr)
	{
		m_pSmoke->SetActorLocation(GetRootChar()->GetActorLocation());
	}

	GetRootChar()->ControlMovement(GetRootChar()->GetKeyStateMng()->GetKeyInput());

	if (GetRootChar()->GetKeyStateMng()->GetAnyKeyIsDown() == false)
	{
		ChangeState(static_cast<int32>(E_State_GBox::E_Idle));
		return;
	}
	

	if (GetRootChar()->GetKeyStateMng()->GetKeyIsJustPress(EKeys::LeftMouseButton))
	{
		FVector vMouse = GetRootChar()->GetMouseMng()->GetMouse_Location();

		if (GetRootChar()->Control_Attack(vMouse))
		{
			return;
		}
	}

	if (GetRootChar()->GetKeyStateMng()->GetKeyIsJustPress(EKeys::RightMouseButton))
	{
		if (GetRootChar()->Control_Dodge())
		{
			return;
		}
	}

}

void UState_GBox_Move::StateMessage(FString StateMessage)
{
	Super::StateMessage(StateMessage);
}