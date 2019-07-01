// Fill out your copyright notice in the Description page of Project Settings.

#include "Widget_PlayerSlowMotion.h"
#include "../../Core/WidgetAni_Mng.h"

#include "Runtime/UMG/Public/Animation/WidgetAnimation.h"
#include "Kismet/KismetMathLibrary.h"

void UWidget_PlayerSlowMotion::NativeConstruct()
{
	Super::NativeConstruct();

	m_pGage = Cast<UImage>(GetWidgetFromName(TEXT("Gage")));
	if (m_pGage == nullptr)
	{
		ULOG(TEXT("Error UProgressBar"));
	}


	m_pGageValueText = Cast<UTextBlock>(GetWidgetFromName(TEXT("GageValue")));
	if (m_pGageValueText == nullptr)
	{
		ULOG(TEXT("Error UTextBlock"));
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

	m_pMaterialInstance = Cast<UMaterialInterface >(m_pGage->Brush.GetResourceObject());
	if (m_pMaterialInstance == nullptr)
	{
		ULOG(TEXT("Error m_pMaterialInstance"));
	}
	else
	{
		m_pMaterialDynamic = UMaterialInstanceDynamic::Create(m_pMaterialInstance, nullptr);

		if (m_pMaterialDynamic == nullptr)
		{
			ULOG(TEXT("Error UMaterialInstanceDynamic"));
		}
		else
		{
			m_pGage->Brush.SetResourceObject(m_pMaterialDynamic);
		}
	}

	ChangeSlowState(static_cast<int32>(E_State_SlowTime::E_SLOW_NONE));
}

void UWidget_PlayerSlowMotion::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	Super::NativeTick(MyGeometry, InDeltaTime);

	switch (m_eSlowState)
	{
	case static_cast<int32>(E_State_SlowTime::E_SLOW_NONE) :
			SlowTick_None(InDeltaTime);
		break;
	case static_cast<int32>(E_State_SlowTime::E_SLOW_START) :
			SlowTick_Start(InDeltaTime);
		break;
	case static_cast<int32>(E_State_SlowTime::E_SLOW_END) :
			SlowTick_End(InDeltaTime);
		break;
	}

	if ( m_fValue <= 0.0f )
		m_bEmptySlow = true;
	else if ( m_fValue > 0.1f )
		m_bEmptySlow = false;

	if (m_fCurrValue_Front <= 0.0f)
		m_fCurrValue_Front = 0.0f;

	m_fCurrValue_Front = FMath::FInterpTo(m_fCurrValue_Front, m_fPerValue, InDeltaTime, 7.0f);
	
	if (m_pGage != nullptr)
	m_pMaterialDynamic->SetScalarParameterValue(FName(TEXT("ProgressBar")), m_fCurrValue_Front);

	FString sText = FString::Printf(TEXT("%d%%"), static_cast<int32>(m_fPerValue*100));// FString::FromInt(sAA) + "%";
	if ( m_pGageValueText != nullptr)
		m_pGageValueText->SetText(FText::FromString(sText));
}

void UWidget_PlayerSlowMotion::SetInit(float fGage)
{
	m_fPerValue = fGage;
	m_fValue = fGage;
	m_fCurrValue_Front = fGage;

	m_bUseSlow = false;
	m_bEmptySlow = false;

	GetRootWidget()->SetVisibility(ESlateVisibility::Hidden);
}

void UWidget_PlayerSlowMotion::SetShow(bool bShow)
{

	if (bShow)
	{		
		if (m_eSlowState == static_cast<int32>(E_State_SlowTime::E_SLOW_NONE))
			m_pWidgetAni->SetPlayAnimation("SlowShow");
	}
	else
	{
		m_pWidgetAni->SetPlayAnimation("SlowHide");
	}
}

void UWidget_PlayerSlowMotion::SetPercent(float fValue)
{
	if (m_fPerValue <= 0.0f)
	{
		m_fPerValue = 0.0f;		
	}
	if (m_fPerValue >= 1.0f)
	{
		m_fPerValue = 1.0f;
	}

	m_fPerValue = fValue;
}

void UWidget_PlayerSlowMotion::ChangeSlowState(int32 eState)
{	
	if ( eState == static_cast<int32>(E_State_SlowTime::E_SLOW_START))
		GetRootWidget()->SetVisibility(ESlateVisibility::Visible);

	m_eSlowState = eState;
}

void UWidget_PlayerSlowMotion::SlowTick_None(float fDeltaTime)
{
	if (m_bUseSlow)
	{
		SetShow(false);
		m_bUseSlow = false;
	}

	m_fValue = 1.0f;
	SetPercent(m_fValue);
}

void UWidget_PlayerSlowMotion::SlowTick_Start(float fDeltaTime)
{
	if (m_fValue <= 0.0f)
	{
		m_fValue = 0.0f;
		ChangeSlowState(static_cast<int32>(E_State_SlowTime::E_SLOW_END));
		return;
	}
	m_bUseSlow = true;
	m_fValue -= m_fUseSpeed * fDeltaTime;
	SetPercent(m_fValue);
}

void UWidget_PlayerSlowMotion::SlowTick_End(float fDeltaTime)
{
	if (m_fValue >= 1.0f)
	{
		
		m_fValue = 1.0f;
		ChangeSlowState(static_cast<int32>(E_State_SlowTime::E_SLOW_NONE));
		return;
	}

	m_fValue += m_fFullSpeed * fDeltaTime;
	SetPercent(m_fValue);
}
