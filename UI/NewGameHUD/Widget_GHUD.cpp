// Fill out your copyright notice in the Description page of Project Settings.

#include "Widget_GHUD.h"
#include "UI/Core/WidgetAni_Mng.h"
#include "Widget/Widget_BulletTime/Widget_SlowGageHUD.h"
#include "Widget/Widget_SkillCoolTime/Widget_SkillHUD.h"
#include "Widget/Widget_TopTitleItem.h"
//#include "Widget/Widget_QuestAlarm/Widget_QuestAlarmHUD.h"

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

	m_pSlowGage_HUD = Cast<UWidget_SlowGageHUD>(GetWidgetFromName(TEXT("SlowGage")));
	if (m_pSlowGage_HUD == nullptr)
	{
		ULOG(TEXT("SlowGage HUD is nullptr"));
		return;
	}

	m_pSkill_HUD = Cast<UWidget_SkillHUD>(GetWidgetFromName(TEXT("SkillHUD")));
	if (m_pSkill_HUD == nullptr)
	{
		ULOG(TEXT("SkillHUD is nullptr"));
		return;
	}

	m_pTopTitle = Cast<UWidget_TopTitleItem>(GetWidgetFromName(TEXT("TopTitle")));
	if (m_pTopTitle == nullptr)
	{
		ULOG(TEXT("topTile is nullptr"));
		return;
	}
	m_pTopTitle->SetActive(false);

	/*m_pQuest_HUD = Cast<UWidget_QuestAlarmHUD>(GetWidgetFromName(TEXT("QuestAlarm")));
	if (m_pQuest_HUD == nullptr)
	{
		ULOG(TEXT("QuestHUD is nullptr"));
		return;
	}*/

	m_pVertcal_Status = Cast<UVerticalBox>(GetWidgetFromName(TEXT("VertStat")));
	if (m_pVertcal_Status == nullptr)
	{
		ULOG(TEXT("Vertical is nullptr"));
		return;
	}

}

void UWidget_GHUD::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	Super::NativeTick(MyGeometry, InDeltaTime);

}

void UWidget_GHUD::NativeDestruct()
{
	Super::NativeDestruct();

	if (m_pWidgetAni != nullptr)
	{
		if (m_pWidgetAni->IsValidLowLevel())
		{
			m_pWidgetAni->Destroy();
			m_pWidgetAni = nullptr;
		}
	}

	/*if (m_pQuest_HUD != nullptr)
	{
		if (m_pQuest_HUD->IsValidLowLevel())
		{
			m_pQuest_HUD->RemoveFromParent();
			m_pQuest_HUD = nullptr;
		}
	}*/

	if (m_pSkill_HUD != nullptr)
	{
		if (m_pSkill_HUD->IsValidLowLevel())
		{
			m_pSkill_HUD->RemoveFromParent();
			m_pSkill_HUD = nullptr;
		}
	}

	if (m_pSlowGage_HUD != nullptr)
	{
		if (m_pSlowGage_HUD->IsValidLowLevel())
		{
			m_pSlowGage_HUD->RemoveFromParent();
			m_pSlowGage_HUD = nullptr;
		}
	}

	if (m_pTopTitle != nullptr)
	{
		if (m_pTopTitle->IsValidLowLevel())
		{
			m_pTopTitle->RemoveFromParent();
			m_pTopTitle = nullptr;
		}
	}

	if (m_pVertcal_Status != nullptr)
	{
		if (m_pVertcal_Status->IsValidLowLevel())
		{
			m_pVertcal_Status->RemoveFromParent();
			m_pVertcal_Status = nullptr;
		}
	}

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