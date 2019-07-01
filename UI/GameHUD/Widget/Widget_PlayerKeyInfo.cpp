// Fill out your copyright notice in the Description page of Project Settings.

#include "Widget_PlayerKeyInfo.h"
#include "../../Core/WidgetAni_Mng.h"
#include "Engine/Texture2D.h"
#include "Kismet/KismetMathLibrary.h"

void UWidget_PlayerKeyInfo::NativePreConstruct()
{
	Super::NativePreConstruct();

	m_pKeyText = Cast<UTextBlock>(GetWidgetFromName(TEXT("Name")));
	if (m_pKeyText != nullptr)
	{
		m_pKeyText->SetText(FText::FromString(m_sKeyName));
	}

	m_pIcon = Cast<UImage>(GetWidgetFromName(TEXT("Icon")));
	if (m_pIcon != nullptr)
	{		
		if ( m_pImage != nullptr )
			m_pIcon->SetBrushFromTexture(m_pImage);	
	}

}

void UWidget_PlayerKeyInfo::NativeConstruct()
{
	Super::NativeConstruct();

	m_pCoolTime = Cast<UProgressBar>(GetWidgetFromName(TEXT("CoolTime")));
	if (m_pCoolTime == nullptr)
	{
		ULOG(TEXT("Error UProgressBar"));
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

	m_pCoolTime->SetPercent(0.0f);
	ChangeState(static_cast<int32>(E_State_SkillTime::E_SKILL_NONE));
}

void UWidget_PlayerKeyInfo::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	Super::NativeTick(MyGeometry, InDeltaTime);

	switch (m_eState)
	{
		case static_cast<int32>(E_State_SkillTime::E_SKILL_NONE) :
			SkillTick_None(InDeltaTime);
			break;
		case static_cast<int32>(E_State_SkillTime::E_SKILL_START) :
			SkillTick_Start(InDeltaTime);
			break;
		case static_cast<int32>(E_State_SkillTime::E_SKILL_END) :
			SkillTick_End(InDeltaTime);
			break;
	}

	m_fInterep = FMath::FInterpTo(m_fInterep, m_fInterepValue, InDeltaTime, 10.0f);
	m_pCoolTime->SetPercent(m_fInterep);
}

void UWidget_PlayerKeyInfo::SetInit(float fCoolTimeSpeed)
{
	if (fCoolTimeSpeed > 0.0f)
		m_fCoolTimepeed = fCoolTimeSpeed;
}

void UWidget_PlayerKeyInfo::ChangeState(int32 eState)
{
	m_eState = eState;
}

void UWidget_PlayerKeyInfo::SkillTick_None(float fDeltaTime)
{
	m_fCoolTime_Curr = 0.0f;
	m_fCoolTime_Max = 1.0f;

	m_fInterep = 0.0f;
	m_fInterepValue = 0.0f;
	m_bCoolTime = false;
}

void UWidget_PlayerKeyInfo::SkillTick_Start(float fDeltaTime)
{
	if (m_fCoolTime_Curr >= m_fCoolTime_Max)
	{
		m_fCoolTime_Curr = m_fCoolTime_Max;
		ChangeState(static_cast<int32>(E_State_SkillTime::E_SKILL_END));
		return;
	}

	m_bCoolTime = true;
	m_fCoolTime_Curr += m_fCoolTimepeed * fDeltaTime;
	SetValue(m_fCoolTime_Curr);
}

void UWidget_PlayerKeyInfo::SkillTick_End(float fDeltaTime)
{
	m_bCoolTime = false;
	m_pWidgetAni->SetPlayAnimation("CoolTimeDone");
	ChangeState(static_cast<int32>(E_State_SkillTime::E_SKILL_NONE));
}

void UWidget_PlayerKeyInfo::SetValue(float fPercent)
{
	if (fPercent >= m_fCoolTime_Max) 
	{
		fPercent = m_fCoolTime_Max;
		return;
	}

	m_fInterepValue = fPercent;
}

void UWidget_PlayerKeyInfo::CoolTimeEffect()
{
	m_pWidgetAni->SetPlayAnimation("CoolTimeProgress");
}