// Fill out your copyright notice in the Description page of Project Settings.

#include "HUD_Game.h"
#include "Widget_GHUD.h"
#include "Components/VerticalBox.h"
#include "UI/GameHUD/Widget/OffScreenIndicator/Cpt_OSIMng.h"

AHUD_Game::AHUD_Game()
{
	static ConstructorHelpers::FObjectFinder<UClass> Widget_MainHUD(TEXT("/Game/1_Project_Main/1_Blueprints/UI/NEW/BP_Widget_GHUD.BP_Widget_GHUD_C"));
	if (Widget_MainHUD.Succeeded())
	{
		m_pInst_MainHUD = Widget_MainHUD.Object;
	}
	m_pOSIMng = CreateDefaultSubobject<UCpt_OSIMng>(TEXT("OSI"));

}

void AHUD_Game::Init()
{
	m_pController = Cast<APlayerController>(UGameplayStatics::GetPlayerController(GetWorld(), 0));
	if (m_pController == nullptr)
	{
		ULOG(TEXT("Controller is nullptr"));
		return;
	}

	m_pMainHUD = CreateWidget<UWidget_GHUD>(m_pController, m_pInst_MainHUD);
	if (m_pMainHUD != nullptr)
	{
		m_pMainHUD->AddToViewport();
			
		m_pMainHUD->GetSlowGageHUD()->SetSlowEnter(m_fGageSpeed);
		m_pMainHUD->GetSkillHUD()->SetSkillEnter();
		m_bActive = true;
		SetHudActive(false);
	}

}

void AHUD_Game::SetHudActive(bool bActive)
{
	if (m_pMainHUD == nullptr) return;
	if (m_bActive == bActive) return;

	if ( bActive )
		m_pMainHUD->SetPlayAnimation("Start");
	else
		m_pMainHUD->SetPlayAnimation("End");
	m_bActive = bActive;

}

void AHUD_Game::BeginPlay()
{
	Super::BeginPlay();

	m_bDestroyOSI = false;
}

void AHUD_Game::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	Super::EndPlay(EndPlayReason);
	
	if (m_pMainHUD != nullptr)
	{
		if (m_pMainHUD->IsValidLowLevel())
		{
			m_pMainHUD->RemoveFromViewport();
			m_pMainHUD = nullptr;
		}
	}

	if (m_pOSIMng != nullptr)
	{
		if (m_pOSIMng->IsValidLowLevel())
		{
			m_pOSIMng->DestroyComponent();
			m_pOSIMng = nullptr;
		}
	}
		
}

void AHUD_Game::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (m_pMainHUD->GetSlowGageHUD() != nullptr)
	{
		m_pMainHUD->GetSlowGageHUD()->Tick_SlowGage(DeltaTime);// UGameplayStatics::GetRealTimeSeconds(GetWorld()));
	}

	if (m_pMainHUD->GetSkillHUD() != nullptr)
	{
		m_pMainHUD->GetSkillHUD()->Tick_SkillCoolTime(DeltaTime);
		m_pMainHUD->GetSkillHUD()->Tick_SkillCoolTimeCount(DeltaTime);
		m_pMainHUD->GetSkillHUD()->Tick_SkillShieldTime(DeltaTime);
	}
}

class UWidget_GHUD* AHUD_Game::GetRootHUD()
{
	if (m_pController == nullptr)
	{
		m_pController = Cast<APlayerController>(UGameplayStatics::GetPlayerController(GetWorld(), 0));
		m_pMainHUD = CreateWidget<UWidget_GHUD>(m_pController, m_pInst_MainHUD);
		if (m_pMainHUD != nullptr)
		{
			m_pMainHUD->AddToViewport();

			m_pMainHUD->GetSlowGageHUD()->SetSlowEnter(m_fGageSpeed);
			m_pMainHUD->GetSkillHUD()->SetSkillEnter();
			m_bActive = true;
			SetHudActive(false);
		}

		GetRootHUD();
		return nullptr;
	}

	return m_pMainHUD;
}

void  AHUD_Game::AddOSIEnemy(class AGameCharacter* pEnemy, int32 nIconState)
{
	if (m_pOSIMng == nullptr) return;

	m_pOSIMng->AddPin(pEnemy, nIconState);
}

void AHUD_Game::DestroyOSIEnemy()
{
	if (m_pOSIMng == nullptr) return;
	if (m_bDestroyOSI == true) return;

	m_pOSIMng->DestroyPin();
	m_bDestroyOSI = true;
}