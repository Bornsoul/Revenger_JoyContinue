// Fill out your copyright notice in the Description page of Project Settings.

#include "Widget_TopTitleItem.h"
#include "UI/Core/WidgetAni_Mng.h"
#include "Kismet/KismetMathLibrary.h"

void UWidget_TopTitleItem::NativePreConstruct()
{
	Super::NativePreConstruct();

}

void UWidget_TopTitleItem::NativeConstruct()
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
	m_bDeActiveTime = false;
	SetActive(false);
}

void UWidget_TopTitleItem::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	Super::NativeTick(MyGeometry, InDeltaTime);

	if (m_bActiveTime)
	{
		m_fDeActiveTime_Cur += InDeltaTime;
		if (m_fDeActiveTime_Cur >= m_fDeActiveTime_End)
		{
			m_fDeActiveTime_Cur = 0.0f;
			DeActive_Title();
			return;
		}
	}

	if (m_bDeActiveTime)
	{
		m_fDeActiveTime_Cur += InDeltaTime;
		if (m_fDeActiveTime_Cur >= m_fDeActiveTime_End)
		{
			m_fDeActiveTime_Cur = 0.0f;
			SetPlayAnimation("End");
			m_bDeActiveTime = false;
			return;
		}
	}
}

void UWidget_TopTitleItem::SetActive(bool bActive)
{
	m_bActive = bActive;

	if (m_bActive)
	{
		GetRootWidget()->SetVisibility(ESlateVisibility::Visible);
		//SetPlayAnimation("Start");
	}
	else
	{
		GetRootWidget()->SetVisibility(ESlateVisibility::Hidden);
	}
}

void UWidget_TopTitleItem::SetPlayAnimation(FString sAniName, bool bRevers)
{
	if (m_pWidgetAni == nullptr) return;
	m_bRevers = bRevers;
	m_pWidgetAni->SetPlayAnimation(sAniName, m_bRevers == true ? EUMGSequencePlayMode::Reverse : EUMGSequencePlayMode::Forward);
}

void UWidget_TopTitleItem::Active_Title()
{
	//SetActive(true);
	SetPlayAnimation("Start");
	m_bActiveTime = true;
	m_fDeActiveTime_Cur = 0.0f;

}

void UWidget_TopTitleItem::DeActive_Title()
{
	m_bActiveTime = false;
	m_bDeActiveTime = true;
	m_fDeActiveTime_Cur = 0.0f;
}