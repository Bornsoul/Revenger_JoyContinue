// Fill out your copyright notice in the Description page of Project Settings.

#include "State_GBox_Idle.h"
#include "Kismet/KismetMathLibrary.h"

void UState_GBox_Idle::Init(class UStateMng_GC* pMng)
{
	Super::Init(pMng);

}

void UState_GBox_Idle::Enter()
{
	Super::Enter();

	GetRootChar()->SetStick_MouseRot(true);

}

void UState_GBox_Idle::Exit()
{
	Super::Exit();

	GetRootChar()->SetStick_MouseRot(false);

}

void UState_GBox_Idle::Update(float fDeltaTime)
{
	Super::Update(fDeltaTime);

	


	if (GetRootChar()->GetKeyStateMng()->GetAnyKeyIsDown())
	{
		ChangeState(static_cast<int32>(E_State_GBox::E_Move));
		//ChangeState(static_cast<int32>(E_State_GBox::E_MoveDash));

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

void UState_GBox_Idle::StateMessage(FString StateMessage)
{
	Super::StateMessage(StateMessage);
}