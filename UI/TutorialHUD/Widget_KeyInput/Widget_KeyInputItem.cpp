// Fill out your copyright notice in the Description page of Project Settings.

#include "Widget_KeyInputItem.h"
#include "Components/TextBlock.h"
#include "Components/Image.h"

void UWidget_KeyInputItem::NativeConstruct()
{
	Super::NativeConstruct();

	m_pKeyText = Cast<UTextBlock>(GetWidgetFromName(TEXT("KeyText")));
	if (m_pKeyText == nullptr)
	{
		ULOG(TEXT("KeyText is nullptr"));
		return;
	}

	m_pKeyImg = Cast<UImage>(GetWidgetFromName(TEXT("KeyImg")));
	if (m_pKeyImg == nullptr)
	{
		ULOG(TEXT("KeyImg is nullptr"));
		return;
	}
}

void UWidget_KeyInputItem::NativeDestruct()
{
	Super::NativeDestruct();

	if (m_pKeyText != nullptr)
	{
		if (m_pKeyText->IsValidLowLevel())
		{
			m_pKeyText = nullptr;
		}
	}

	if (m_pKeyImg != nullptr)
	{
		if (m_pKeyImg->IsValidLowLevel())
		{
			m_pKeyImg = nullptr;
		}
	}
}

void UWidget_KeyInputItem::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	Super::NativeTick(MyGeometry, InDeltaTime);

}

void UWidget_KeyInputItem::SetKeyText(const FText sKeyText, UTexture2D* pKeyImg)
{
	if (m_pKeyText != nullptr)
	{
		m_sKeyState = sKeyText;		

		if (pKeyImg == nullptr)
		{
			m_pKeyImg->SetBrushFromTexture(nullptr);
			m_pKeyImg->SetVisibility(ESlateVisibility::Hidden);
			m_pKeyText->SetVisibility(ESlateVisibility::SelfHitTestInvisible);
			m_pKeyText->SetText(sKeyText);
		}
		else
		{
			m_pKeyText->SetVisibility(ESlateVisibility::Hidden);
			m_pKeyImg->SetVisibility(ESlateVisibility::SelfHitTestInvisible);
			m_pKeyImg->SetBrushFromTexture(pKeyImg, true);
		}
		
	}
}

FText UWidget_KeyInputItem::GetKeyText()
{
	if (m_pKeyText == nullptr)
	{
		ULOG(TEXT("KeyText is nullptr"));
		return FText::GetEmpty();
	}

	return m_sKeyState;
}
