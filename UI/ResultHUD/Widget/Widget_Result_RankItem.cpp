// Fill out your copyright notice in the Description page of Project Settings.

#include "Widget_Result_RankItem.h"
#include "UI/Core/WidgetAni_Mng.h"
#include "Kismet/KismetMathLibrary.h"

void UWidget_Result_RankItem::NativePreConstruct()
{
	Super::NativePreConstruct();

}

void UWidget_Result_RankItem::NativeConstruct()
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

}

void UWidget_Result_RankItem::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	Super::NativeTick(MyGeometry, InDeltaTime);

}

void UWidget_Result_RankItem::SetPlayAnimation(FString sAniName, bool bRevers)
{
	if (m_pWidgetAni == nullptr) return;
	m_bRevers = bRevers;
	m_pWidgetAni->SetPlayAnimation(sAniName, m_bRevers == true ? EUMGSequencePlayMode::Reverse : EUMGSequencePlayMode::Forward);
}

void UWidget_Result_RankItem::SetActive(bool bActive)
{
	//if (m_bActive == bActive) return;
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