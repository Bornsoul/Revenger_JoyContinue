// Fill out your copyright notice in the Description page of Project Settings.

#include "AISpawnMng.h"
#include "AISpawn_ArrowPin.h"
#include "AISpawn_Wall.h"

#include "Actor/Props/MovePortal/MovePortal.h"
#include "Actor/Characters/Npc/CitizenCage/CitizenCage.h"
#include "Components/BoxComponent.h"

#include "Actor/Characters/Player/GBox/GBox.h"

// Sets default values
AAISpawnMng::AAISpawnMng()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	m_pCollider = CreateDefaultSubobject<UBoxComponent>(TEXT("Collider"));
	m_pCollider->OnComponentBeginOverlap.AddDynamic(this, &AAISpawnMng::OnOverlapBegin);
	m_pCollider->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Ignore);
	m_pCollider->SetCollisionResponseToChannel(ECC_Pawn, ECollisionResponse::ECR_Overlap);

	RootComponent = m_pCollider;
}

// Called when the game starts or when spawned
void AAISpawnMng::BeginPlay()
{
	Super::BeginPlay();

	TArray<UActorComponent*> pArrowArray = GetComponentsByClass(UAISpawn_ArrowPin::StaticClass());
	for (int i = 0; i < pArrowArray.Num(); i++)
	{
		UAISpawn_ArrowPin* pObj = Cast<UAISpawn_ArrowPin>(pArrowArray[i]);
		if (pObj == nullptr) continue;
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
		ULOG(TEXT("Portal is Nullptr"))
	}
	m_nCurrPhase = 0;
	m_bActive = false;
	m_bPortalUsed = false;
	//ULOG(TEXT("Max Phase = %d"), m_nMaxPhase);
}

void  AAISpawnMng::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	Super::EndPlay(EndPlayReason);
	m_pSpawnPins.Empty();
	m_pSpawnWalls.Empty();
	
	if (m_pPortal != nullptr)
	{
		m_pPortal->ConditionalBeginDestroy();
		m_pPortal = nullptr;
	}

	ULOG(TEXT("%s is Destroy"), *GetName());
}

// Called every frame
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
			ULOG(TEXT("End"));
		}

		/*if (m_bStageClear == true)
		{
			if (m_pCitizenCage == nullptr)
			{
				m_pCitizenCage->SetMovePortal(m_pPortal);
				m_pCitizenCage->SetCitizenActive(true);
				return;
			}
		}*/
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
	/*for (int i = 0; i < m_pDoors.Num(); i++)
	{
		m_pDoors[i]->Open();
	}*/


}

void AAISpawnMng::OnOverlapBegin(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (m_bActive == true) return;
	if (OtherActor && (OtherActor != this) && OtherComp)
	{
		if (OtherActor->ActorHasTag(FName(TEXT("Player"))) == true)
		{
			m_bActive = true;
			/*for (int i = 0; i < m_pDoors.Num(); i++)
			{
				m_pDoors[i]->Close();
			}*/
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