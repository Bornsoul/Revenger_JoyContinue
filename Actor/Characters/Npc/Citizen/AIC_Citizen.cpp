// Fill out your copyright notice in the Description page of Project Settings.

#include "AIC_Citizen.h"

#include "Citizen.h"
#include "Perception/AIPerceptionComponent.h"
#include "Perception/AISenseConfig_Sight.h"

AAIC_Citizen::AAIC_Citizen()
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

void AAIC_Citizen::BeginPlay()
{
	Super::BeginPlay();

}

void AAIC_Citizen::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	Super::EndPlay(EndPlayReason);

}

void AAIC_Citizen::Possess(APawn * Pawn)
{
	Super::Possess(Pawn);

	if (Pawn == nullptr)
	{
		ULOG(TEXT("AI Possess Pawn is nullptr"))
			return;
	}

	m_pRoot = Cast<ACitizen>(Pawn);
	if (m_pRoot == nullptr)
	{
		ULOG(TEXT("AI Possess Root is nullptr"));
		return;
	}
}

void AAIC_Citizen::InitAI()
{
	
	SetActiveAI(true);

	ULOG(TEXT("AI Controller Start"));
}

void AAIC_Citizen::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AAIC_Citizen::SetActiveAI(bool bActive)
{
	m_bActive = bActive;
}

void AAIC_Citizen::StopAI()
{
	SetActiveAI(false);
}

AActor * AAIC_Citizen::DetectInPerception()
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



