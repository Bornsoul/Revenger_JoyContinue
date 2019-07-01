 // Fill out your copyright notice in the Description page of Project Settings.

#include "State_GBox_SimpleMenu.h"
#include "Kismet/KismetMathLibrary.h"

void UState_GBox_SimpleMenu::Init(class UStateMng_GC* pMng)
{
	Super::Init(pMng);

}

void UState_GBox_SimpleMenu::Enter()
{
	Super::Enter();
	

	GetRootChar()->GetAnimationMng()->PlayAnimationMontage("MT_Landing", 1.0f, "Ready");
	GetRootChar()->GetMouseMng()->SetMouseCamMove(false);

	GetRootChar()->SetActorHiddenInGame(true);
	GetRootChar()->GetSimpleMenu()->Active_SimpleMenu();

	m_bMotionEnd = false;
}

void UState_GBox_SimpleMenu::Exit()
{
	Super::Exit();

	// SomWorks :D //
	//UE_LOG(LogTemp, Fatal, TEXT("Warning!!"));

	//GetRootChar()->GetAnimationMng()->StopAnimation_Montage("MT_Landing");		

	GetRootChar()->Tags.Add(FName("Player"));

}

void UState_GBox_SimpleMenu::Update(float fDeltaTime)
{
	Super::Update(fDeltaTime);

	if (GetRootChar()->GetSimpleMenu()->Menu_GetStart() == true)
	{
		GetRootChar()->GetSimpleMenu()->DeActive_SimpleMenu();
		ChangeState(static_cast<int32>(E_State_GBox::E_Landing));
		return;
	}
}

void UState_GBox_SimpleMenu::StateMessage(FString StateMessage)
{
	Super::StateMessage(StateMessage);
}
