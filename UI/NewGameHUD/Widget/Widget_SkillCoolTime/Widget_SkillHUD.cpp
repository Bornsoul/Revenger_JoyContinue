// Fill out your copyright notice in the Description page of Project Settings.

#include "Widget_SkillHUD.h"

#include "Widget_SkillItem.h"
#include "Widget_SkillShieldItem.h"

#include "UI/Core/WidgetAni_Mng.h"
#include "Kismet/KismetMathLibrary.h"

void UWidget_SkillHUD::NativePreConstruct()
{
	Super::NativePreConstruct();

}

void UWidget_SkillHUD::NativeConstruct()
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

	for (int32 i = 0; i < 3; i++)
	{
		FString sStr = FString::Printf(TEXT("Item_%d"), i);
		m_pSkillItemList.Add(Cast<UWidget_SkillItem>(GetWidgetFromName(*sStr)));
	}
	
	m_pSkillShield = Cast<UWidget_SkillShieldItem>(GetWidgetFromName("Shield"));
	if(m_pSkillShield == nullptr)
	{
		ULOG(TEXT("Shield is nullptr"));
		return;
	}
}

void UWidget_SkillHUD::SetSkillEnter()
{
	for (int32 i = 0; i < m_pSkillItemList.Num(); i++)
	{
		m_pSkillItemList[i]->SetEnter();
	}

	m_pSkillShield->SetEnter();
}

void UWidget_SkillHUD::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	Super::NativeTick(MyGeometry, InDeltaTime);

}

void UWidget_SkillHUD::SetActive(bool bActive)
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

void UWidget_SkillHUD::SetPlayAnimation(FString sAniName, bool bRevers)
{
	if (m_pWidgetAni == nullptr) return;
	m_bRevers = bRevers;
	m_pWidgetAni->SetPlayAnimation(sAniName, m_bRevers == true ? EUMGSequencePlayMode::Reverse : EUMGSequencePlayMode::Forward);
}

void UWidget_SkillHUD::Active_CoolTime(int32 nIndex, float fCoolTime)
{
	if (nIndex > m_pSkillItemList.Num()) return;

	m_pSkillItemList[nIndex]->Active_CoolTime(fCoolTime);
}

void UWidget_SkillHUD::Active_CoolTimeCount(int32 nIndex)
{
	if (nIndex > m_pSkillItemList.Num()) return;

	m_pSkillItemList[nIndex]->Active_CoolTimeCount();
}

void UWidget_SkillHUD::Active_ShieldCoolTime(float fCoolTime)
{
	m_pSkillShield->Active_CoolTime(fCoolTime);
}

void UWidget_SkillHUD::Tick_SkillCoolTime(float fDeltaTime)
{
	if (m_pSkillItemList.Num() <= 0) return;
	for (int32 i = 0; i < m_pSkillItemList.Num(); i++)
	{
		m_pSkillItemList[i]->Tick_SkillCoolTime(fDeltaTime);
	}
}

void UWidget_SkillHUD::Tick_SkillCoolTimeCount(float fDeltaTime)
{
	if (m_pSkillItemList.Num() <= 0) return;
	for (int32 i = 0; i < m_pSkillItemList.Num(); i++)
	{
		m_pSkillItemList[i]->Tick_SkillCoolTimeCount(fDeltaTime);
	}
}

void UWidget_SkillHUD::Tick_SkillShieldTime(float fDeltaTime)
{
	m_pSkillShield->Tick_SkillShieldCoolTime(fDeltaTime);
}
