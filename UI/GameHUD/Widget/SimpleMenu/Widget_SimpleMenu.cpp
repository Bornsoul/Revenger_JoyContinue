// Fill out your copyright notice in the Description page of Project Settings.

#include "Widget_SimpleMenu.h"

#include "Components/RichTextBlock.h"
#include "Kismet/KismetMathLibrary.h"

void UWidget_SimpleMenu::NativeConstruct()
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
	SetButtonState(static_cast<int32>(E_Button_State::E_NONE));
	SetActive(false);
}

void UWidget_SimpleMenu::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	Super::NativeTick(MyGeometry, InDeltaTime);

}

void UWidget_SimpleMenu::SetPlayAnimation(FString sAniName, bool bRevers)
{
	if (m_pWidgetAni == nullptr) return;
	m_bRevers = bRevers;
	m_pWidgetAni->SetPlayAnimation(sAniName, m_bRevers == true ? EUMGSequencePlayMode::Reverse : EUMGSequencePlayMode::Forward);
}

void UWidget_SimpleMenu::SetActive(bool bActive)
{
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

void UWidget_SimpleMenu::Menu_Destory()
{
	SetActive(false);
	m_bDestroy = true;
}

void UWidget_SimpleMenu::Menu_Start()
{
	SetButtonState(static_cast<int32>(E_Button_State::E_START));
}

void UWidget_SimpleMenu::Menu_Quit()
{
	SetButtonState(static_cast<int32>(E_Button_State::E_QUIT));
}

void UWidget_SimpleMenu::SetButtonState(int32 nState)
{
	m_nState = nState;
}