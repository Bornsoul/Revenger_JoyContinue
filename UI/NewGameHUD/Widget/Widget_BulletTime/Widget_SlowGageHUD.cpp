// Fill out your copyright notice in the Description page of Project Settings.

#include "Widget_SlowGageHUD.h"
#include "Widget_SlowArrowUp.h"
#include "Widget_SlowTime.h"

#include "UI/Core/WidgetAni_Mng.h"
#include "Kismet/KismetMathLibrary.h"

void UWidget_SlowGageHUD::NativePreConstruct()
{
	Super::NativePreConstruct();

}

void UWidget_SlowGageHUD::NativeConstruct()
{
	Super::NativeConstruct();

	m_pWidgetAni = NewObject<UWidgetAni_Mng>();
	if (m_pWidgetAni != nullptr)
	{
		m_pWidgetAni->Init(this);
	}
	else
	{
		ULOG(TEXT("WidgetAniMng is nullptr"));
		return;
	}

	m_pTimer = Cast<UWidget_SlowTime>(GetWidgetFromName("Timer"));
	if (m_pTimer == nullptr)
	{
		ULOG(TEXT("Timer is Nullptr"));
		return;
	}

	for (int i = 0; i < 10; i++)
	{
		FString sText = FString::Printf(TEXT("A%d"), i);
		m_pGageList.Add(Cast<UWidget_SlowArrowUp>(GetWidgetFromName(*sText)));
	}
	m_fCurrentGage = 100.0f;
	m_fGageValue = 100.0f;

	m_pTimer->SetTimerValue(m_fGageValue);
	m_eState = static_cast<int32>(E_State_SlowGageState::E_SLOW_NONE);
	//SetGagePercent(100.0f, true);


}

void UWidget_SlowGageHUD::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	Super::NativeTick(MyGeometry, InDeltaTime);

	//Tick_SlowGage(InDeltaTime);

}

void UWidget_SlowGageHUD::SetSlowEnter(float fGageSpeed)
{
	m_fLastValue = 0.0f;
	m_fCurrentGage = 100.0f;
	m_fGageValue = 100.0f;
	m_fGageSpeed = fGageSpeed;
	m_fDeActiveGageVal = m_fCurrentGage;
	m_bIsEmpty = false;

	m_pTimer->SetTimerValue(m_fGageValue);
	m_eState = static_cast<int32>(E_State_SlowGageState::E_SLOW_NONE);
}

void UWidget_SlowGageHUD::SetActive(bool bActive)
{
	m_bActive = bActive;

	if (m_bActive)
	{
		GetRootWidget()->SetVisibility(ESlateVisibility::Visible);
	}
	else
	{
		GetRootWidget()->SetVisibility(ESlateVisibility::Hidden);
	}
}

void UWidget_SlowGageHUD::Active_SlowGage()
{
	if (m_eState == static_cast<int32>(E_State_SlowGageState::E_SLOW_ACTIVE)) return;

	m_fRealTime = UGameplayStatics::GetRealTimeSeconds(GetWorld());
	m_eState = static_cast<int32>(E_State_SlowGageState::E_SLOW_ACTIVE);
}

void UWidget_SlowGageHUD::DeActive_SlowGage()
{
	if (m_eState == static_cast<int32>(E_State_SlowGageState::E_SLOW_DEACTIVE)) return;	
	m_fRealTime = UGameplayStatics::GetRealTimeSeconds(GetWorld());

	m_bIsEmpty = false;
	m_fDeActiveGageVal = m_fGageValue;
	m_eState = static_cast<int32>(E_State_SlowGageState::E_SLOW_DEACTIVE);
}

void UWidget_SlowGageHUD::SetPlayAnimation(FString sAniName, bool bRevers)
{
	if (m_pWidgetAni == nullptr) return;
	m_bRevers = bRevers;
	m_pWidgetAni->SetPlayAnimation(sAniName, m_bRevers == true ? EUMGSequencePlayMode::Reverse : EUMGSequencePlayMode::Forward);
}

void UWidget_SlowGageHUD::SetGagePercent(float fPer, bool bFull)
{
	if (m_pGageList.Num() <= 0)
	{
		ULOG(TEXT("GageList is nullptr"));
		return;
	}
	if (fPer < 0.0f) return;
	else if (fPer > 100.0f) return;

	float fResultPer = fPer / 1.0f * 0.1f;
	m_pTimer->SetTimerValue(FMath::FloorToInt(fPer));
	
	if (bFull)
	{
		if (FMath::FloorToInt(fResultPer) >= 9)
			fResultPer = 9;

		for (int32 i = 0; i < FMath::FloorToInt(fResultPer); i++)
		{
			m_pGageList[i]->SetFullArrowActive(true);
		}

		m_pGageList[FMath::FloorToInt(fResultPer)]->SetFullArrowActive(true);
	}
	else
	{
		if (FMath::FloorToInt(fResultPer) <= 0)
			fResultPer = 0;

		for (int32 i = FMath::FloorToInt(fResultPer); i < m_pGageList.Num(); i++)
		{
			m_pGageList[i]->SetFullArrowActive(false);
		}

		m_pGageList[FMath::FloorToInt(fResultPer)]->SetFullArrowActive(false);
	}
	m_fLastValue = FMath::FloorToInt(fResultPer);
	
}

void UWidget_SlowGageHUD::Tick_SlowGage(float fDeltaTime)
{

	switch (m_eState)
	{
		case static_cast<int32>(E_State_SlowGageState::E_SLOW_NONE) :
		{
			break;
		}
		case static_cast<int32>(E_State_SlowGageState::E_SLOW_ACTIVE) :
		{
			if (m_fGageValue <= 0.0f)
			{
				m_fGageValue = 0.0f;
				m_bIsEmpty = true;
				SetGagePercent(m_fGageValue, false);
				m_eState = static_cast<int32>(E_State_SlowGageState::E_SLOW_DEACTIVE);
				return;
			}
			
			m_fGageValue -= m_fGageSpeed * fDeltaTime;
			SetGagePercent(m_fGageValue, false);
			break;
		}
		case static_cast<int32>(E_State_SlowGageState::E_SLOW_DEACTIVE) :
		{
			if (m_fGageValue >= 100.0f)
			{
				m_fGageValue = 100.0f;
				SetGagePercent(m_fGageValue, true);
				m_eState = static_cast<int32>(E_State_SlowGageState::E_SLOW_NONE);
				return;
			}

			m_fGageValue += m_fGageSpeed * fDeltaTime;
			SetGagePercent(m_fGageValue, true);
			break;
		}
	}

}