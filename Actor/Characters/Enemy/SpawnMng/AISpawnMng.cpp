// Fill out your copyright notice in the Description page of Project Settings.

#include "AISpawnMng.h"
#include "AISpawn_Wall.h"

#include "Actor/Props/MovePortal/MovePortal.h"
#include "Actor/Characters/Npc/CitizenCage/CitizenCage.h"
#include "Components/BoxComponent.h"
#include "Actor/SaveData/Cpt_GameSave.h"
#include "Actor/Characters/Player/GBox/GBox.h"

#include "Instance/GameInst_JoyContinue.h"

// Sets default values
AAISpawnMng::AAISpawnMng()
{
	PrimaryActorTick.bCanEverTick = true;

	m_pCollider = CreateDefaultSubobject<UBoxComponent>(TEXT("Collider"));
	m_pCollider->OnComponentBeginOverlap.AddDynamic(this, &AAISpawnMng::OnOverlapBegin);
	m_pCollider->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Ignore);
	m_pCollider->SetCollisionResponseToChannel(ECC_Pawn, ECollisionResponse::ECR_Overlap);

	RootComponent = m_pCollider;

	m_pSaveData = CreateDefaultSubobject<UCpt_GameSave>(TEXT("SaveData"));
	if (m_pSaveData == nullptr)
	{
		ULOG(TEXT("SaveData is nullptr"));
		return;
	}
}

void AAISpawnMng::BeginPlay()
{
	Super::BeginPlay();

	/*if (m_pSaveData->Check_DataValid())
	{
		m_nDifficultLevel = m_pSaveData->Load_Data()->m_nDifficulty;
		
	}
	else
	{
		ULOG(TEXT("Data is Lost"));
		return;
	}*/
	
	UGameInst_JoyContinue* pGInst = Cast<UGameInst_JoyContinue>(GetWorld()->GetGameInstance());
	if (pGInst != nullptr)
	{
		pGInst->SetDifficulty(m_nDifficultLevel);
	}

	TArray<UActorComponent*> pArrowArray = GetComponentsByClass(UAISpawn_ArrowPin::StaticClass());	
	for (int i = 0; i < pArrowArray.Num(); i++)
	{
	
		UAISpawn_ArrowPin* pObj = Cast<UAISpawn_ArrowPin>(pArrowArray[i]);
		if (pObj == nullptr) continue;		
		pObj->SetDifficulty(m_nDifficultLevel);
		m_pSpawnPins.Add(pObj);

		if (pObj->GetMaxPhase() >= m_nMaxPhase)
		{
			m_nMaxPhase = pObj->GetMaxPhase();
		}
	}

	TArray<UActorComponent*> pWallArray = GetComponentsByClass(UAISpawn_Wall::StaticClass());
	for (int i = 0; i < pWallArray.Num(); i++)
	{
		UAISpawn_Wall* pObj = Cast<UAISpawn_Wall>(pWallArray[i]);
		if (pObj == nullptr) continue;
		m_pSpawnWalls.Add(pObj);

		m_pSpawnWalls[i]->Wall_Destroy();
	}

	if (m_pPortal != nullptr)
	{
		m_pPortal->SetCircleActive(false);		
		m_pPortal->SetActorHiddenInGame(true);
	}
	else
	{
		ULOG(TEXT("%s | Portal is Nullptr"), *GetName());
	}


	m_nCurrPhase = 0;
	m_bActive = false;
	m_bPortalUsed = false;
}

void  AAISpawnMng::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	Super::EndPlay(EndPlayReason);
	m_pSpawnPins.Empty();
	m_pSpawnWalls.Empty();
	
	if (m_pSaveData != nullptr)
	{
		if (m_pSaveData->IsValidLowLevel())
		{
			m_pSaveData = nullptr;
		}
	}

	if (m_pPortal != nullptr)
	{
		if (m_pPortal->IsValidLowLevel())
		{
			m_pPortal = nullptr; 
		}
	}

	if (m_pCitizenCage != nullptr)
	{
		if (m_pCitizenCage->IsValidLowLevel())
		{
			m_pCitizenCage = nullptr;
		}
	}

	if (m_pCollider != nullptr)
	{
		if (m_pCollider->IsValidLowLevel())
		{
			m_pCollider = nullptr;
		}
	}
}

void AAISpawnMng::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (m_bActive == true)
	{
		bool bCheck = false;

		
		for (int i = 0; i < m_pSpawnPins.Num(); i++)
		{
			if (m_pSpawnPins[i]->CheckAILife() == false)
			{
				bCheck = true;
				break;
			}
		}

		if (bCheck == false && m_nCurrPhase <= m_nMaxPhase)
		{
			SpawnAIs();
		}
		if (bCheck == false && m_nCurrPhase > m_nMaxPhase)
		{
			StageClear();
			//ULOG(TEXT("End"));
		}

	
	}
	else
	{
		if (m_bPortalUsed == true)
		{
			if (m_pPortal != nullptr)
			{
				if (m_pPortal->GetActive() == true && m_pPortal->GetUsed() == true)
				{
					m_bPortalUsed = false;
					Destroy();
					return;
				}
			}
		}
	}
}

void AAISpawnMng::SpawnAIs()
{
	//m_pDifficultSetting[m_nDifficultLevel]m_pMobMaxHp[]
	

	for (int i = 0; i < m_pSpawnPins.Num(); i++)
	{
		m_pSpawnPins[i]->SpawnAI(m_nCurrPhase);
	}

	for (int i = 0; i < m_pSpawnWalls.Num(); i++)
	{
		if (m_pSpawnWalls[i] != nullptr)
		{
			m_pSpawnWalls[i]->Wall_Spawn();
		}
	}

	m_bStageClear = false;
	m_nCurrPhase++;
}

void AAISpawnMng::StageClear()
{
	m_bActive = false;
	if (m_pCitizenCage != nullptr)
	{
		m_pCitizenCage->SetMovePortal(m_pPortal);
		m_pCitizenCage->SetCitizenActive(true);
	}
	if (m_pPortal != nullptr)
	{
		/*m_pPortal->SetActorHiddenInGame(false);
		m_pPortal->SpawnPortal();*/

		m_pPortal->SetCircleActive(true);

		m_bPortalUsed = true;		
	}

	for (int i = 0; i < m_pSpawnWalls.Num(); i++)
	{
		if (m_pSpawnWalls[i] != nullptr)
		{
			m_pSpawnWalls[i]->Wall_Destroy();
		}
	}

	if (m_bBossStage == true)
	{
		AGBox* pPlayerPawn = Cast<AGBox>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));
		if (pPlayerPawn != nullptr)
		{
			pPlayerPawn->ShowResult();
		}
	}

	m_bStageClear = true;

}

void AAISpawnMng::OnOverlapBegin(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (m_bActive == true) return;
	if (OtherActor && (OtherActor != this) && OtherComp)
	{
		if (OtherActor->ActorHasTag(FName(TEXT("Player"))) == true)
		{
			m_bActive = true;

			SpawnAIs();
		}
	}
}

void AAISpawnMng::KillAllMonsters()
{
	for (int i = 0; i < m_pSpawnPins.Num(); i++)
	{
		if (m_pSpawnPins[i] == nullptr) continue;
		if (m_pSpawnPins[i]->CheckAILife() == true) continue;

		m_pSpawnPins[i]->KillAI();
	}
}

void AAISpawnMng::BeginedOverlap()
{
	m_bActive = true;
	SpawnAIs();
}
