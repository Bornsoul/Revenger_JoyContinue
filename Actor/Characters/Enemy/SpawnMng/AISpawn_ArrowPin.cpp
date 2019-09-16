// Fill out your copyright notice in the Description page of Project Settings.

#include "AISpawn_ArrowPin.h"
#include "Actor/Characters/GameCharacter.h"

UAISpawn_ArrowPin::UAISpawn_ArrowPin()
{
	ArrowSize = 3.0f;
	ArrowColor = FColor(255.0f, 0.0f, 0.0f, 255.0f);

	for (int i = 0; i < 4; i++)
	{
		FDifficultArrow stDifficult;
		stDifficult.m_eDifficult = static_cast<eDifficultArrow>(i);
		m_pInstance_Arrow.Add(stDifficult);
	}
}

int UAISpawn_ArrowPin::GetMaxPhase()
{
	if (m_nDifficulty < 0) return -1;

	return m_pInstance_Arrow[m_nDifficulty].m_pInstance_AI.Num();
}

void UAISpawn_ArrowPin::SpawnAI(int nPhaseNum)
{
	m_pCurrentAI = nullptr;
	if (m_nDifficulty < 0) return;
	if (nPhaseNum >= GetMaxPhase()) return;
	if (nPhaseNum < 0) return;
	if (nPhaseNum >= m_pInstance_Arrow[m_nDifficulty].m_pInstance_AI.Num()) return;
	if (m_pInstance_Arrow[m_nDifficulty].m_pInstance_AI[nPhaseNum] == nullptr) return;

	AGameCharacter* pAI = GetWorld()->SpawnActor<AGameCharacter>(m_pInstance_Arrow[m_nDifficulty].m_pInstance_AI[nPhaseNum], GetComponentLocation(), GetComponentRotation());
	if (pAI == nullptr) return;
	pAI->SetActorLocation(GetComponentLocation());
	pAI->SetActorRotation(GetComponentRotation());

	m_pCurrentAI = pAI;
}

void UAISpawn_ArrowPin::SetDifficulty(int32 nDifficulty)
{
	if (nDifficulty < 0)
	{
		UALERT(TEXT("AI SpawnPin Difficulty is Not Valid"));
		return;
	}
	
	m_nDifficulty = nDifficulty;	
}

bool UAISpawn_ArrowPin::CheckAILife()
{
	if (m_pCurrentAI == nullptr) return true;
	if (m_pCurrentAI->GetLife() == false) return true;

	return false;
}

void UAISpawn_ArrowPin::KillAI()
{
	if (m_pCurrentAI == nullptr) return;
	if (m_pCurrentAI->GetLife() == false) return;

	FDamageEvent* DamageEvent = new FDamageEvent_Hit(100.0f, m_pCurrentAI->GetActorLocation(), m_pCurrentAI->GetActorLocation());
	float fResultDamage = m_pCurrentAI->TakeDamage(100.0f, *DamageEvent, nullptr, nullptr);

}
