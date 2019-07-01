// Fill out your copyright notice in the Description page of Project Settings.

#include "AISpawn_ArrowPin.h"
#include "Actor/Characters/GameCharacter.h"

UAISpawn_ArrowPin::UAISpawn_ArrowPin()
{
	ArrowSize = 3.0f;
	ArrowColor = FColor(255.0f, 0.0f, 0.0f, 255.0f);
}

int UAISpawn_ArrowPin::GetMaxPhase()
{
	return m_pInstance_AI.Num();
}

void UAISpawn_ArrowPin::SpawnAI(int nPhaseNum)
{
	m_pCurrentAI = nullptr;
	if (nPhaseNum >= GetMaxPhase()) return;
	if (nPhaseNum < 0) return;
	if (nPhaseNum >= m_pInstance_AI.Num()) return;
	if (m_pInstance_AI[nPhaseNum] == nullptr) return;

	AGameCharacter* pAI = GetWorld()->SpawnActor<AGameCharacter>(m_pInstance_AI[nPhaseNum], GetComponentLocation(), GetComponentRotation());
	if (pAI == nullptr) return;

	pAI->SetActorLocation(GetComponentLocation());
	pAI->SetActorRotation(GetComponentRotation());

	m_pCurrentAI = pAI;
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