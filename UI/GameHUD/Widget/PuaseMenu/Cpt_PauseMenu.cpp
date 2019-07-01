// Fill out your copyright notice in the Description page of Project Settings.

#include "Cpt_PauseMenu.h"
#include "Widget_PauseMenu.h"
#include "Libraries/Components/KeyStateMng/Cpt_KeyStateMng.h"

UCpt_PauseMenu::UCpt_PauseMenu()
{
	PrimaryComponentTick.bCanEverTick = true;

	static ConstructorHelpers::FObjectFinder<UClass> Const_Widget(TEXT("/Game/1_Project_Main/1_Blueprints/UI/GameHUD/PauseMenu/BP_Widget_Pause.BP_Widget_Pause_C"));
	if (Const_Widget.Succeeded())
	{
		m_pInst_Widget = Const_Widget.Object;
	}
}

void UCpt_PauseMenu::BeginPlay()
{
	Super::BeginPlay();

	APlayerController* pPlayerController = UGameplayStatics::GetPlayerController(GetWorld(), 0);
	m_pWidget = CreateWidget<UWidget_PauseMenu>(pPlayerController, m_pInst_Widget);
	if (m_pWidget != nullptr)
	{
		m_pWidget->AddToViewport();
	}
	m_bActive = false;
}

void UCpt_PauseMenu::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	Super::EndPlay(EndPlayReason);

	if (m_pWidget != nullptr)
	{
		if (m_pWidget->IsValidLowLevel())
		{
			m_pWidget->RemoveFromParent();
			m_pWidget->ConditionalBeginDestroy();
			m_pWidget = nullptr;
		}
	}
	ULOG(TEXT("PauseMenu is Destroy"));
}

void UCpt_PauseMenu::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	
}

void UCpt_PauseMenu::Active_PauseMenu()
{
	if (m_pWidget == nullptr) return;
	if (m_bActive == true) return;

	m_pWidget->SetActive(true);
	m_pWidget->SetPlayAnimation("Start");
	m_bActive = true;
}

void UCpt_PauseMenu::DeActive_PauseMenu()
{
	if (m_pWidget == nullptr) return;
	if (m_bActive == false) return;
	m_pWidget->SetButtonState(static_cast<int32>(E_Button_Pause::E_RESUME));

	m_pWidget->SetPlayAnimation("End", true);
	m_bActive = false;
}

int32 UCpt_PauseMenu::Menu_GetButton()
{
	if (m_pWidget == nullptr) return 0;
	
	return m_pWidget->GetCurrentState();
}

bool UCpt_PauseMenu::GetAniPlaying()
{
	if (m_pWidget == nullptr) return false;

	return m_pWidget->GetAniPlaying();
}

//bool UCpt_PauseMenu::Menu_GetStart()
//{
//	if (m_pWidget == nullptr) return false;
//
//	if (m_pWidget->GetCurrentState() == static_cast<int32>(E_Button_State::E_START))
//	{
//		return true;
//	}
//
//	return false;
//}

