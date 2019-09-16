// Fill out your copyright notice in the Description page of Project Settings.

#include "Widget_SayDialogItem.h"
#include "UI/Core/WidgetAni_Mng.h"
#include "Components/TextBlock.h"
#include "Kismet/KismetMathLibrary.h"

void UWidget_SayDialogItem::NativePreConstruct()
{
	Super::NativePreConstruct();

}

void UWidget_SayDialogItem::NativeConstruct()
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

	m_pSayText = Cast<UTextBlock>(GetWidgetFromName(TEXT("Say")));
	if (m_pSayText == nullptr)
	{
		ULOG(TEXT("Say Text is nullptr"));
		return;
	}

}

void UWidget_SayDialogItem::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	Super::NativeTick(MyGeometry, InDeltaTime);

}

void UWidget_SayDialogItem::NativeDestruct()
{
	Super::NativeDestruct();

	if (m_pWidgetAni != nullptr)
	{
		if (m_pWidgetAni->IsValidLowLevel())
		{
			m_pWidgetAni->Destroy();
			m_pWidgetAni = nullptr;
		}
	}

	if (m_pSayText != nullptr)
	{
		if (m_pSayText->IsValidLowLevel())
		{
			m_pSayText = nullptr;
		}
	}
}

void UWidget_SayDialogItem::SetSayText(FText sSaying)
{
	if (m_pSayText != nullptr)
	{
		m_pSayText->SetText(sSaying);
	}
}

void UWidget_SayDialogItem::SetActive(bool bActive)
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

void UWidget_SayDialogItem::SetPlayAnimation(FString sAniName, bool bRevers)
{
	if (m_pWidgetAni == nullptr) return;
	m_bRevers = bRevers;
	m_pWidgetAni->SetPlayAnimation(sAniName, m_bRevers == true ? EUMGSequencePlayMode::Reverse : EUMGSequencePlayMode::Forward);
}

