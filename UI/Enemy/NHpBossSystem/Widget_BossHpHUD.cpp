// Fill out your copyright notice in the Description page of Project Settings.

#include "Widget_BossHpHUD.h"
#include "Widget_BossHpItem.h"
#include "Widget_BossShieldItem.h"

#include "Components/HorizontalBox.h"
#include "UI/Core/WidgetAni_Mng.h"
#include "Kismet/KismetMathLibrary.h"

void UWidget_BossHpHUD::NativeConstruct()
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

	m_pHeartBoxList = Cast<UHorizontalBox>(GetWidgetFromName(TEXT("HeartBox")));
	if (m_pHeartBoxList == nullptr)
	{
		ULOG(TEXT("Horizontal is nullptr"));
		return;
	}

	m_pShieldBoxList = Cast<UHorizontalBox>(GetWidgetFromName(TEXT("ShieldBox")));
	if (m_pShieldBoxList == nullptr)
	{
		ULOG(TEXT("Horizontal is nullptr"));
		return;
	}
	
}

void UWidget_BossHpHUD::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	Super::NativeTick(MyGeometry, InDeltaTime);

}

void UWidget_BossHpHUD::NativeDestruct()
{
	Super::NativeDestruct();

	if (m_pHeartBoxList != nullptr)
	{
		if (m_pHeartBoxList->IsValidLowLevel())
		{
			m_pHeartBoxList->ClearChildren();
			m_pHeartBoxList = nullptr;
		}
	}

	if (m_pShieldBoxList != nullptr)
	{
		if (m_pShieldBoxList->IsValidLowLevel())
		{
			m_pShieldBoxList->ClearChildren();
			m_pShieldBoxList = nullptr;
		}
	}

	if (m_pWidgetAni != nullptr)
	{
		if (m_pWidgetAni->IsValidLowLevel())
		{
			m_pWidgetAni->Destroy();
			m_pWidgetAni = nullptr;
		}
	}
}

void UWidget_BossHpHUD::SetActive(bool bActive)
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

void UWidget_BossHpHUD::SetPlayAnimation(FString sAniName, bool bRevers)
{
	if (m_pWidgetAni == nullptr) return;
	m_bRevers = bRevers;
	m_pWidgetAni->SetPlayAnimation(sAniName, m_bRevers == true ? EUMGSequencePlayMode::Reverse : EUMGSequencePlayMode::Forward);
}

void UWidget_BossHpHUD::Add_Hp(class UWidget_BossHpItem* pItem)
{
	if (m_pHeartBoxList != nullptr)
	{
		m_pHeartBoxList->AddChild(pItem);
	}
}

void UWidget_BossHpHUD::Add_Shield(class UWidget_BossShieldItem* pItem)
{
	if (m_pShieldBoxList != nullptr)
	{
		m_pShieldBoxList->AddChild(pItem);
	}
}
