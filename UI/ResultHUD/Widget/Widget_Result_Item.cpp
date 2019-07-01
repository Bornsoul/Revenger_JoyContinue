// Fill out your copyright notice in the Description page of Project Settings.

#include "Widget_Result_Item.h"
#include "UI/Core/WidgetAni_Mng.h"

#include "Components/TextBlock.h"
#include "Kismet/KismetMathLibrary.h"

void UWidget_Result_Item::NativePreConstruct()
{
	Super::NativePreConstruct();


	if (m_pTitle == nullptr)
	{
		m_pTitle = Cast<UTextBlock>(GetWidgetFromName(TEXT("Title")));
	}
	else
	{
		m_pTitle->SetText(FText::FromString(m_sTitleText));
	}	
}

void UWidget_Result_Item::NativeConstruct()
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

	m_pResult = Cast<UTextBlock>(GetWidgetFromName(TEXT("Result")));
	if (m_pResult == nullptr)
	{
		ULOG(TEXT("TextBlock is nullptr"));
		return;
	}

	m_bAniDone = false;
}

void UWidget_Result_Item::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	Super::NativeTick(MyGeometry, InDeltaTime);

}

void UWidget_Result_Item::SetResultTitle(FString sText)
{
	if (m_pTitle == nullptr) return;
	m_pTitle->SetText(FText::FromString(sText));
}

void UWidget_Result_Item::SetResultText(FString sText)
{
	if (m_pResult == nullptr) return;
	FString sStr = FString::Printf(TEXT("%s 회"), *sText);
	m_pResult->SetText(FText::FromString(sStr));
}

void UWidget_Result_Item::SetPlayAnimation(FString sAniName, bool bRevers)
{
	if (m_pWidgetAni == nullptr) return;
	m_bRevers = bRevers;
	m_pWidgetAni->SetPlayAnimation(sAniName, m_bRevers == true ? EUMGSequencePlayMode::Reverse : EUMGSequencePlayMode::Forward);
}

void UWidget_Result_Item::SetActive(bool bActive)
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