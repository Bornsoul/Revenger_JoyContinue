// Fill out your copyright notice in the Description page of Project Settings.

#include "AI_Command.h"
#include "Actor/Characters/Player/GBox/GBox.h"
#include "Actor/Characters/Enemy/GC_Enemy.h"
#include "Actor/Characters/GameCharacter.h"
#include "Actor/Characters/Enemy/E3/EnemyE3.h"
#include "Actor/Characters/Enemy/E3/AIC_EnemyE3.h"
#include "Engine/Public/EngineUtils.h"

AAI_Command::AAI_Command()
{
	PrimaryActorTick.bCanEverTick = true;

}

void AAI_Command::BeginPlay()
{
	Super::BeginPlay();

	m_fLoopTime_Curr = 0.0f;


	ULOG(TEXT("AI Command is Online"));
}

void AAI_Command::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	Super::EndPlay(EndPlayReason);

	ULOG(TEXT("AI Command is Offline"));
}

void AAI_Command::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	m_fLoopTime_Curr += DeltaTime;
	if (m_fLoopTime_Curr >= m_fLoopTime_End)
	{
		m_fLoopTime_Curr = 0.0f;
		m_pEnemyList.Empty();
		m_pPlayerList.Empty();

		for (TActorIterator<AGameCharacter> pActorItr(GetWorld()); pActorItr; ++pActorItr)
		{
			if (*pActorItr != nullptr)
			{
				if ( pActorItr->ActorHasTag("Enemy") == true)
				{
					AEnemyE3* pEnemy = Cast<AEnemyE3>(*pActorItr);
					if (pEnemy != nullptr)
					{
						m_pEnemyList.Add(pEnemy);
					}
				}
				if (pActorItr->ActorHasTag("Player") == true)
				{
					AGC_Player* pPlayer = Cast<AGC_Player>(*pActorItr);
					if (pPlayer != nullptr)
					{
						m_pPlayerList.Add(pPlayer);
					}
				}
			}			
		}

		for (int i = 0; i < m_pEnemyList.Num(); i++)
		{
			ULOG(TEXT("EnemyList : %d  |  %s"), m_pEnemyList[i]->GetFighter(), *m_pEnemyList[i]->GetName());
		}
		ULOG(TEXT("--------------------------------"));

		switch (m_nState)
		{
			case static_cast<int32>(E_Command::E_None) :

				if (m_nCount >= 2)
				{					
					m_nCount = 2;
					m_nState = static_cast<int32>(E_Command::E_NonFight);
					return;
				}

				for (int i = 0; i < m_pEnemyList.Num(); i++)
				{
					if (m_pEnemyList[i]->GetFighter() == false)
					{
						m_pEnemyList[i]->SetFighter(true);
						m_nCount++;
						return;
					}
				}
			
				break;
			case static_cast<int32>(E_Command::E_NonFight) :

				for (int i = 0; i < m_pEnemyList.Num(); i++)
				{
					m_pEnemyList[i]->GetAI()->State_Fight();
					return;
				}
				break;
			case static_cast<int32>(E_Command::E_Fight) :
				
				break;
		}

// 		if (m_nFighterCount == 0)
// 		{			
// 			if (m_pEnemyList.Num() > 2)
// 			{
// 				if (m_nCount >= 2)
// 				{
// 					m_nFighterCount = 1;
// 					ULOG(TEXT("Phase1 Done"));
// 					return;
// 				}				
// 			}
// 			else
// 			{
// 				for (int e = 0; e < m_pEnemyList.Num(); e++)
// 				{
// 					if (m_pEnemyList[e]->GetFighter() == false)
// 					{
// 						m_pEnemyList[e]->SetFighter(true);
// 						m_pEnemyList[e]->m_nFightCnt++;
// 					}
// 				}
// 				m_nFighterCount = 1;
// 				return;
// 			}
// 
// 			for (int e = 0; e < m_pEnemyList.Num(); e++)
// 			{
// 				float fDist = FVector::Distance(m_pPlayerList[0]->GetActorLocation(), m_pEnemyList[e]->GetActorLocation());
// 
// 				if (fDist <= 800.0f)
// 				{
// 					if (m_pEnemyList[e]->GetFighter() == false && m_pEnemyList[e]->m_nFightCnt == 0)
// 					{
// 						m_pEnemyList[e]->SetFighter(true);
// 						m_pEnemyList[e]->m_nFightCnt++;
// 						m_nCount++;
// 						return;
// 					}
// 				}
// 			}
// 		}
// 		else if (m_nFighterCount == 1)
// 		{
// 			for (int e = 0; e < m_pEnemyList.Num(); e++)
// 			{
// 				if (m_pEnemyList[e]->GetFighter() == false && m_pEnemyList[e]->m_nFightCnt == 0)
// 				{
// 					m_pEnemyList[e]->State_Ready(false);
// 				}
// 				else
// 				{
// 					
// 					ULOG(TEXT("Fighter : %s"), *m_pEnemyList[e]->GetName());
// 					m_pEnemyList[e]->State_Ready(true);
// 
// 					if (m_pEnemyList[e]->GetLife() == false)
// 					{
// 						m_nCount--;
// 						m_nFighterCount--;
// 						ULOG(TEXT("Fighter is Die"));
// 						return;
// 					}
// 				}
// 			}
// 		}
// 		else if (m_nFighterCount == 2)
// 		{
// 
// 		}

		/*if (m_nFighterCount <= 2)
		{
			ULOG(TEXT("@1"));

			for (int e = 0; e < m_pEnemyList.Num(); e++)
			{
				float fDist = FVector::Distance(m_pPlayerList[0]->GetActorLocation(), m_pEnemyList[e]->GetActorLocation());

				if (m_pEnemyList[e]->GetFighter() == false && m_pEnemyList[e]->m_nFightCnt == 0)
				{
					if (fDist <= 800.0f)
					{
						ULOG(TEXT("@2"));
						m_pEnemyList[e]->m_nFightCnt++;
						return;
					}
				}
			}
			for (int e = 0; e < m_pEnemyList.Num(); e++)
			{
				if (m_pEnemyList[e]->m_nFightCnt > 0)
				{
					m_pEnemyList[e]->SetFighter(true);
					m_nFighterCount++;
					ULOG(TEXT("Fight Count : %d"), m_nFighterCount);
					return;
				}
			}
		}
		else
		{
			ULOG(TEXT("@3"));
			for (int e = 0; e < m_pEnemyList.Num(); e++)
			{
				if (m_pEnemyList[e]->GetFighter() == true)
				{
					m_pEnemyList[e]->State_Ready(true);
					if (m_pEnemyList[e]->GetLife() == false && m_pEnemyList[e]->m_nFightCnt > 0)
					{
						m_nFighterCount = 0;
						m_pEnemyList[e]->m_nFightCnt = 0;
						return;
					}
				}
				else
				{
					m_pEnemyList[e]->State_Ready(false);
				}

			}
		}*/


	}




}

