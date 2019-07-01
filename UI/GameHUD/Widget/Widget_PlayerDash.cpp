// Fill out your copyright notice in the Description page of Project Settings.

#include "Widget_PlayerDash.h"
#include "../../Core/WidgetAni_Mng.h"
#include "Runtime/UMG/Public/Animation/WidgetAnimation.h"

#include "Styling/SlateBrush.h"
#include "Materials/MaterialInstanceDynamic.h"
#include "Materials/MaterialInterface.h"
#include "Kismet/KismetMathLibrary.h"

void UWidget_PlayerDash::NativeConstruct()
{
	Super::NativeConstruct();

	m_pGage = Cast<UProgressBar>(GetWidgetFromName(TEXT("Gage")));
	if (m_pGage == nullptr)
	{
		ULOG(TEXT("Error Gage"));
	}

	m_pGageText = Cast<UTextBlock>(GetWidgetFromName(TEXT("GageTxt")));
	if (m_pGageText == nullptr)
	{
		ULOG(TEXT("Error GageText"));
	}
	
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

	
	m_bGage = true;
}

void UWidget_PlayerDash::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	Super::NativeTick(MyGeometry, InDeltaTime);

	if (m_bGage)
	{
		float fVal = FMath::FInterpTo(m_pGage->Percent, 1.0f, InDeltaTime, 8.0f);
		SetValue(fVal);
	}
	else
	{
		float fVal = FMath::FInterpTo(m_pGage->Percent, 0.0f, InDeltaTime, 8.0f);
		SetValue(fVal);
	}
}

void UWidget_PlayerDash::SetValue(float fValue)
{
	m_pGage->SetPercent(fValue);
}

void UWidget_PlayerDash::SetShow(bool bShow)
{		
	if (bShow)
	{
		m_pGageText->SetText(FText::FromString("F"));
		m_pWidgetAni->SetPlayAnimation("GageText");
		m_pWidgetAni->SetPlayAnimation("GageAdd");
	}
	else
	{
		m_pGageText->SetText(FText::FromString("E"));
		m_pWidgetAni->SetPlayAnimation("GageText");
		m_pWidgetAni->SetPlayAnimation("GageRemove");
	}
	m_bGage = bShow;
}