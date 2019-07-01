// Fill out your copyright notice in the Description page of Project Settings.

#include "Widget_SkillItem.h"
#include "UI/Core/WidgetAni_Mng.h"

#include "Components/TextBlock.h"
#include "Components/Image.h"
#include "Components/ProgressBar.h"
#include "Kismet/KismetMathLibrary.h"

#define EmptyCheck(a) { if (a == nullptr)	{ ULOG(TEXT("nullptr")); return;	} }
#define EmptyChecks(a, b) { if (a == nullptr || b == nullptr)	{ ULOG(TEXT("nullptr")); return;	} }

void UWidget_SkillItem::NativePreConstruct()
{
	Super::NativePreConstruct();

	m_pIcon = nullptr;
	m_pIcon = Cast<UImage>(GetWidgetFromName(TEXT("Icon")));
	EmptyCheck(m_pIcon);

	if (m_pIcon_Normal->GetPathName() == "None")
	{
		m_pIcon->SetVisibility(ESlateVisibility::Hidden);
	}
	else
	{
		m_pIcon->SetVisibility(ESlateVisibility::Visible);
		m_pIcon->SetBrushFromTexture(m_pIcon_Normal);
	}

	m_pLabel = nullptr;
	m_pLabel = Cast<UImage>(GetWidgetFromName(TEXT("Label")));
	EmptyCheck(m_pLabel);

	if (m_pIcon_Label->GetPathName() == "None")
	{
		m_pLabel->SetVisibility(ESlateVisibility::Hidden);
	}
	else
	{
		m_pLabel->SetVisibility(ESlateVisibility::Visible);
		m_pLabel->SetBrushFromTexture(m_pIcon_Label);		
	}

	m_pCoolTime = nullptr;
	m_pCoolTime = Cast<UProgressBar>(GetWidgetFromName(TEXT("Gage")));			
	EmptyCheck(m_pCoolTime);

	m_pCoolTime_Text = nullptr;
	m_pCoolTime_Text = Cast<UTextBlock>(GetWidgetFromName(TEXT("GageLabel")));
	EmptyCheck(m_pCoolTime_Text);

	m_pCountList.Empty();
	for (int32 i = 0; i < 3; i++)
	{
		FString sStr = FString::Printf(TEXT("Cnt%d"), i);
		m_pCountList.Add(Cast<UProgressBar>(GetWidgetFromName(*sStr)));
	}

	SetCountHidden(m_bUseCount);
	DeActive_CoolTime();
}

void UWidget_SkillItem::NativeConstruct()
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

void UWidget_SkillItem::SetEnter()
{
	m_bCoolTimeActive = false;
	m_bCoolTimeCountActive = false;
	m_bCoolTimeCount_WaitActive = false;

	m_fCoolTime_Cur = 0.0f;
	m_fCoolTimeCount_Cur = 0.0f;
	m_fCoolTime_Lerp = 0.0f;
	
	m_nCoolTimeCount_Val = m_pCountList.Num();
	//ULOG(TEXT("Count : %d"), m_nCoolTimeCount_Val);
}

void UWidget_SkillItem::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	Super::NativeTick(MyGeometry, InDeltaTime);

}

void UWidget_SkillItem::Tick_SkillCoolTime(float fDeltaTime)
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
				m_fCoolTime_Lerp = FMath::Lerp(m_fCoolTime_Lerp, m_fCoolTime_Percent, i * fDeltaTime);
			}
			m_pCoolTime->SetPercent(m_fCoolTime_Lerp);
		}
		else
		{
			m_fCoolTime_Lerp = FMath::Lerp(m_fCoolTime_Lerp, 1.0f, 10.0f*fDeltaTime);

			m_pCoolTime->SetPercent(m_fCoolTime_Lerp);
		}

		float fResult = m_fCoolTime_End - m_fCoolTime_CurTime;
		if (fResult <= 0.0f) fResult = 0.0f;

		FString sStr = FString::Printf(TEXT("%d"), FMath::FloorToInt(fResult));
		m_pCoolTime_Text->SetText(FText::FromString(sStr));
	}

}

void UWidget_SkillItem::Tick_SkillCoolTimeCount(float fDeltaTime)
{
	if (m_bCoolTimeCount_WaitActive == true) return;
	if (m_bCoolTimeCountActive == true)
	{
		if (UGameplayStatics::GetRealTimeSeconds(GetWorld()) - m_fCoolTimeCount_Cur >= m_fCoolTimeCount_End)
		{
			m_fCoolTimeCount_Cur = UGameplayStatics::GetRealTimeSeconds(GetWorld());
			DeActive_CoolTimeCount();
		}
	}
}

void UWidget_SkillItem::SetActive(bool bActive)
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

void UWidget_SkillItem::SetPlayAnimation(FString sAniName, bool bRevers)
{
	if (m_pWidgetAni == nullptr) return;
	m_bRevers = bRevers;
	m_pWidgetAni->SetPlayAnimation(sAniName, m_bRevers == true ? EUMGSequencePlayMode::Reverse : EUMGSequencePlayMode::Forward);
}

