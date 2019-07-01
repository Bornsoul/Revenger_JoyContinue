// Fill out your copyright notice in the Description page of Project Settings.

#include "Widget_GameHUD.h"
#include "Widget_PlayerDash.h"
#include "Widget_PlayerKeyInfo.h"
#include "../../Core/WidgetAni_Mng.h"

#include "Components/TextBlock.h"

void UWidget_GameHUD::NativeConstruct()
{
	Super::NativeConstruct();

	for (int32 i = 1; i <= 3; i++)
	{
		FString sText = "Dash" + FString::FromInt(i);
		m_pGageArr.Add(Cast<UWidget_PlayerDash>(GetWidgetFromName(*sText)));
		if (m_pGageArr[i - 1] == nullptr)
		{
			ULOG(TEXT("nullptr Dash%d"), i);
		}
	}

	for (int32 i = 1; i <= 3; i++)
	{
		FString sText = "Key" + FString::FromInt(i);
		m_pSkillArr.Add(Cast<UWidget_PlayerKeyInfo>(GetWidgetFromName(*sText)));
		if (m_pSkillArr[i - 1] == nullptr)
		{
			ULOG(TEXT("nullptr Key%d"), i);
		}
	}

	m_pStageTxt = Cast<UTextBlock>(GetWidgetFromName(TEXT("StageTxt")));
	if (m_pStageTxt == nullptr)
	{
		ULOG(TEXT("UText is nullptr"));
		return;
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

	m_bActive = true;
	InitDash();
	SetStageName(TEXT("Rabbit City 2 floor"));

}

void UWidget_GameHUD::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	Super::NativeTick(MyGeometry, InDeltaTime);

	if (m_bActive == false) return;
	DashTick_AddDash(InDeltaTime);
}

void UWidget_GameHUD::SetShow(bool bShow)
{	
	if (m_bActive == bShow) return;

	if (bShow)
	{		
		m_pWidgetAni->SetPlayAnimation("Shutdown", EUMGSequencePlayMode::Reverse);
	}
	else
	{
		m_pWidgetAni->SetPlayAnimation("Shutdown");
	}

	m_bActive = bShow;
}

void UWidget_GameHUD::InitDash()
{
	//ULOG(TEXT("InitDash : %d"), m_pGageArr.Num());
	for (int32 i = 0; i < (m_pGageArr.Num() - 1); i++)
	{
		m_pGageArr[i]->SetShow(true);
	}

	m_fDashTime_Curr = 0.0f;
	m_fDashTime_End = 2.0f;
}

void UWidget_GameHUD::DashTick_AddDash(float fDeltaTime)
{	
	if (m_pGageArr[m_pGageArr.Num() - 1]->GetShow() == true) return;

	m_fDashTime_Curr += fDeltaTime;
	if (m_fDashTime_Curr >= m_fDashTime_End)
	{
		m_fDashTime_Curr = 0.0f;
		AddDash();
		return;
	}
}

bool UWidget_GameHUD::AddDash()
{
	if (m_pGageArr[m_pGageArr.Num()-1]->GetShow() == true)
	{
		ULOG(TEXT("Dash is full!"));
		return false;
	}	
		
	for (int32 i = 0; i <= (m_pGageArr.Num()-1); i++)
	{
		if (m_pGageArr[i]->GetShow() == false)
		{
			m_pGageArr[i]->SetShow(true);
			return true;
		}
	}

	return false;
}

bool UWidget_GameHUD::RemoveDash()
{	
	if (m_pGageArr[0]->GetShow() == false)
	{
		ULOG(TEXT("Dash is Empty"));
		return false;
	}

	for (int32 i = (m_pGageArr.Num() - 1); i >= 0; i--)
	{
		if (m_pGageArr[i]->GetShow() == true)
		{
			m_pGageArr[i]->SetShow(false);
			return true;
		}
	}

	return false;
}

bool UWidget_GameHUD::GetDashAllEmpty()
{
	if (m_pGageArr[0]->GetShow() == false)
		return true;

	return false;
}
//
//void UWidget_GameHUD::InitSlow()
//{
//	m_bUseSlow = false;
//	m_pSlowMotion->SetInit(1.0f);
//	m_pSlowMotion->ChangeSlowState(static_cast<int32>(E_State_SlowTime::E_SLOW_NONE));
//}
//
//void UWidget_GameHUD::DeActive_SlowMotion()
//{
//	if (m_bUseSlow == false) return;
//	m_pSlowMotion->ChangeSlowState(static_cast<int32>(E_State_SlowTime::E_SLOW_END));
//	m_bUseSlow = false;
//	//ULOG(TEXT("DeActive Slow"));
//}
//
//void UWidget_GameHUD::Active_SlowMotion()
//{
//	if (m_bUseSlow == true) return;
//	m_pSlowMotion->SetShow(true);
//	m_pSlowMotion->ChangeSlowState(static_cast<int32>(E_State_SlowTime::E_SLOW_START));
//	m_bUseSlow = true;
//	//ULOG(TEXT("Active Slow"));
//}
//
//bool UWidget_GameHUD::GetSlowEmpty()
//{ 
//	return m_pSlowMotion->GetSlowEmpty(); 
//}

void UWidget_GameHUD::SetStageName(FString sName)
{
	m_pStageTxt->SetText(FText::FromString(sName));
}

void UWidget_GameHUD::InitKeyInfo(float fKey1, float fKey2, float fKey3)
{	
	for (int32 i = 0; i < (m_pSkillArr.Num() - 1); i++)
	{		
		m_pSkillArr[i]->ChangeState(static_cast<int32>(E_State_SkillTime::E_SKILL_NONE));
	}

	m_pSkillArr[0]->SetInit(fKey1);
	m_pSkillArr[1]->SetInit(fKey2);
	m_pSkillArr[2]->SetInit(fKey3);
}

void UWidget_GameHUD::Active_KeyCoolTime(int32 nSelect)
{
	if (m_pSkillArr[nSelect]->GetCoolTime() == false)
		m_pSkillArr[nSelect]->ChangeState(static_cast<int32>(E_State_SkillTime::E_SKILL_START));
	else
		m_pSkillArr[nSelect]->CoolTimeEffect();
		//ULOG(TEXT("ÀÌ¹Ì ÄðÅ¸ÀÓ"));
}

bool UWidget_GameHUD::GetCoolTimeCheck(int32 nSelect)
{
	return m_pSkillArr[nSelect]->GetCoolTime();
}
