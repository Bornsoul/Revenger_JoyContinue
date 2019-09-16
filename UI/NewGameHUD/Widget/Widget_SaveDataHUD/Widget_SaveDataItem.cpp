// Fill out your copyright notice in the Description page of Project Settings.

#include "Widget_SaveDataItem.h"
#include "UI/Core/WidgetAni_Mng.h"
#include "Components/Image.h"
#include "Kismet/KismetMathLibrary.h"

void UWidget_SaveDataItem::NativePreConstruct()
{
	Super::NativePreConstruct();

}

void UWidget_SaveDataItem::NativeConstruct()
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

	m_pImg_Slide = Cast<UImage>(GetWidgetFromName(TEXT("Img_Front")));
	if (m_pImg_Slide == nullptr)
	{
		ULOG(TEXT("Slide is nullptr"));
		return;
	}
	else
	{
		m_pImg_Slide->SetRenderScale(FVector2D(1.0f, 0.0f));
	}

	m_fSlideTime = 0.0f;
	m_fShowTime = 0.0f;
}

void UWidget_SaveDataItem::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	Super::NativeTick(MyGeometry, InDeltaTime);

	if (m_pImg_Slide != nullptr)
	{
		if (m_bSlideActive == true )
		{
			m_fSlideTime += InDeltaTime;

			float fSlideResult = (m_fSlideTime / m_fShowTime) * 1.0f;						
			if (fSlideResult >= 1.0f)
			{
				m_bSlideActive = false;
				fSlideResult = 1.0f;
			}
			m_pImg_Slide->SetRenderScale(FVector2D(1.0f, fSlideResult));
		}		
	}
}

void UWidget_SaveDataItem::NativeDestruct()
{
	Super::NativeDestruct();

	m_fSlideTime = 0.0f;
	m_fShowTime = 0.0f;
	m_bSlideActive = false;
	if (m_pWidgetAni != nullptr)
	{
		if (m_pWidgetAni->IsValidLowLevel())
		{
			m_pWidgetAni->Destroy();
			m_pWidgetAni = nullptr;
		}
	}

	if (m_pVerticalBox != nullptr)
	{
		m_pVerticalBox = nullptr;
	}

	if (m_pRoot != nullptr)
	{

		m_pRoot = nullptr;
	}
	GetOwningPlayer()->GetWorldTimerManager().ClearTimer(m_pTimer);
	ULOG(TEXT("SaveData Item Destroyed"));
}

void UWidget_SaveDataItem::SetDestroyTimer(float fTimer)
{	
	m_bSlideActive = true;
	m_fShowTime = fTimer;
	GetOwningPlayer()->GetWorldTimerManager().SetTimer(m_pTimer, this, &UWidget_SaveDataItem::Destroy, fTimer, false);	
}

void UWidget_SaveDataItem::SetVericalBox(class UVerticalBox* pVertBox, class UCpt_SaveDataAlert* pRoot)
{	
	m_pVerticalBox = pVertBox;
	m_pRoot = pRoot;
}

void UWidget_SaveDataItem::Destroy()
{
	SetPlayAnimation("End");
}

void UWidget_SaveDataItem::SetActive(bool bActive)
{
	m_bActive = bActive;

	if (m_bActive)
	{
		GetRootWidget()->SetVisibility(ESlateVisibility::Visible);
		SetPlayAnimation("Start");
	}
	else
	{
		if (m_pVerticalBox != nullptr)
		{
			m_pVerticalBox->ClearChildren();
		}
		if (m_pRoot != nullptr)
		{
			m_pRoot->SetDestroyed(false);
		}
		GetRootWidget()->RemoveFromParent();
		GetRootWidget()->SetVisibility(ESlateVisibility::Hidden);
	}
}

void UWidget_SaveDataItem::SetPlayAnimation(FString sAniName, bool bRevers)
{
	if (m_pWidgetAni == nullptr) return;
	m_bRevers = bRevers;
	m_pWidgetAni->SetPlayAnimation(sAniName, m_bRevers == true ? EUMGSequencePlayMode::Reverse : EUMGSequencePlayMode::Forward);
}

