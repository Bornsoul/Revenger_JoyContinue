// Fill out your copyright notice in the Description page of Project Settings.

#include "Tutorial_AISpawnMng.h"
#include "Actor/Characters/Enemy/SpawnMng/AISpawn_ArrowPin.h"
#include "Actor/Characters/Player/GBox/GBox.h"

ATutorial_AISpawnMng::ATutorial_AISpawnMng()
{
	PrimaryActorTick.bCanEverTick = true;

}

void ATutorial_AISpawnMng::BeginPlay()
{
	Super::BeginPlay();
	
	TArray<UActorComponent*> pArrow = GetComponentsByClass(UAISpawn_ArrowPin::StaticClass());
	for (int i = 0; i < pArrow.Num(); i++)
	{
		UAISpawn_ArrowPin* pObj = Cast<UAISpawn_ArrowPin>(pArrow[i]);
		if (pObj == nullptr) continue;
		pObj->SetDifficulty(0);
		m_pSpawnPins.Add(pObj);

		if (pObj->GetMaxPhase() >= m_nMaxPhase)
		{
			m_nMaxPhase = pObj->GetMaxPhase();
		}
	}

	m_nCurrPhase = 0;
	m_bActive = false;
}

void ATutorial_AISpawnMng::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	Super::EndPlay(EndPlayReason);

	m_pSpawnPins.Empty();

}

void ATutorial_AISpawnMng::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (m_bClearState)
	{
		bool bCheck = false;

		for (int i = 0; i < m_pSpawnPins.Num(); i++)
		{
			if (m_pSpawnPins[i]->CheckAILife() == false)
			{
				bCheck = true;
				break;
			}

			if (bCheck == false && m_nCurrPhase <= m_nMaxPhase)
			{
				SpawnAI();
			}

			if (bCheck == false && m_nCurrPhase > m_nMaxPhase)
			{
				m_bClearSuccess = true;
				m_bClearState = false;
			}

		}
	}
}

void ATutorial_AISpawnMng::SpawnAI()
{

	for (int i = 0; i < m_pSpawnPins.Num(); i++)
	{
		m_pSpawnPins[i]->SpawnAI(m_nCurrPhase);
	}
	
	m_nCurrPhase++;
}

void ATutorial_AISpawnMng::ClearAI()
{
	
	if (m_pSpawnPins.Num() > 0)
	{
		for (int i = 0; i < m_pSpawnPins.Num(); i++)
		{
			if (m_pSpawnPins[i]->CheckAILife()) continue;

			m_pSpawnPins[i]->KillAI();
		}
	}
	m_nCurrPhase = 0;
	m_bClearSuccess = true;
}

class AGameCharacter* ATutorial_AISpawnMng::GetCharacter(const int32 nIndex)
{
	return m_pSpawnPins[nIndex]->GetCurrentAI();
}

