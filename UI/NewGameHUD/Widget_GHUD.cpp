// Fill out your copyright notice in the Description page of Project Settings.

#include "Widget_GHUD.h"
#include "UI/Core/WidgetAni_Mng.h"
#include "Widget/Widget_BulletTime/Widget_SlowGageHUD.h"
#include "Widget/Widget_SkillCoolTime/Widget_SkillHUD.h"
#include "Widget/Widget_TopTitleItem.h"

#include "Kismet/KismetMathLibrary.h"

void UWidget_GHUD::NativePreConstruct()
{
	Super::NativePreConstruct();

}

void UWidget_GHUD::NativeConstruct()
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

	m_pSlowGage_HUD = Cast<UWidget_SlowGageHUD>(GetWidgetFromName("SlowGage"));
	if (m_pSlowGage_HUD == nullptr)
	{
		ULOG(TEXT("SlowGage HUD is nullptr"));
		return;
	}

	m_pSkill_HUD = Cast<UWidget_SkillHUD>(GetWidgetFromName("SkillHUD"));
	if (m_pSkill_HUD == nullptr)
	{
		ULOG(TEXT("SkillHUD is nullptr"));
		return;
	}

	m_pTopTitle = Cast<UWidget_TopTitleItem>(GetWidgetFromName("TopTitle"));
	if (m_pTopTitle == nullptr)
	{
		ULOG(TEXT("topTile is nullptr"));
		return;
	}
	m_pTopTitle->SetActive(false);

}

void UWidget_GHUD::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	Super::NativeTick(MyGeometry, InDeltaTime);

}

void UWidget_GHUD::SetActive(bool bActive)
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

void UWidget_GHUD::SetPlayAnimation(FString sAniName, bool bRevers)
{
	if (m_pWidgetAni == nullptr) return;
	m_bRevers = bRevers;
	m_pWidgetAni->SetPlayAnimation(sAniName, m_bRevers == true ? EUMGSequencePlayMode::Reverse : EUMGSequencePlayMode::Forward);
}

void UWidget_GHUD::Active_TopTitle(bool bActive)
{
	if (bActive)
	{
		m_pTopTitle->SetActive(true);
		m_pTopTitle->Active_Title();
	}
	else
	{
		m_pTopTitle->DeActive_Title();
	}
}