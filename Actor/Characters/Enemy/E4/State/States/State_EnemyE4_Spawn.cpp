// Fill out your copyright notice in the Description page of Project Settings.

#include "State_EnemyE4_Spawn.h"
#include "Kismet/KismetMathLibrary.h"
#include "Libraries/Components/MaterialEffect/Cpt_MaterialEffect.h"
#include "Libraries/Components/AnimationMng/Cpt_AnimationMng.h"
#include "Libraries/Components/CamShake/Cpt_CamShake.h"

void UState_EnemyE4_Spawn::Init(class UStateMng_GC* pMng)
{
	Super::Init(pMng);

}

void UState_EnemyE4_Spawn::Enter()
{
	Super::Enter();
	GetRootChar()->GetAI()->SetActiveAI(false);
	//GetRootCharacter()->GetAnimationMng()->PlayAnimationSequnceBase("Hit_" + GetHitDirection(), TEXT("DefaultSlot"), 0.0f, 0.2f, 1.0f);
	GetRootChar()->GetAnimationMng()->PlayAnimationSequnceBase("Spawn", TEXT("DefaultSlot"), 0.0f, 0.2f, 1.0f);
	m_bMotionEnd = false;
	GetRootChar()->SetIgnoreCollision_Hit(true);
}

void UState_EnemyE4_Spawn::Exit()
{
	Super::Exit();
	GetRootChar()->GetAI()->SetActiveAI(true);
	GetRootChar()->GetAnimationMng()->StopAnimation_SequnceBaseSlot(TEXT("DefaultSlot"), 0.2f);
	GetRootChar()->SetIgnoreCollision_Hit(false);
}

void UState_EnemyE4_Spawn::Update(float fDeltaTime)
{
	Super::Update(fDeltaTime);

	if (m_bMotionEnd == true)
	{
		ChangeState(static_cast<int32>(E_State_EnemyE3::E_Idle));
		return;
	}

}

void UState_EnemyE4_Spawn::StateMessage(FString StateMessage)
{
	Super::StateMessage(StateMessage);

	if (StateMessage == "MotionEnd")
	{
		m_bMotionEnd = true;
	}
	else if (StateMessage == "Landing")
	{
		//GetRootChar()->GetCamShake()->PlayCameraShake(TEXT("Landing"));
	}//
}


