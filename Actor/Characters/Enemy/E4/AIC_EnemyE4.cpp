// Fill out your copyright notice in the Description page of Project Settings.

#include "AIC_EnemyE4.h"
#include "EnemyE4.h"
#include "../GC_Enemy.h"
#include "StateAI/StateMng_AI_EnemyE4.h"

#include "Perception/AIPerceptionComponent.h"
#include "Perception/AISenseConfig_Sight.h"


AAIC_EnemyE4::AAIC_EnemyE4()
{
	PrimaryActorTick.bCanEverTick = true;

	m_pPerception = CreateDefaultSubobject<UAIPerceptionComponent>(TEXT("AIPerceptionCom"));
	m_pSightConfig = CreateDefaultSubobject<UAISenseConfig_Sight>(TEXT("AIConfigSightCom"));

	if (m_pPerception && m_pSightConfig)
	{
		m_pPerception->ConfigureSense(*m_pSightConfig);
		m_pPerception->SetDominantSense(m_pSightConfig->GetSenseImplementation());

		m_pSightConfig->SightRadius = m_fAISightRadius;
		m_pSightConfig->LoseSightRadius = m_fAILoseSightRadius;
		m_pSightConfig->PeripheralVisionAngleDegrees = m_fAIFieldOfView;
		m_pSightConfig->SetMaxAge(12.0f);
		m_pSightConfig->DetectionByAffiliation.bDetectEnemies = true;
		m_pSightConfig->DetectionByAffiliation.bDetectFriendlies = false;
		m_pSightConfig->DetectionByAffiliation.bDetectNeutrals = false;

		SetPerceptionComponent(*m_pPerception);
	}

	SetGenericTeamId(FGenericTeamId(1));
}

void AAIC_EnemyE4::BeginPlay()
{
	Super::BeginPlay();

}

void AAIC_EnemyE4::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	Super::EndPlay(EndPlayReason);

	if (m_pStateMng != nullptr)
		m_pStateMng->Destroy();

	m_pStateMng = nullptr;
}

void AAIC_EnemyE4::Possess(APawn * Pawn)
{
	Super::Possess(Pawn);

	if (Pawn == nullptr)
	{
		ULOG(TEXT("AI Possess Pawn is nullptr"))
			return;
	}

	m_pRoot = Cast<AEnemyE4>(Pawn);
	if (m_pRoot == nullptr)
	{
		ULOG(TEXT("AI Possess Root is nullptr"));
		return;
	}
}

void AAIC_EnemyE4::InitAI()
{
	m_pStateMng = NewObject<UStateMng_AI_EnemyE4>();
	if (m_pStateMng != nullptr)
	{
		m_pStateMng->Init(this);
		m_pStateMng->ChangeState(static_cast<int32>(E_StateAI_EnemyE4::E_Normal));
	}
	else
	{
		ULOG(TEXT("AI StateMng is nullptr"));
		return;
	}

	SetActiveAI(true);

}

void AAIC_EnemyE4::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (m_bActive == true)
	{
		if (m_pStateMng != nullptr) m_pStateMng->Update(DeltaTime);
	}
}

void AAIC_EnemyE4::SetActiveAI(bool bActive)
{
	m_bActive = bActive;
}

void AAIC_EnemyE4::StopAI()
{
	SetActiveAI(false);
	if (m_pStateMng != nullptr)
		m_pStateMng->Destroy();

	m_pStateMng = nullptr;
}

AActor * AAIC_EnemyE4::DetectInPerception()
{
	if (m_pPerception != nullptr)
	{
		TArray<AActor*> pList;
		m_pPerception->GetCurrentlyPerceivedActors(UAISenseConfig_Sight::StaticClass(), pList);

		for (int i = 0; i < pList.Num(); i++)
		{
			if (pList[i]->ActorHasTag("Player") == true)
			{
				return pList[i];
			}
		}
	}
	return nullptr;
}

AActor * AAIC_EnemyE4::DetectInPerceptionDie()
{
	if (m_pPerception != nullptr)
	{
		TArray<AActor*> pList;
		m_pPerception->GetCurrentlyPerceivedActors(UAISenseConfig_Sight::StaticClass(), pList);

		for (int i = 0; i < pList.Num(); i++)
		{
			if (pList[i]->ActorHasTag("PlayerDie") == true)
			{
				return pList[i];
			}
		}
	}
	return nullptr;
}
