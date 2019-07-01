// Fill out your copyright notice in the Description page of Project Settings.

#include "Widget_Result_ButtonItem.h"
#include "UI/Core/WidgetAni_Mng.h"

#include "Components/Button.h"
#include "Components/TextBlock.h"
#include "Kismet/KismetMathLibrary.h"

void UWidget_Result_ButtonItem::NativePreConstruct()
{
	Super::NativePreConstruct();

}

void UWidget_Result_ButtonItem::NativeConstruct()
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

	m_pButton = Cast<UButton>(GetWidgetFromName(TEXT("Btn")));
	if (m_pButton == nullptr)
	{
		ULOG(TEXT("Button is nullptr"));
		return;
	}

	m_pBtnTitle = Cast<UTextBlock>(GetWidgetFromName(TEXT("Txt")));
	if (m_pBtnTitle == nullptr)
	{
		ULOG(TEXT("TextBlock is nullptr"));
		return;
	}

}

void UWidget_Result_ButtonItem::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	Super::NativeTick(MyGeometry, InDeltaTime);

	if (m_bPress == false)
	{
		if (m_pButton->IsPressed())
		{
			ULOG(TEXT("Button Press : %s"), *GetName());
			m_bPress = true;
		}
	}

}

void UWidget_Result_ButtonItem::SetPlayAnimation(FString sAniName, bool bRevers)
{
	if (m_pWidgetAni == nullptr) return;
	m_bRevers = bRevers;
	m_pWidgetAni->SetPlayAnimation(sAniName, m_bRevers == true ? EUMGSequencePlayMode::Reverse : EUMGSequencePlayMode::Forward);
}

void UWidget_Result_ButtonItem::SetTitle(FString sText)
{
	if (m_pBtnTitle == nullptr) return;
	m_pBtnTitle->SetText(FText::FromString(sText));
}

void UWidget_Result_ButtonItem::SetActive(bool bActive)
{
	m_bActive = bActive;

	if (m_bActive == true)
	{
		GetRootWidget()->SetVisibility(ESlateVisibility::Visible);
	}
	else
	{
		GetRootWidget()->SetVisibility(ESlateVisibility::Hidden);
	}
}

bool UWidget_Result_ButtonItem::GetButtonDown()
{
	return m_bPress;
}
