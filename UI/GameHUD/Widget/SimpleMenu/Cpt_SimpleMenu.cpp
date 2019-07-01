// Fill out your copyright notice in the Description page of Project Settings.

#include "Cpt_SimpleMenu.h"
#include "Widget_SimpleMenu.h"
#include "Libraries/Components/KeyStateMng/Cpt_KeyStateMng.h"

UCpt_SimpleMenu::UCpt_SimpleMenu()
{
	PrimaryComponentTick.bCanEverTick = true;

	static ConstructorHelpers::FObjectFinder<UClass> Const_Widget(TEXT("/Game/1_Project_Main/1_Blueprints/UI/GameHUD/Simple_Menu/BP_Widget_SimpleMenu.BP_Widget_SimpleMenu_C"));
	if (Const_Widget.Succeeded())
	{
		m_pInst_Widget = Const_Widget.Object;
	}
}

void UCpt_SimpleMenu::BeginPlay()
{
	Super::BeginPlay();

	APlayerController* pPlayerController = UGameplayStatics::GetPlayerController(GetWorld(), 0);
	m_pWidget = CreateWidget<UWidget_SimpleMenu>(pPlayerController, m_pInst_Widget);
	if (m_pWidget != nullptr)
	{
		m_pWidget->AddToViewport();		
	}	
	m_bActive = false;
}

void UCpt_SimpleMenu::EndPlay(const EEndPlayReason::Type EndPlayReason)
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
	ULOG(TEXT("SimpleMenu is Destroy"));
}

void UCpt_SimpleMenu::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if (m_pWidget != nullptr)
	{
		if (m_pWidget->GetDestroy() == true)
		{
			DestroyComponent();
			return;
		}
	}
}

void UCpt_SimpleMenu::Active_SimpleMenu()
{
	if (m_pWidget == nullptr) return;
	
	m_pWidget->SetActive(true);
	m_pWidget->SetPlayAnimation("Start");
}

void UCpt_SimpleMenu::DeActive_SimpleMenu()
{
	if (m_pWidget == nullptr) return;

	//m_pWidget->SetPlayAnimation("End", true);
}

bool UCpt_SimpleMenu::Menu_GetStart()
{
	if (m_pWidget == nullptr) return false;

	if (m_pWidget->GetCurrentState() == static_cast<int32>(E_Button_State::E_START))
	{
		return true;
	}

	return false;
}