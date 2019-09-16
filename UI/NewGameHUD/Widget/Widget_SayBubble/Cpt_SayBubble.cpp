// Fill out your copyright notice in the Description page of Project Settings.

#include "Cpt_SayBubble.h"
#include "../Widget_SayDialogItem.h"

UCpt_SayBubble::UCpt_SayBubble()
{
	PrimaryComponentTick.bCanEverTick = true;

	static ConstructorHelpers::FObjectFinder<UClass> Const_Widget(TEXT("/Game/1_Project_Main/1_Blueprints/UI/NEW/Widgets/BP_Widget_SayDialog.BP_Widget_SayDialog_C"));
	if (Const_Widget.Succeeded())
	{
		m_pInst_SayDialog = Const_Widget.Object;
	}
}

void UCpt_SayBubble::BeginPlay()
{
	Super::BeginPlay();

	APlayerController* pPlayerController = UGameplayStatics::GetPlayerController(GetWorld(), 0);
	m_pSayDialog = CreateWidget<UWidget_SayDialogItem>(pPlayerController, m_pInst_SayDialog);
	if (m_pSayDialog != nullptr)
	{
		m_pSayDialog->AddToViewport();
		m_pSayDialog->SetTargetActor(GetOwner());
		m_pSayDialog->SetActive(false);
	}

	if (m_bAutoStart)
		PlaySaying();
	else
		StopSaying();

	m_bActive = true;
}

void UCpt_SayBubble::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	Super::EndPlay(EndPlayReason);

	if (m_pSayDialog != nullptr)
	{
		if (m_pSayDialog->IsValidLowLevel())
		{
			m_pSayDialog = nullptr;
		}
	}
}

void UCpt_SayBubble::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	
	if (GetOwner()->ActorHasTag(TEXT("EnemyDie")) == true)
	{
		ULOG(TEXT("EnemyDie"));
		if (m_pSayDialog != nullptr)
		{			
			m_pSayDialog->RemoveFromParent();
		}	
		DestroyComponent();
		m_bActive = false;
		return;
	}

	if (m_bActive == false)
	{
		return;
	}

	if (m_stSayBubble.Num() <= 0)
	{
		return;
	}

	if (m_pSayDialog != nullptr)
	{
		AActor* pActor = m_pSayDialog->GetTargetActor();
		if (pActor != nullptr)
		{
			FVector vPos = pActor->GetActorLocation();

			APlayerController* pPlayerController = UGameplayStatics::GetPlayerController(GetWorld(), 0);
			
			FVector2D vScreenPos;
			pPlayerController->ProjectWorldLocationToScreen(vPos, vScreenPos);

			int32 nScreen_Width = 0.0f;
			int32 nScreen_Height = 0.0f;

			pPlayerController->GetViewportSize(nScreen_Width, nScreen_Height);

			int32 nScreenX = (int32)vScreenPos.X;
			int32 nScreenY = (int32)vScreenPos.Y;

			m_pSayDialog->SetPositionInViewport(FVector2D(nScreenX - m_vBubbleLocation.X, nScreenY - m_vBubbleLocation.Y));
		}
	}

	switch (m_eState)
	{
	case eSayState::E_NONE:
		break;
	case eSayState::E_SHOW:
		m_fTurnDelay_Time += DeltaTime;
		if (m_fTurnDelay_Time >= m_fTurnDelay_Time)
		{
			Show_SayDialog();
			m_eState = eSayState::E_HIDE;
			m_fTurnDelay_Time = 0.0f;
		}
		break;
	case eSayState::E_HIDE:
		if (m_pSayDialog->GetStartAniEnd() == false)
		{
			return;
		}
		else
		{
			m_fTurnDelay_Time += DeltaTime;
			if (m_fTurnDelay_Time >= m_stSayBubble[m_nSayIndex].m_fSayDestroyDelay)
			{
				Hide_SayDialog();
				m_eState = eSayState::E_WAIT;				
				m_fTurnDelay_Time = 0.0f;
			}
		}
		break;
	case eSayState::E_WAIT:
		m_fTurnDelay_Time += DeltaTime; 
		if (m_fTurnDelay_Time >= 2.0f)
		{
			if (m_bStopPlaying)
			{
				m_eState = eSayState::E_NONE;
			}
			else
			{
				m_eState = eSayState::E_SHOW;
			}
			
			m_fTurnDelay_Time = 0.0f;
		}
		break;
	}

}

void UCpt_SayBubble::SetHidden(bool bHide)
{
	if (bHide)
	{		
		m_pSayDialog->SetVisibility(ESlateVisibility::Hidden);
	}
	else
	{
		m_pSayDialog->SetVisibility(ESlateVisibility::SelfHitTestInvisible);
	}
}

void UCpt_SayBubble::PlaySaying()
{
	m_bStopPlaying = false;
	m_eState = eSayState::E_SHOW;
}

void UCpt_SayBubble::StopSaying()
{
	m_bStopPlaying = true;
	m_eState = eSayState::E_HIDE;
}

bool UCpt_SayBubble::GetHideAniEnd()
{
	if (m_pSayDialog == nullptr) return false;

	return m_pSayDialog->GetHideAniEnd();
}

void UCpt_SayBubble::SetTarget(class AActor* pTarget)
{
	if (m_pSayDialog != nullptr)
	{
		m_pSayDialog->SetTargetActor(pTarget);
	}
}

void UCpt_SayBubble::SetAutoPlay(bool bPlay)
{
	m_bAutoStart = bPlay;

	if (m_bAutoStart)
		PlaySaying();
	else
		StopSaying();
}

void UCpt_SayBubble::Show_SayDialog()
{
	if (m_pSayDialog == nullptr)
	{
		ULOG(TEXT("SayDialog is nullptr"));
		return;
	}

	m_pSayDialog->SetActive(true);
	m_pSayDialog->SetPlayAnimation("Start");

	FText sSayText;

	if (m_bSayingIsRandom)
	{
		m_nSayIndex = FMath::RandRange(0, m_stSayBubble.Num()-1);
		sSayText = m_stSayBubble[m_nSayIndex].m_sSaying;
	}
	else
	{
		sSayText = m_stSayBubble[m_nSayIndex].m_sSaying; 		
	}
	
	m_pSayDialog->SetSayText(sSayText);
}

void UCpt_SayBubble::Hide_SayDialog()
{
	if (m_pSayDialog == nullptr)
	{
		ULOG(TEXT("SayDialog is nullptr"));
		return;
	}
	m_pSayDialog->SetPlayAnimation("End");

	if (m_nSayIndex >= m_stSayBubble.Num()-1)
	{		
		m_nSayIndex = 0;
		return;
	}

	m_nSayIndex++;
}

