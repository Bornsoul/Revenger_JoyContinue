// Fill out your copyright notice in the Description page of Project Settings.

#include "State_GBox_Landing.h"
#include "Kismet/KismetMathLibrary.h"

void UState_GBox_Landing::Init(class UStateMng_GC* pMng)
{
	Super::Init(pMng);

}

void UState_GBox_Landing::Enter()
{
	Super::Enter();
	
	GetRootChar()->Tags.Add(FName("Player"));
	GetRootChar()->SetDialoging(true);
	GetRootChar()->GetAnimationMng()->PlayAnimationMontage("MT_Landing", 1.0f, "Ready");
	GetRootChar()->SetActorHiddenInGame(false);

	m_bMotionEnd = false;
	m_bStartTime = false;
}

void UState_GBox_Landing::Exit()
{
	Super::Exit();

	GetRootChar()->SetDialoging(false);
	GetRootChar()->GetAnimationMng()->StopAnimation_Montage("MT_Landing");
	GetRootChar()->GetMouseMng()->SetMouseCamMove(true);
	GetRootChar()->CreateSpawn_Stick();
	GetRootChar()->SetVisibleHUD(true);
	GetRootChar()->GetShield()->Shield_Spawn();
	GetRootChar()->SetShield(true);


	//GetRootChar()->GetHUD()->GetRootHUD()->Active_TopTitle(true);
}

void UState_GBox_Landing::Update(float fDeltaTime)
{
	Super::Update(fDeltaTime);
	
	if (m_bStartTime == false)
	{
		m_fStartTime_Cur += fDeltaTime;
		if (m_fStartTime_Cur >= m_fStartTime_End)
		{
			m_fStartTime_Cur = 0.0f;
			
			GetRootChar()->GetAnimationMng()->PlayAnimationMontage("MT_Landing", 1.0f, "Start");

			 //PlayAnimationSequnceBase(TEXT("Landing"), TEXT("DefaultSlot"), 0.0f, 0.0f, 1.0f);
			m_bStartTime = true;
		}
	}
	else
	{
		if (m_bMotionEnd)
		{
			ChangeState(static_cast<int32>(E_State_GBox::E_Idle));
			return;
		}
	}
}

void UState_GBox_Landing::StateMessage(FString StateMessage)
{
	Super::StateMessage(StateMessage);

	if (StateMessage == "MotionEnd")
	{
		m_bMotionEnd = true;
	}
}
