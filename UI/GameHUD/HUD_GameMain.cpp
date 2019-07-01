// Fill out your copyright notice in the Description page of Project Settings.

#include "HUD_GameMain.h"
#include "Widget/Widget_GameHUD.h"
#include "Widget/OffScreenIndicator/Cpt_OSIMng.h"
#include "UI/Enemy/HpSystem/Cpt_EnemyHp.h"

AHUD_GameMain::AHUD_GameMain()
{
	static ConstructorHelpers::FObjectFinder<UClass> Widget_MainHUD(TEXT("/Game/1_Project_Main/1_Blueprints/UI/GameHUD/BP_Widget_GameHUD.BP_Widget_GameHUD_C"));
	if (Widget_MainHUD.Succeeded())
	{
		m_pInst_MainHUD = Widget_MainHUD.Object;
	}

	m_pOSIMng = CreateDefaultSubobject<UCpt_OSIMng>(TEXT("OSI"));

	//ULOG(TEXT("GameMain Init"));

}

void AHUD_GameMain::Init()
{
	if (m_pInst_MainHUD != nullptr)
	{
		m_pMainHUD = CreateWidget<UWidget_GameHUD>(UGameplayStatics::GetPlayerController(GetWorld(), 0), m_pInst_MainHUD);
		if (m_pMainHUD != nullptr) m_pMainHUD->AddToViewport();
	}
	else
	{
		ULOG(TEXT("UI Fail"));
	}
}

void AHUD_GameMain::AddViewPort()
{


}

void AHUD_GameMain::BeginPlay()
{
	Super::BeginPlay();

}

void AHUD_GameMain::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	Super::EndPlay(EndPlayReason);


	if (m_pMainHUD != nullptr)
	{
		m_pMainHUD->RemoveFromViewport();
		m_pMainHUD = nullptr;
	}
}

void AHUD_GameMain::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void  AHUD_GameMain::AddOSIEnemy(class AGameCharacter* pEnemy)
{
	if (m_pOSIMng == nullptr) return;

	//m_pOSIMng->AddPin(pEnemy);
}