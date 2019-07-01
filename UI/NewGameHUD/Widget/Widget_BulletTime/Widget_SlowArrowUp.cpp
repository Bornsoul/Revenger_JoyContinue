// Fill out your copyright notice in the Description page of Project Settings.

#include "Widget_SlowArrowUp.h"
#include "UI/Core/WidgetAni_Mng.h"
#include "Components/Image.h"
#include "Kismet/KismetMathLibrary.h"

void UWidget_SlowArrowUp::NativePreConstruct()
{
	Super::NativePreConstruct();

}

void UWidget_SlowArrowUp::NativeConstruct()
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

	m_pFullImg = Cast<UImage>(GetWidgetFromName(TEXT("Full")));
	if (m_pFullImg == nullptr)
	{
		ULOG(TEXT("Image is nullptr"));
		return;
	}

}

void UWidget_SlowArrowUp::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	Super::NativeTick(MyGeometry, InDeltaTime);

}

void UWidget_SlowArrowUp::SetFullArrowActive(bool bActive)
{
	if (m_pFullImg == nullptr) return;

	if (bActive)
		m_pFullImg->SetVisibility(ESlateVisibility::Visible);
	else
		m_pFullImg->SetVisibility(ESlateVisibility::Hidden);
}

void UWidget_SlowArrowUp::SetActive(bool bActive)
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

void UWidget_SlowArrowUp::SetPlayAnimation(FString sAniName, bool bRevers)
{
	if (m_pWidgetAni == nullptr) return;
	m_bRevers = bRevers;
	m_pWidgetAni->SetPlayAnimation(sAniName, m_bRevers == true ? EUMGSequencePlayMode::Reverse : EUMGSequencePlayMode::Forward);
}