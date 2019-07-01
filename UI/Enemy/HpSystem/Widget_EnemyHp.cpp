// Fill out your copyright notice in the Description page of Project Settings.

#include "Widget_EnemyHp.h"
#include "UI/Core/WidgetAni_Mng.h"
#include "Runtime/UMG/Public/Animation/WidgetAnimation.h"

#include "Styling/SlateBrush.h"
#include "Materials/MaterialInstanceDynamic.h"
#include "Materials/MaterialInterface.h"
#include "Kismet/KismetMathLibrary.h"

void UWidget_EnemyHp::NativeConstruct()
{
	Super::NativeConstruct();

	m_pHp = Cast<UProgressBar>(GetWidgetFromName(TEXT("HP")));
	if (m_pHp == nullptr)
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

	m_bActive = true;
	m_bHit = false;
}

void UWidget_EnemyHp::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	Super::NativeTick(MyGeometry, InDeltaTime);

}

void UWidget_EnemyHp::SetActive(bool bActive)
{
	m_bActive = bActive;
	if (bActive)
	{
		SetVisibility(ESlateVisibility::Visible);
		SetPlayAnimation("Start");
	}
	else
	{
		SetPlayAnimation("Destroy");
		//SetVisibility(ESlateVisibility::Hidden);
	}
}

void UWidget_EnemyHp::SetPlayAnimation(FString sAniName, bool bRevers)
{
	if (m_pWidgetAni == nullptr) return;
	m_bRevers = bRevers;
	m_pWidgetAni->SetPlayAnimation(sAniName, m_bRevers == true ? EUMGSequencePlayMode::Reverse : EUMGSequencePlayMode::Forward);
}

void UWidget_EnemyHp::SetHit(bool bNoHit)
{
	m_bHit = !bNoHit;
	if (bNoHit)
	{
		m_pHp->SetPercent(1.0f);
	}
	else
	{
		m_pHp->SetPercent(0.0f);
		SetPlayAnimation("Hit");
	}
}

void UWidget_EnemyHp::SetDestroy()
{
	m_pWidgetAni->SetPlayAnimation("Destroy");
}