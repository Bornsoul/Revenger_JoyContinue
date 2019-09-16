// Fill out your copyright notice in the Description page of Project Settings.

#include "Widget_TutoSayHUD.h"
#include "Components/TextBlock.h"
#include "Components/Image.h"
#include "Kismet/GameplayStatics.h"

void UWidget_TutoSayHUD::NativeConstruct()
{
	Super::NativeConstruct();

	m_pPlayerController = UGameplayStatics::GetPlayerController(GetWorld(), 0);
	if (m_pPlayerController == nullptr)
	{
		ULOG(TEXT("PlayerCon is nullptr"));
		return;
	}

	m_pTxt_Tuto = Cast<UTextBlock>(GetWidgetFromName(TEXT("Label")));
	if (m_pTxt_Tuto == nullptr)
	{
		ULOG(TEXT("Tuto is nullptr"));
		return;
	}

	m_pTxt_Count = Cast<UTextBlock>(GetWidgetFromName(TEXT("CntLabel")));
	if (m_pTxt_Count == nullptr)
	{
		ULOG(TEXT("Tuto is nullptr"));
		return;
	}

	m_pTimeGage = Cast<UImage>(GetWidgetFromName(TEXT("Front")));
	if (m_pTimeGage == nullptr)
	{
		ULOG(TEXT("TimeGage"));
		return;
	}
	m_pTimeGage->SetRenderScale(FVector2D(0.0f, 1.0f));
	m_bSkip = false;
}

void UWidget_TutoSayHUD::NativeDestruct()
{
	Super::NativeDestruct();

	m_pPlayerController->GetWorldTimerManager().ClearAllTimersForObject(this);

	if (m_pTxt_Tuto != nullptr)
	{
		if (m_pTxt_Tuto->IsValidLowLevel())
		{
			m_pTxt_Tuto = nullptr;
		}
	}

	if (m_pTimeGage != nullptr)
	{
		if (m_pTimeGage->IsValidLowLevel())
		{
			m_pTimeGage = nullptr;
		}
	}

	if (m_pPlayerController != nullptr)
	{
		if (m_pPlayerController->IsValidLowLevel())
		{
			m_pPlayerController = nullptr;
		}
	}
	
	m_stTutoSayList.m_sSayingList.Empty();
	m_stTutoSayList.m_fSayDelay.Empty();	
}

void UWidget_TutoSayHUD::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	Super::NativeTick(MyGeometry, InDeltaTime);

	if (UGameplayStatics::IsGamePaused(GetWorld()) == true) return;

	if (m_bGageState)
	{
		Tick_TutorialGage(InDeltaTime);
	}
}

void UWidget_TutoSayHUD::SetInit(const FTutorialSay stSayList)
{
	m_stTutoSayList = stSayList;
	m_nListCount = 0;
	m_nTutoSayLen = 0;
	m_fGageScale = 0.0f;
}

void UWidget_TutoSayHUD::Play_TutorialText()
{
	if (m_nListCount >= m_stTutoSayList.m_sSayingList.Num())
	{
		SetPlayAnimation("End");		
		return;
	}
	if (m_stTutoSayList.m_sSayingList.Num() <= 0)
	{
		ULOG(TEXT("Say Value is Nullptr"));
		return;
	}
	if (m_stTutoSayList.m_fSayDelay.Num() <= 0)
	{
		ULOG(TEXT("Delay Value is nullptr"));
		return;
	}

	if (m_pTxt_Tuto != nullptr)
	{
		m_pTxt_Tuto->SetText(FText::FromString(TEXT("")));
		m_nTutoSayLen = 0;
		if (m_pPlayerController != nullptr)
		{
			m_pPlayerController->GetWorldTimerManager().SetTimer(m_pTutoSayTimer, this, &UWidget_TutoSayHUD::Cor_TutoSay, m_fTutorialSay_Speed, true);
		}
	}	
	SetSayCountText(m_nListCount);
	SetGageTime(m_stTutoSayList.m_fSayDelay[m_nListCount]);
	SetPlayAnimation("TextStart");	
}

void UWidget_TutoSayHUD::Stop_TutorialText()
{
	m_bSkip = true;

	//SetSayCountText(m_nListCount);
	//SetGageTime(m_stTutoSayList.m_fSayDelay[m_nListCount]);
	//SetPlayAnimation("End");
}

void UWidget_TutoSayHUD::SetGageTime(float fGage)
{
	m_pTimeGage->SetRenderScale(FVector2D(0.0f, 1.0f));
	m_fGageScale = fGage;
	m_fGageTime = 0.0f;
}

void UWidget_TutoSayHUD::SetSayCountText(int32 nCount)
{
	if (m_stTutoSayList.m_fSayDelay.Num() <= 0)
	{
		return;
	}
	m_pTxt_Count->SetText(FText::FromString(TEXT("")));
	FString sStr = FString::Printf(TEXT("%d / %d"), (nCount+1), m_stTutoSayList.m_fSayDelay.Num());
	m_pTxt_Count->SetText(FText::FromString(sStr));
}

void UWidget_TutoSayHUD::Tick_TutorialGage(float fDeltaTime)
{	
	if (m_bGageState == true)
	{
		m_fGageTime += fDeltaTime;
		float fGageScale = (m_fGageTime / m_fGageScale) * 1.0f;

		if (fGageScale >= 1.0f)
		{
			m_fGageTime = 0.0f;
			fGageScale = 1.0f;			
			if (m_bSkip == false)
			{
				m_nListCount += 1;
			}
			else
			{
				m_nListCount = m_stTutoSayList.m_sSayingList.Num();
			}

			SetPlayAnimation("TextEnd");			
			m_bGageState = false;
		}

		m_pTimeGage->SetRenderScale(FVector2D(fGageScale, 1.0f));
	}
}

void UWidget_TutoSayHUD::Cor_TutoSay()
{
	if (m_pTxt_Tuto == nullptr)
	{
		ULOG(TEXT("Text is nullptr"));
		return;
	}

	FString sSayStr = m_stTutoSayList.m_sSayingList[m_nListCount].ToString();
	if (m_nTutoSayLen >= sSayStr.Len())
	{
		m_nTutoSayLen = sSayStr.Len();
		
		if (m_pPlayerController != nullptr)
		{
			m_pPlayerController->GetWorldTimerManager().ClearTimer(m_pTutoSayTimer);
		}
		return;
	}

	m_nTutoSayLen++;

	m_pTxt_Tuto->SetText(FText::FromString(sSayStr.Left(m_nTutoSayLen)));
}
