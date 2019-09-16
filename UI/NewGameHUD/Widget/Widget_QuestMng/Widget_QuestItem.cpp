// Fill out your copyright notice in the Description page of Project Settings.

#include "Widget_QuestItem.h"
#include "Components/Image.h"
#include "Components/TextBlock.h"

void UWidget_QuestItem::NativeConstruct()
{
	Super::NativeConstruct();

	m_pImg_Icon = Cast<UImage>(GetWidgetFromName(TEXT("IconImg")));
	if (m_pImg_Icon == nullptr)
	{
		return;
	}

	m_pTxt_Quest = Cast<UTextBlock>(GetWidgetFromName(TEXT("TextInfo")));
	if (m_pTxt_Quest == nullptr)
	{
		return;
	}

	m_bDone = false;
}

void UWidget_QuestItem::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	Super::NativeTick(MyGeometry, InDeltaTime);

}

void UWidget_QuestItem::NativeDestruct()
{
	Super::NativeDestruct();
	
	if (m_pTxt_Quest != nullptr)
	{
		if (m_pTxt_Quest->IsValidLowLevel())
		{
			m_pTxt_Quest = nullptr;
		}
	}
	if (m_pImg_Icon != nullptr)
	{
		if (m_pImg_Icon->IsValidLowLevel())
		{
			m_pImg_Icon = nullptr;
		}
	}
	
}

void UWidget_QuestItem::SetImage_Icon(class UTexture2D* pTexture)
{
	if (m_pImg_Icon != nullptr)
	{
		m_pImg_Icon->SetBrushFromTexture(pTexture, true);
	}
}

void UWidget_QuestItem::SetText_Quest(const FText sText)
{
	if (m_pTxt_Quest != nullptr)
	{
		m_pTxt_Quest->SetText(sText);
	}
}

void UWidget_QuestItem::SetTag(FString sTagName)
{
	m_sMyTag = sTagName;
}

FString UWidget_QuestItem::GetTag()
{
	return m_sMyTag;
}
