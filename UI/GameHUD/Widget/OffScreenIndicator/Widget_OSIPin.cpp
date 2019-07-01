// Fill out your copyright notice in the Description page of Project Settings.

#include "Widget_OSIPin.h"
#include "Components/Image.h"
#include "Actor/Characters/GameCharacter.h"

void UWidget_OSIPin::NativeConstruct()
{
	Super::NativeConstruct();

	m_pIcon = Cast<UImage>(GetWidgetFromName(TEXT("Icon")));
	if (m_pIcon == nullptr)
	{
		ULOG(TEXT("Error"));
	}

	m_pArrow = Cast<UImage>(GetWidgetFromName(TEXT("Arrow")));
	if (m_pArrow == nullptr)
	{
		ULOG(TEXT("Error"));
	}
}

void UWidget_OSIPin::SetChangeImage(int32 nIconState)
{
	if (m_pIconList.Num() <= 0 || m_pArrowList.Num() <= 0) return;
	if (nIconState > m_pIconList.Num()) return;

	m_pIcon->SetBrushFromTexture(m_pIconList[nIconState]);
	m_pArrow->SetBrushFromTexture(m_pArrowList[nIconState]);
}

void UWidget_OSIPin::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	Super::NativeTick(MyGeometry, InDeltaTime);
	
}

void UWidget_OSIPin::SetShow(bool bShow)
{
	if (bShow == true)
	{
		SetVisibility(ESlateVisibility::Visible);
	}
	else
	{
		SetVisibility(ESlateVisibility::Hidden);
	}
}