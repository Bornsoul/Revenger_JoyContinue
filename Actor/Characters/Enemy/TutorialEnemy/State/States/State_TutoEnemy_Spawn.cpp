// Fill out your copyright notice in the Description page of Project Settings.

#include "State_TutoEnemy_Spawn.h"

void UState_TutoEnemy_Spawn::Init(class UStateMng_GC* pMng)
{
	Super::Init(pMng);

}

void UState_TutoEnemy_Spawn::Enter()
{
	Super::Enter();

	GetRootChar()->GetAnimationMng()->PlayAnimationSequnceBase(TEXT("Spawn"), TEXT("DefaultSlot"), 0.2f, 0.2f);
	GetRootChar()->SetIgnoreCollision_Hit(true);

	ULOG(TEXT("Spawn Enemy"));
}

void UState_TutoEnemy_Spawn::Exit()
{
	Super::Exit();
	GetRootChar()->GetAnimationMng()->StopAnimation_SequnceBaseSlot(TEXT("DefaultSlot"), 0.2f);
	GetRootChar()->SetIgnoreCollision_Hit(false);
}

void UState_TutoEnemy_Spawn::Update(float fDeltaTime)
{
	Super::Update(fDeltaTime);


}

void UState_TutoEnemy_Spawn::StateMessage(FString StateMessage)
{
	Super::StateMessage(StateMessage);

	if (StateMessage == "MotionEnd")
	{
		ChangeState(static_cast<int32>(E_State_TutoEnemy::E_Idle));
		return;
	}
}