void UWidget_SkillItem::Active_CoolTime(float fCoolTime)
{
	EmptyChecks(m_pCoolTime, m_pCoolTime_Text);
	if (m_bCoolTimeActive == true)
	{
		ULOG(TEXT("CoolTime InProgress"));
		return;
	}

	m_pIcon->SetBrushFromTexture(m_pIcon_Outline);
	m_pCoolTime->SetVisibility(ESlateVisibility::Visible);
	m_pCoolTime->SetPercent(0.0f);

	m_pCoolTime_Text->SetVisibility(ESlateVisibility::Visible);
	m_pCoolTime_Text->SetText(FText::FromString(FString::FromInt(FMath::FloorToInt(fCoolTime))));
	
	m_pLabel->SetVisibility(ESlateVisibility::Hidden);

	m_fCoolTime_Cur = UGameplayStatics::GetRealTimeSeconds(GetWorld());

	m_fCoolTime_End = fCoolTime;
	m_fCoolTime_CurTime = 0.0f;
	m_fCoolTime_Percent = 0.0f;
	m_fCoolTime_Lerp = 0.0f;
	m_bCoolTimeActive = true;
}

void UWidget_SkillItem::DeActive_CoolTime()
{
	EmptyChecks(m_pCoolTime, m_pCoolTime_Text);
	
	m_pIcon->SetBrushFromTexture(m_pIcon_Normal);
	m_pCoolTime->SetPercent(1.0f);
	m_pCoolTime->SetVisibility(ESlateVisibility::Hidden);

	m_pCoolTime_Text->SetText(FText::FromString(" "));
	m_pCoolTime_Text->SetVisibility(ESlateVisibility::Hidden);	

	m_pLabel->SetVisibility(ESlateVisibility::Visible);

	m_fCoolTime_Cur = UGameplayStatics::GetRealTimeSeconds(GetWorld());

	m_fCoolTime_CurTime = 0.0f;
	m_fCoolTime_Lerp = 0.0f;
	m_bCoolTimeActive = false;

	if (m_bCoolTimeCountActive == true)
	{
		DeActive_CoolTimeCount();
	}
}

void UWidget_SkillItem::SetCountHidden(bool bHidden)
{
	for (int32 i = 0; i < m_pCountList.Num(); i++)
	{
		if (bHidden == true)
		{
			m_pCountList[i]->SetVisibility(ESlateVisibility::Visible);
		}
		else
		{
			m_pCountList[i]->SetVisibility(ESlateVisibility::Hidden);
		}
	}
}

void UWidget_SkillItem::SetCountUseActive(int32 nMaxIndex)
{
	if (nMaxIndex < 0 || nMaxIndex > m_pCountList.Num())
	{
		ULOG(TEXT("MaxIndex is Nullptr"));
		return;
	}

	for (int32 i = 0; i < m_pCountList.Num(); i++)
	{
		m_pCountList[i]->SetPercent(0.0f);
	}

	for (int32 i = 0; i < nMaxIndex; i++)
	{
		m_pCountList[i]->SetPercent(1.0f);
	}
}

void UWidget_SkillItem::Active_CoolTimeCount()
{
	if (m_bUseCount == false)
	{
		ULOG(TEXT("This is Not UseCount Item"));
		return;
	}
	if (m_bCoolTimeCount_WaitActive == true)return;

	if (m_nCoolTimeCount_Val <= 1)
	{
		ULOG(TEXT("CoolTimeCount is Empty"));
		Active_CoolTime(2.0f);
		m_bCoolTimeCount_WaitActive = true;
		m_nCoolTimeCount_Val = 0;
		m_fCoolTimeCount_Cur = UGameplayStatics::GetRealTimeSeconds(GetWorld());

		SetCountUseActive(m_nCoolTimeCount_Val);
		return;
	}

	m_fCoolTimeCount_Cur = UGameplayStatics::GetRealTimeSeconds(GetWorld());

	m_fCoolTimeCount_End = 2.0f;	
	m_nCoolTimeCount_Val -= 1;
	m_bCoolTimeCountActive = true;
	SetCountUseActive(m_nCoolTimeCount_Val);

}

void UWidget_SkillItem::DeActive_CoolTimeCount()
{
	if (m_nCoolTimeCount_Val >= m_pCountList.Num()-1)
	{
		ULOG(TEXT("CoolTimeCount is Full"));
		m_nCoolTimeCount_Val = m_pCountList.Num();
		SetCountUseActive(m_nCoolTimeCount_Val);

		m_fCoolTimeCount_Cur = UGameplayStatics::GetRealTimeSeconds(GetWorld());

		m_bCoolTimeCountActive = false;
		return;
	}

	m_bCoolTimeCount_WaitActive = false;
	m_fCoolTimeCount_Cur = UGameplayStatics::GetRealTimeSeconds(GetWorld());

	m_nCoolTimeCount_Val += 1;
	SetCountUseActive(m_nCoolTimeCount_Val);	
}