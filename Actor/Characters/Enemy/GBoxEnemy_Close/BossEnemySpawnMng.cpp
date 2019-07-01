// Fill out your copyright notice in the Description page of Project Settings.

#include "BossEnemySpawnMng.h"
#include "BossEnemySpawn_Arrow.h"
#include "Kismet/KismetMathLibrary.h"
#include "Actor/Characters/GameCharacter.h"

// Sets default values
ABossEnemySpawnMng::ABossEnemySpawnMng()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Tags.Add(FName("EnemySpawnMng"));
}

// Called when the game starts or when spawned
void ABossEnemySpawnMng::BeginPlay()
{
	Super::BeginPlay();
	TArray<UActorComponent*> pArrowArray = GetComponentsByClass(UBossEnemySpawn_Arrow::StaticClass());
	for (int i = 0; i < pArrowArray.Num(); i++)
	{
		UBossEnemySpawn_Arrow* pObj = Cast<UBossEnemySpawn_Arrow>(pArrowArray[i]);
		if (pObj == nullptr) continue;
		m_pSpawnPins.Add(pObj);
	}
}

// Called every frame
void ABossEnemySpawnMng::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ABossEnemySpawnMng::SpawnMonsters(int nSpawnNum)
{
	if (m_pSpawnPins.Num() <= 0) return;
	if (m_pInstance_AI.Num() <= 0) return;

	/*ULOG(TEXT("%d"), m_pSpawnPins.Num());
	ULOG(TEXT("%d"), m_pInstance_AI.Num());

	for (int i = 0; i < 100; i++)
	{
		int a22 = UKismetMathLibrary::RandomIntegerInRange(0, m_pSpawnPins.Num());
		ULOG(TEXT("%d"), a22);
	}*/

	//return;
	int nSpawnMax = m_pSpawnPins.Num();

	if (nSpawnNum > nSpawnMax) nSpawnNum = nSpawnMax;
	//ULOG(TEXT("1"));
	TArray<int> nSpawnedNum;
	for (int i = 0; i < nSpawnNum; i++)
	{
		for (int j = 0; j < 100; j++)
		{
			int nRandMonArrow = UKismetMathLibrary::RandomIntegerInRange(0, m_pSpawnPins.Num() - 1);
			bool bOverlab = false;
			for (int k = 0; k < nSpawnedNum.Num(); k++)
			{
				if (nSpawnedNum[k] == nRandMonArrow)
				{
					bOverlab = true;
					break;
				}
			}
			if (bOverlab == false)
			{
				if (m_pSpawnPins[nRandMonArrow] == nullptr) return;
				int nRandMon = UKismetMathLibrary::RandomIntegerInRange(0, m_pInstance_AI.Num() - 1);
				if (m_pInstance_AI[nRandMon] == nullptr) return;
				AGameCharacter* pAI = GetWorld()->SpawnActor<AGameCharacter>(m_pInstance_AI[nRandMon], m_pSpawnPins[nRandMonArrow]->GetComponentLocation(), m_pSpawnPins[nRandMonArrow]->GetComponentRotation());
				if (pAI == nullptr) return;

				pAI->SetActorLocation(m_pSpawnPins[nRandMonArrow]->GetComponentLocation());
				pAI->SetActorRotation(m_pSpawnPins[nRandMonArrow]->GetComponentRotation());

				m_pMonsters.Add(pAI);


				nSpawnedNum.Add(nRandMonArrow);
				break;
			}
		}
	}
}

bool ABossEnemySpawnMng::GetIsMonstarLive()
{
	for (int i = 0; i < m_pMonsters.Num(); i++)
	{
		if (m_pMonsters[i] == nullptr) continue;
		if (m_pMonsters[i]->GetLife() == true) return true;
	}
	return false;
}

void ABossEnemySpawnMng::KillAllMonsters()
{
	for (int i = 0; i < m_pMonsters.Num(); i++)
	{
		if (m_pMonsters[i] == nullptr) continue;
		if (m_pMonsters[i]->GetLife() == false) continue;

		FDamageEvent* DamageEvent = new FDamageEvent_Hit(100.0f, m_pMonsters[i]->GetActorLocation(), m_pMonsters[i]->GetActorLocation());
		float fResultDamage = m_pMonsters[i]->TakeDamage(100.0f, *DamageEvent, nullptr, nullptr);

	}
}