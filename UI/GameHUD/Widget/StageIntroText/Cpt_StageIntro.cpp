// Fill out your copyright notice in the Description page of Project Settings.

#include "Cpt_StageIntro.h"
#include "UI/GameHUD/Widget/StageIntroText/Widget_StageIntro.h"
#include "Kismet/GameplayStatics.h"

UCpt_StageIntro::UCpt_StageIntro()
{
	PrimaryComponentTick.bCanEverTick = true;

	static ConstructorHelpers::FObjectFinder<UClass> Const_Widget(TEXT("/Game/1_Project_Main/1_Blueprints/UI/GameHUD/StageIntro/BP_Widget_StageIntro.BP_Widget_StageIntro_C"));
	if (Const_Widget.Succeeded())
	{
		m_pInst_Widget = Const_Widget.Object;
	}
}


void UCpt_StageIntro::BeginPlay()
{
	Super::BeginPlay();

}

void UCpt_StageIntro::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	Super::EndPlay(EndPlayReason);

	if (m_pWidget != nullptr)
	{
		m_pWidget->ConditionalBeginDestroy();
		m_pWidget = nullptr;
	}
	m_bPlaying = false;

}


void UCpt_StageIntro::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if (m_bPlaying == true)
	{
		if (m_bStartDelay == false)
		{
			m_fStartDelay_Curr += DeltaTime;
			if (m_fStartDelay_Curr > m_fStartDelay_End)
			{
				m_fStartDelay_Curr = 0.0f;
				m_pWidget->SetAnimation("Start");
				m_bStartDelay = true;				
			}
		}
		else
		{
			m_fEndTime_Curr += DeltaTime;
			if (m_fEndTime_Curr > m_fEndTime_End)
			{
				m_fEndTime_Curr = 0.0f;
				SetEndPlay();
			}
		}
	}
}

void UCpt_StageIntro::SetInit()
{
	if (m_pInst_Widget == nullptr) return;
	
	APlayerController* pPlayerController = UGameplayStatics::GetPlayerController(GetWorld(), 0);
	UWidget_StageIntro* pObj = CreateWidget<UWidget_StageIntro>(pPlayerController, m_pInst_Widget);
	if (pObj != nullptr)
	{
		pObj->AddToViewport();
		pObj->SetActive(false);
		m_pWidget = pObj;
		//ULOG(TEXT("Intro Init Widget"));
		//SetPosition(vScreenPos);
	}

	m_bPlaying = false;
	//ULOG(TEXT("Intro Init"));
}

void UCpt_StageIntro::SetPlay(float fStartDelay, float fEndTime)
{
	if (m_pWidget == nullptr)
	{
		ULOG(TEXT("Widget is nullptr"));
		return;
	}
	if (m_bPlaying == true)
	{
		return;
	}


	m_fStartDelay_Curr = 0.0f;
	m_fStartDelay_End = fStartDelay;

	m_fEndTime_Curr = 0.0f;
	m_fEndTime_End = fEndTime;

	m_bPlaying = true;
	m_bStartDelay = false;

	//ULOG(TEXT("Intro Playing"));
}

void UCpt_StageIntro::SetEndPlay()
{
	if (m_pWidget == nullptr) return;

	m_pWidget->SetAnimation("Start", true);
	m_bPlaying = false;
}

void UCpt_StageIntro::SetPosition(FVector vPos)
{
	APlayerController* pPlayerController = UGameplayStatics::GetPlayerController(GetWorld(), 0);

	FVector2D vScreenPos;
	pPlayerController->ProjectWorldLocationToScreen(vPos, vScreenPos);

	int32 nScreen_Width = 0.0f;
	int32 nScreen_Height = 0.0f;

	pPlayerController->GetViewportSize(nScreen_Width, nScreen_Height);

	int32 nScreenX = (int32)vScreenPos.X;
	int32 nScreenY = (int32)vScreenPos.Y;

	m_pWidget->SetPositionInViewport(FVector2D(nScreenX, nScreenY));
}