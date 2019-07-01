// Fill out your copyright notice in the Description page of Project Settings.

#include "State_GBEC_Panic.h"
#include "Libraries/Components/AnimationMng/Cpt_AnimationMng.h"
#include "Kismet/KismetMathLibrary.h"
#include "Libraries/Components/ParticleMng/Cpt_ParticleMng.h"
#include "Libraries/Components/CamShake/Cpt_CamShake.h"
#include "Libraries/Components/WarningSpace/Cpt_WarningSpace.h"
#include "Libraries/Components/WarningSpace/WarningSpace_Root.h"
#include "Libraries/Components/MaterialEffect/Cpt_MaterialEffect.h"
#include "Actor/Characters/Enemy/EnemyBarrier.h"

void UState_GBEC_Panic::Init(class UStateMng_GC* pMng)
{
	Super::Init(pMng);

}

void UState_GBEC_Panic::Enter()
{
	Super::Enter();
	m_bMotion = false;
	m_bOpen = false;
	if (m_bBreak == true)
	{
		m_sAni = TEXT("Panic_Break");
		m_fWaitTime = 1.5f;

		GetRootChar()->GetBarrier()->Hit_Barrier(100);
	}
	else
	{
		m_sAni = TEXT("Panic_Panic");
		m_fWaitTime = 9.0f;
	}
	GetRootChar()->GetAnimationMng()->PlayAnimationMontage(m_sAni, 1.0f, TEXT("Start"));
	GetRootChar()->GetAI()->StopMovement();
	GetRootChar()->GetAI()->SetActiveAI(false);
	m_fTime = 0.0f;



	PanicHit(true);
}

void UState_GBEC_Panic::PanicHit(bool bStiffen)
{
	GetRootChar()->GetMaterialEffect()->ActiveEffect(E_MaterialEffect::E_Hit2);
	if(bStiffen==true) GetRootChar()->GetAnimationMng()->Active_Stiffen(0.3f, 0.001f);
}

void UState_GBEC_Panic::Exit()
{
	Super::Exit();
	GetRootChar()->GetAI()->SetActiveAI(true);

	GetRootChar()->GetAnimationMng()->StopAnimation_Montage(m_sAni);

	if (GetRootChar()->GetBarrier()->GetActiveState() == false)
	{
		GetRootChar()->Active_Barrier();
	}

	
	
}

void UState_GBEC_Panic::Update(float fDeltaTime)
{
	Super::Update(fDeltaTime);
	
	if (m_bOpen == false)
	{
		m_fTime += fDeltaTime;
		if (m_fTime >= m_fWaitTime)
		{
			GetRootChar()->SpawnMonsters();
			GetRootChar()->GetAnimationMng()->PlayAnimationMontage(m_sAni, 1.0f, TEXT("End"));
			m_bOpen = true;
		}
	}
	else
	{

	}
	

	if (m_bMotion)
	{
		
		ChangeState(static_cast<int32>(E_State_GBEClose::E_Idle));
		return;
	}

}

void UState_GBEC_Panic::StateMessage(FString StateMessage)
{
	Super::StateMessage(StateMessage);

	if (StateMessage == "MotionEnd2")
	{
		
		m_bMotion = true;
	}

}