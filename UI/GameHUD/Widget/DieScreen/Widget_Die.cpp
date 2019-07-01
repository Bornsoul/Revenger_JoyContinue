// Fill out your copyright notice in the Description page of Project Settings.

#include "Widget_Die.h"
#include "UI/Core/WidgetAni_Mng.h"
#include "Components/TextBlock.h"
#include "Kismet/KismetMathLibrary.h"

void UWidget_Die::NativeConstruct()
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

	m_pDieTimeLabel = Cast<UTextBlock>(GetWidgetFromName("DieText"));
	if (m_pDieTimeLabel == nullptr)
	{
		ULOG(TEXT("Textblock is nullptr"));
		return;
	}

	m_fDieTime_Val = 10.0f;
	SetButtonState(static_cast<int32>(E_Button_Die::E_NONE));
	SetActive(false);
}

void UWidget_Die::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	Super::NativeTick(MyGeometry, InDeltaTime);

	if (m_bDieTime)
	{
		if (m_fDieTime_Val <= 0.01f)
		{
			m_fDieTime_Val = 0.0f;
			SetDieText("0.00");
			DeActive_DieTime();
			return;
		}

		m_fDieTime_Val -= 1.0f * InDeltaTime;
		FString sStr = FString::Printf(TEXT("%d"), FMath::FloorToInt(m_fDieTime_Val));
		SetDieText(sStr);
	}

}

void UWidget_Die::SetPlayAnimation(FString sAniName, bool bRevers)
{
	if (m_pWidgetAni == nullptr) return;
	m_bRevers = bRevers;
	m_pWidgetAni->SetPlayAnimation(sAniName, m_bRevers == true ? EUMGSequencePlayMode::Reverse : EUMGSequencePlayMode::Forward);
}

void UWidget_Die::Active_DieTime(float fDieTime)
{
	ULOG(TEXT("Active DieTime"));
	m_fDieTime_Val = fDieTime;
	m_bDieTime = true;
}

void UWidget_Die::DeActive_DieTime()
{
	ULOG(TEXT("Active DeActive"));

	m_fDieTime_Val = 0.0f;
	SetDieText("0.00");
	m_bDieTime = false;
	UGameplayStatics::OpenLevel(GetWorld(), TEXT("Loading_Game"), true);
}

void UWidget_Die::SetActive(bool bActive)
{
	m_bActive = bActive;

	if (m_bActive == true)
	{
		GetRootWidget()->SetVisibility(ESlateVisibility::SelfHitTestInvisible);
	}
	else
	{
		GetRootWidget()->SetVisibility(ESlateVisibility::Hidden);
	}
}

void UWidget_Die::SetDieText(FString sStr)
{
	if (m_pDieTimeLabel == nullptr) return;
	m_pDieTimeLabel->SetText(FText::FromString(sStr));
}

void UWidget_Die::Menu_Destory()
{
	SetActive(false);
	m_bDestroy = true;
}

void UWidget_Die::Menu_Button(E_Button_Die eState)
{
	switch (eState)
	{
	case E_Button_Die::E_RESTART:
		SetButtonState(static_cast<int32>(E_Button_Die::E_RESTART));
		break;
	case E_Button_Die::E_QUIT:
		SetButtonState(static_cast<int32>(E_Button_Die::E_QUIT));
		break;
	}

}

void UWidget_Die::SetButtonState(int32 nState)
{
	m_nState = nState;
}
