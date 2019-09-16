// Fill out your copyright notice in the Description page of Project Settings.

#include "Cpt_TutorialSay.h"
#include "Widget_TutoSayHUD.h"
UCpt_TutorialSay::UCpt_TutorialSay()
{
	PrimaryComponentTick.bCanEverTick = true;

	static ConstructorHelpers::FObjectFinder<UClass> Const_Tuto(TEXT("/Game/1_Project_Main/1_Blueprints/UI/NEW/Tutorial_Widget/Widget_TutoSay/BP_Widget_TutoSayHUD.BP_Widget_TutoSayHUD_C"));
	if (Const_Tuto.Succeeded())
	{
		m_pInst_Hud = Const_Tuto.Object;
	}

}

void UCpt_TutorialSay::BeginPlay()
{
	Super::BeginPlay();

	APlayerController* pController = UGameplayStatics::GetPlayerController(GetWorld(), 0);
	m_pTutoSayHud = CreateWidget<UWidget_TutoSayHUD>(pController, m_pInst_Hud);
	if (m_pTutoSayHud != nullptr)
	{
		m_pTutoSayHud->AddToViewport();
		m_pTutoSayHud->SetActive(false);
	}

	m_bPlaySay = false;
}

void UCpt_TutorialSay::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	if (m_pTutoSayHud != nullptr)
	{
		if (m_pTutoSayHud->IsValidLowLevel())
		{
			m_pTutoSayHud->RemoveFromParent();
			m_pTutoSayHud = nullptr;
		}
	}	
}

void UCpt_TutorialSay::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if (m_bPlaySay)
	{
		if (m_pTutoSayHud != nullptr)
		{
			if (m_pTutoSayHud->GetSayAllEnd())
			{
				m_bPlaySay = false;
				m_pTutoSayHud->SetSayAllEnd(false);
				return;
			}
		}
	}
}

void UCpt_TutorialSay::Create_TutoSay(const FTutorialSay stSayDialog)
{
	if (m_bPlaySay == true)
	{
		ULOG(TEXT("Already Running Saying"));
		return;
	}

	if (m_pTutoSayHud == nullptr)
	{
		ULOG(TEXT("Tuto Hud is nullptr"));
		return;
	}

	if (stSayDialog.m_sSayingList.Num() != stSayDialog.m_fSayDelay.Num())
	{
		ULOG(TEXT("Struct Num is Not Valid"));
		return;
	}

	m_pTutoSayHud->SetInit(stSayDialog);

	m_pTutoSayHud->SetActive(true);
	m_pTutoSayHud->SetPlayAnimation("Start");	
	m_bPlaySay = true;
}

void UCpt_TutorialSay::Stop_TutoSay()
{
	if (m_bPlaySay == false)
	{
		ULOG(TEXT("Not Running Saying"));
		return;
	}
	if (m_pTutoSayHud == nullptr)
	{
		ULOG(TEXT("Tuto Hud is nullptr"));
		return;
	}
	   
	m_pTutoSayHud->Stop_TutorialText();
}

