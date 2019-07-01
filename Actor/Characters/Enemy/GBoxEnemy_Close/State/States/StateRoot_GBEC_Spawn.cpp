// Fill out your copyright notice in the Description page of Project Settings.

#include "StateRoot_GBEC_Spawn.h"
#include "Kismet/KismetMathLibrary.h"
#include "Libraries/Components/MaterialEffect/Cpt_MaterialEffect.h"
#include "Libraries/Components/AnimationMng/Cpt_AnimationMng.h"
#include "Libraries/Components/CamShake/Cpt_CamShake.h"

void UStateRoot_GBEC_Spawn::Init(class UStateMng_GC* pMng)
{
	Super::Init(pMng);

}

void UStateRoot_GBEC_Spawn::Enter()
{
	Super::Enter();
	GetRootChar()->GetAI()->SetActiveAI(false);
	//GetRootCharacter()->GetAnimationMng()->PlayAnimationSequnceBase("Hit_" + GetHitDirection(), TEXT("DefaultSlot"), 0.0f, 0.2f, 1.0f);
	//GetRootChar()->GetAnimationMng()->PlayAnimationSequnceBase("Spawn", TEXT("DefaultSlot"), 0.0f, 0.2f, 1.0f);
	GetRootChar()->GetAnimationMng()->PlayAnimationMontage(TEXT("Landing"), 1.0f, TEXT("Start"));

	m_bMotionEnd = false;
	GetRootChar()->SetIgnoreCollision_Hit(true);
}

void UStateRoot_GBEC_Spawn::Exit()
{
	Super::Exit();
	GetRootChar()->GetAI()->SetActiveAI(true);
	//GetRootChar()->GetAnimationMng()->StopAnimation_SequnceBaseSlot(TEXT("DefaultSlot"), 0.2f);
	GetRootChar()->GetAnimationMng()->StopAnimation_Montage(TEXT("Landing"));

	GetRootChar()->SetIgnoreCollision_Hit(false);
	m_bLand = false;
	GetRootChar()->SpawnMonsters();
}

void UStateRoot_GBEC_Spawn::Update(float fDeltaTime)
{
	Super::Update(fDeltaTime);
	if (m_bLand == false)
	{
		m_fWaitTime += fDeltaTime;
		if (m_fWaitTime > 0.5f)
		{
			GetRootChar()->GetAnimationMng()->PlayAnimationMontage(TEXT("Landing"), 1.0f, TEXT("Loop2"));
			m_bLand = true;
		}
	}
	
	if (m_bMotionEnd == true)
	{
		ChangeState(static_cast<int32>(E_State_GBEClose::E_Idle));
		return;
	}

}

void UStateRoot_GBEC_Spawn::StateMessage(FString StateMessage)
{
	Super::StateMessage(StateMessage);

	if (StateMessage == "MotionEnd")
	{
		m_bMotionEnd = true;
	}
	else if (StateMessage == "Landing")
	{
		GetRootChar()->GetCamShake()->PlayCameraShake(TEXT("Landing"));
	}
}
