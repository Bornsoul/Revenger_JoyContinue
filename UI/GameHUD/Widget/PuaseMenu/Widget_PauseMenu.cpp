// Fill out your copyright notice in the Description page of Project Settings.

#include "Widget_PauseMenu.h"
#include "UI/Core/WidgetAni_Mng.h"

#include "Kismet/KismetMathLibrary.h"

void UWidget_PauseMenu::NativeConstruct()
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

	m_bDestroy = false;
	SetButtonState(static_cast<int32>(E_Button_Pause::E_NONE));
	SetActive(false);
}

void UWidget_PauseMenu::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	Super::NativeTick(MyGeometry, InDeltaTime);

}

void UWidget_PauseMenu::SetPlayAnimation(FString sAniName, bool bRevers)
{
	if (m_pWidgetAni == nullptr) return;
	m_bRevers = bRevers;
	m_pWidgetAni->SetPlayAnimation(sAniName, m_bRevers == true ? EUMGSequencePlayMode::Reverse : EUMGSequencePlayMode::Forward);
}

void UWidget_PauseMenu::SetActive(bool bActive)
{
	SetButtonState(static_cast<int32>(E_Button_Pause::E_NONE));
	
	m_bActive = bActive;

	if (m_bActive == true)
	{
		GetRootWidget()->SetVisibility(ESlateVisibility::Visible);
	}
	else
	{
		GetRootWidget()->SetVisibility(ESlateVisibility::Hidden);
	}
}

void UWidget_PauseMenu::Menu_Destory()
{
	SetActive(false);
	m_bDestroy = true;
}

void UWidget_PauseMenu::Menu_Button(E_Button_Pause eState)
{
	switch (eState)
	{
	case E_Button_Pause::E_RESUME:
		SetButtonState(static_cast<int32>(E_Button_Pause::E_RESUME));
		break;
	case E_Button_Pause::E_RESTART:
		SetButtonState(static_cast<int32>(E_Button_Pause::E_RESTART));
		break;
	case E_Button_Pause::E_QUIT:
		SetButtonState(static_cast<int32>(E_Button_Pause::E_QUIT));
		break;
	}

}

void UWidget_PauseMenu::SetButtonState(int32 nState)
{
	m_nState = nState;
}
