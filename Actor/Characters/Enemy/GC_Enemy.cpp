// Fill out your copyright notice in the Description page of Project Settings.

#include "GC_Enemy.h"
#include "UI/GameHUD/HUD_GameMain.h"
#include "UI/NewGameHUD/HUD_Game.h"
#include "Instance/GameInst_JoyContinue.h"

AGC_Enemy::AGC_Enemy()
{
	AutoPossessAI = EAutoPossessAI::PlacedInWorldOrSpawned;


	static ConstructorHelpers::FClassFinder<ASoulFollow> Const_SoulFollow(TEXT("/Game/1_Project_Main/1_Blueprints/Actor/Props/SoulFollow/BP_SoulFollow.BP_SoulFollow_C"));
	if (Const_SoulFollow.Succeeded()) m_pInst_SoulFollow = Const_SoulFollow.Class;
	
	for (int i = 0; i < 4; i++)
	{
		FDifficultySetting stStruct;
		stStruct.m_eDifficult = static_cast<eDifficultArrow>(i);
		stStruct.m_fHp = 0.0f;
		stStruct.m_fBarrier = 0.0f;
		stStruct.m_fMoveSpeed = 0.0f;
		m_stDifficulty.Add(stStruct);
	}
}

void AGC_Enemy::BeginPlay()
{
	Super::BeginPlay();
	m_pHud = Cast<AHUD_Game>(UGameplayStatics::GetPlayerController(this, 0)->GetHUD());

	//if (m_pHud != nullptr)
	//{
	//	m_pHud->AddOSIEnemy(this);
	//	//m_pHud->AddEnemyHp(3);

	//}

	m_pGamInst = Cast<UGameInst_JoyContinue>(GetGameInstance());
	if (m_pGamInst == nullptr)
	{
		UALERT(TEXT("Game Instance is nullptr"));
		return;
	}

	m_fFallingTime_Curr = 0.0f;
	m_bFalling = false;
}

float AGC_Enemy::GetEnemyHp()
{
	return m_stDifficulty[m_pGamInst->GetDifficulty()].m_fHp;
}

float AGC_Enemy::GetEnemyBarrier()
{
	return m_stDifficulty[m_pGamInst->GetDifficulty()].m_fBarrier;
}

float AGC_Enemy::GetEnemySpeed()
{
	return m_stDifficulty[m_pGamInst->GetDifficulty()].m_fMoveSpeed;
}

int32 AGC_Enemy::GetDifficulty()
{
	return m_pGamInst->GetDifficulty();
}

void AGC_Enemy::AddOisEnemy(AGameCharacter* pTarget, int32 nIconState)
{
	if (m_pHud != nullptr)
	{
		m_pHud->AddOSIEnemy(this, nIconState);
	}
}

void AGC_Enemy::DestroyOsiEnemy()
{
	if (m_pHud != nullptr)
	{
		m_pHud->DestroyOSIEnemy();
	}
}

void AGC_Enemy::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	Super::EndPlay(EndPlayReason);
	m_pHud = nullptr;

	m_pGamInst = nullptr;
}

void AGC_Enemy::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	m_bFalling = GetCharacterMovement()->IsFalling();
	if (m_bFalling == false)
	{
		m_fFallingTime_Curr = 0.0f;
	}
	else
	{
		m_fFallingTime_Curr += DeltaTime;
		if (m_fFallingTime_Curr >= m_fFallingTime_End)
		{
			m_fFallingTime_Curr = 0.0f;			
			//m_pHud->GetOSIMng()->DestroyComponent();
			Destroy();
		}
	}
	
}

void AGC_Enemy::CreateSoulFollow()
{
	if (m_pInst_SoulFollow == nullptr) return;

	AActor* pSrc = GetWorld()->SpawnActor<AActor>(m_pInst_SoulFollow, GetActorLocation(), FRotator::ZeroRotator);
	if (pSrc == nullptr) return;
}