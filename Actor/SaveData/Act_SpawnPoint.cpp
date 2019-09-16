// Fill out your copyright notice in the Description page of Project Settings.

#include "Act_SpawnPoint.h"
#include "Components/BoxComponent.h"
#include "Components/ArrowComponent.h"
#include "Cpt_GameSave.h"

AAct_SpawnPoint::AAct_SpawnPoint()
{
	PrimaryActorTick.bCanEverTick = true;

	m_pBoxColider = CreateDefaultSubobject<UBoxComponent>(TEXT("BoxComp"));
	if (m_pBoxColider != nullptr)
	{
		m_pBoxColider->SetBoxExtent(FVector(500.0f, 500.0f, 60.0f));
		m_pBoxColider->OnComponentBeginOverlap.AddDynamic(this, &AAct_SpawnPoint::OnOverlapBegin);

		RootComponent = m_pBoxColider;
	}

	m_pSpawnArrow = CreateDefaultSubobject<UArrowComponent>(TEXT("ArrowComp"));
	if (m_pSpawnArrow != nullptr)
	{
		m_pSpawnArrow->ArrowSize = 2.0f;
		m_pSpawnArrow->SetRelativeLocation(FVector(150.0f, 0.0f, 0.0f));
		m_pSpawnArrow->SetupAttachment(m_pBoxColider);
	}

	m_pComp_Save = CreateDefaultSubobject<UCpt_GameSave>(TEXT("DataSaveComp"));
	if (m_pComp_Save == nullptr)
	{
		ULOG(TEXT("Data Save Comp is nullptr"));
		return;
	}
}

void AAct_SpawnPoint::BeginPlay()
{
	Super::BeginPlay();

}

void AAct_SpawnPoint::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	Super::EndPlay(EndPlayReason);

}

void AAct_SpawnPoint::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	/*if (m_pComp_Save == nullptr)
		return;

	if (m_bInRound == false) 
		return;

	if (m_bInRound)
	{
		if (m_pComp_Save->Load_Data()->m_nSpawnPoint != m_nCurrentPoint)
		{
			m_bInRound = false;
			return;
		}
	}*/
}

void AAct_SpawnPoint::OnOverlapBegin(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OtherActor && (OtherActor != this) && OtherComp)
	{
		if (OtherActor->ActorHasTag(TEXT("Player")) == true)
		{					
			m_pComp_Save->Load_Data()->m_nSpawnPoint = m_nCurrentPoint;

			if (m_pComp_Save->Save_Data("Test01", 0, m_fSaveAlertTime) == true)
			{
				m_bInRound = true;
				return;
			}
		}
	}
}

