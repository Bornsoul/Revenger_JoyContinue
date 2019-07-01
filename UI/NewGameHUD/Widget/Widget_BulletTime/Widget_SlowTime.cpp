// Fill out your copyright notice in the Description page of Project Settings.

#include "Widget_SlowTime.h"
#include "UI/Core/WidgetAni_Mng.h"
#include "Components/TextBlock.h"
#include "Kismet/KismetMathLibrary.h"

void UWidget_SlowTime::NativePreConstruct()
{
	Super::NativePreConstruct();

}

void UWidget_SlowTime::NativeConstruct()
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

	m_pTimerTxt = Cast<UTextBlock>(GetWidgetFromName(TEXT("Timer")));
	if (m_pTimerTxt == nullptr)
	{
		ULOG(TEXT("TextBlock is nullptr"));
		return;
	}

}

void UWidget_SlowTime::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	Super::NativeTick(MyGeometry, InDeltaTime);

}

void UWidget_SlowTime::SetActive(bool bActive)
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

void UWidget_SlowTime::SetPlayAnimation(FString sAniName, bool bRevers)
{
	if (m_pWidgetAni == nullptr) return;
	m_bRevers = bRevers;
	m_pWidgetAni->SetPlayAnimation(sAniName, m_bRevers == true ? EUMGSequencePlayMode::Reverse : EUMGSequencePlayMode::Forward);
}

void UWidget_SlowTime::SetTimerValue(float fTimer)
{
	if (m_pTimerTxt == nullptr) return;

	FString sStr = FString::Printf(TEXT("%d%%"), (int)fTimer);
	m_pTimerTxt->SetText(FText::FromString(*sStr));
}
