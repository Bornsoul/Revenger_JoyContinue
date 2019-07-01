// Fill out your copyright notice in the Description page of Project Settings.

#include "Widget_SkillShieldItem.h"

#include "UI/Core/WidgetAni_Mng.h"
#include "Components/TextBlock.h"
#include "Components/Image.h"
#include "Components/ProgressBar.h"
#include "Kismet/KismetMathLibrary.h"

void UWidget_SkillShieldItem::NativePreConstruct()
{
	Super::NativePreConstruct();

	m_pIcon = nullptr;
	m_pIcon = Cast<UImage>(GetWidgetFromName(TEXT("Icon")));

	if (m_pIcon_Normal->GetPathName() == "None")
	{
		m_pIcon->SetVisibility(ESlateVisibility::Hidden);
	}
	else
	{
		m_pIcon->SetVisibility(ESlateVisibility::Visible);
		m_pIcon->SetBrushFromTexture(m_pIcon_Normal);
	}

	m_pCoolTime = nullptr;
	m_pCoolTime = Cast<UProgressBar>(GetWidgetFromName(TEXT("Gage")));

	DeActive_CoolTime();
}

void UWidget_SkillShieldItem::NativeConstruct()
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

}

void UWidget_SkillShieldItem::SetEnter()
{
	m_bCoolTimeActive = false;

	m_fCoolTime_Cur = 0.0f;
	m_fCoolTime_Lerp = 0.0f;
}

void UWidget_SkillShieldItem::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	Super::NativeTick(MyGeometry, InDeltaTime);

}

void UWidget_SkillShieldItem::Tick_SkillShieldCoolTime(float fDeltaTime)
{

	if (m_bCoolTimeActive == true)
	{
		if (m_fCoolTime_CurTime >= m_fCoolTime_End)
		{
			m_fCoolTime_CurTime = m_fCoolTime_End;
			DeActive_CoolTime();
			return;
		}

		float fTime = m_fCoolTime_End > 1.0f ? 1.0f : m_fCoolTime_End;
		if (UGameplayStatics::GetRealTimeSeconds(GetWorld()) - m_fCoolTime_Cur >= fTime)
		{
			m_fCoolTime_CurTime += 1.0f;
			m_fCoolTime_Percent = m_fCoolTime_CurTime / m_fCoolTime_End * 1.0f;
			m_fCoolTime_Cur = UGameplayStatics::GetRealTimeSeconds(GetWorld());
		}

		if (m_fCoolTime_End > 1.0f)
		{
			for (float i = 0.0f; i < m_fCoolTime_Percent; i += fDeltaTime)
			{
				m_fCoolTime_Lerp = FMath::Lerp(m_fCoolTime_Lerp, 1.0f, i * fDeltaTime);
			}
			//m_fCoolTime_Lerp = FMath::Lerp(m_fCoolTime_Lerp, 1.0f, m_fCoolTime_Percent*fDeltaTime);
			m_pCoolTime->SetPercent(m_fCoolTime_Lerp);
		}
		else
		{
			m_fCoolTime_Lerp = FMath::Lerp(m_fCoolTime_Lerp, 1.0f, 10.0f*fDeltaTime);
			m_pCoolTime->SetPercent(m_fCoolTime_Lerp);
		}
	}



}
void UWidget_SkillShieldItem::SetActive(bool bActive)
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

void UWidget_SkillShieldItem::SetPlayAnimation(FString sAniName, bool bRevers)
{
	if (m_pWidgetAni == nullptr) return;
	m_bRevers = bRevers;
	m_pWidgetAni->SetPlayAnimation(sAniName, m_bRevers == true ? EUMGSequencePlayMode::Reverse : EUMGSequencePlayMode::Forward);
}

void UWidget_SkillShieldItem::Active_CoolTime(float fCoolTime)
{
	if (m_bCoolTimeActive == true)
	{
		ULOG(TEXT("CoolTime InProgress"));
		return;
	}

	m_pIcon->SetBrushFromTexture(m_pIcon_Normal);
	m_pCoolTime->SetVisibility(ESlateVisibility::Visible);
	m_pCoolTime->SetPercent(0.0f);

	m_fCoolTime_Cur = UGameplayStatics::GetRealTimeSeconds(GetWorld());

	m_fCoolTime_End = fCoolTime;
	m_fCoolTime_CurTime = 0.0f;
	m_fCoolTime_Percent = 0.0f;
	m_fCoolTime_Lerp = 0.0f;
	m_bCoolTimeActive = true;
}

void UWidget_SkillShieldItem::DeActive_CoolTime()
{
	m_pIcon->SetBrushFromTexture(m_pIcon_Shield);
	m_pCoolTime->SetPercent(1.0f);
	m_pCoolTime->SetVisibility(ESlateVisibility::Hidden);

	m_fCoolTime_Cur = UGameplayStatics::GetRealTimeSeconds(GetWorld());

	m_fCoolTime_CurTime = 0.0f;
	m_fCoolTime_Lerp = 0.0f;
	m_bCoolTimeActive = false;

}