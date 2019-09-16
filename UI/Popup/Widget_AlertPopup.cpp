// Fill out your copyright notice in the Description page of Project Settings.

#include "Widget_AlertPopup.h"
#include "Components/TextBlock.h"

void UWidget_AlertPopup::NativeConstruct()
{
	Super::NativeConstruct();

	m_pText = Cast<UTextBlock>(GetWidgetFromName(TEXT("Alert")));
	if (m_pText == nullptr)
	{
		ULOG(TEXT("Text is nullptr"));
		return;
	}
}

void UWidget_AlertPopup::NativeDestruct()
{
	Super::NativeDestruct();

	if (m_pText != nullptr)
	{
		if (m_pText->IsValidLowLevel())
		{
			m_pText = nullptr;
		}
	}
}

void UWidget_AlertPopup::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	Super::NativeTick(MyGeometry, InDeltaTime);

	if (m_bDestroy == false)
	{
		if (m_fDestroyTime_End > 0.0f)
		{
			m_fDestroyTime_Cur += InDeltaTime;
			if (m_fDestroyTime_Cur >= m_fDestroyTime_End)
			{
				m_fDestroyTime_Cur = 0.0f;
				SetPlayAnimation("End");
				m_bDestroy = true;
				return;
			}
		}
	}
}

void UWidget_AlertPopup::SetText(FText sText)
{
	if (m_pText != nullptr) 
	{
		m_pText->SetText(sText);
	}
}

void UWidget_AlertPopup::SetTimer(float fDestroyTime)
{
	m_fDestroyTime_Cur = 0.0f;
	m_fDestroyTime_End = fDestroyTime;
}

void UWidget_AlertPopup::DestroyWidget()
{
	RemoveFromParent();
}
