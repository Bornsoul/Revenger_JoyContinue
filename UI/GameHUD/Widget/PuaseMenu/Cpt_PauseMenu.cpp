// Fill out your copyright notice in the Description page of Project Settings.

#include "Cpt_PauseMenu.h"
#include "Widget_PauseMenu.h"
#include "Libraries/Components/KeyStateMng/Cpt_KeyStateMng.h"
#include "Libraries/Components/KeyStateMng/Cpt_KeyStateMng.h"
#include "Kismet/GameplayStatics.h"

UCpt_PauseMenu::UCpt_PauseMenu()
{
	PrimaryComponentTick.bCanEverTick = true;

	static ConstructorHelpers::FObjectFinder<UClass> Const_Widget(TEXT("/Game/1_Project_Main/1_Blueprints/UI/GameHUD/PauseMenu/BP_Widget_Pause.BP_Widget_Pause_C"));
	if (Const_Widget.Succeeded())
	{
		m_pInst_Widget = Const_Widget.Object;
	}
	m_pKeyStateMng = CreateDefaultSubobject<UCpt_KeyStateMng>(TEXT("KeyStateMng"));
}

void UCpt_PauseMenu::BeginPlay()
{
	Super::BeginPlay();

	/*APlayerController* pPlayerController = UGameplayStatics::GetPlayerController(GetWorld(), 0);
	m_pWidget = CreateWidget<UWidget_PauseMenu>(pPlayerController, m_pInst_Widget);
	if (m_pWidget != nullptr)
	{
		m_pWidget->AddToViewport(10);
	}*/
	m_bActive = false;
}

void UCpt_PauseMenu::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	Super::EndPlay(EndPlayReason);

	if (m_pWidget != nullptr)
	{
		if (m_pWidget->IsValidLowLevel())
		{
			//m_pWidget->RemoveFromParent();
			//m_pWidget->ConditionalBeginDestroy();
			m_pWidget = nullptr;
		}
	}
	//ULOG(TEXT("PauseMenu is Destroy"));
}

void UCpt_PauseMenu::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	
	if (m_bActive == false) return;

	m_fKeyTime_Cur += DeltaTime;
	if (m_fKeyTime_Cur >= 1.0f)
	{
		if (m_pKeyStateMng->GetKeyIsJustPress(EKeys::Escape) == true ||
			m_pKeyStateMng->GetKeyIsJustPress(EKeys::Tab) == true && GetAniPlaying() == false)
		{
			if (m_pPlayer != nullptr)
			{
				m_pPlayer->SetPause(false);
				m_pPlayer->GetPauseMenu()->DeActive_PauseMenu();

			}
		}
	}
}

void UCpt_PauseMenu::Active_PauseMenu()
{
	//if (m_pWidget == nullptr) return;
	if (m_bActive == true) return;

	if (m_pWidget != nullptr)
	{
		m_pWidget->RemoveFromParent();
		m_pWidget = nullptr;
	}

	APlayerController* pPlayerController = UGameplayStatics::GetPlayerController(GetWorld(), 0);
	UWidget_PauseMenu* pWidget = CreateWidget<UWidget_PauseMenu>(pPlayerController, m_pInst_Widget);
	if (pWidget != nullptr)
	{
		pWidget->AddToViewport(10);
		pWidget->SetActive(true);
		pWidget->SetPlayAnimation("Start");

		m_pWidget = pWidget;
	}
	
	m_fKeyTime_Cur = 0.0f;
	m_bActive = true;
	UGameplayStatics::SetGamePaused(GetWorld(), true);

}

void UCpt_PauseMenu::DeActive_PauseMenu()
{
	//if (m_pWidget == nullptr) return;
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

