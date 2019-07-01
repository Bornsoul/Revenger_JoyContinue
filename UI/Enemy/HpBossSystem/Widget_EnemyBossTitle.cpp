// Fill out your copyright notice in the Description page of Project Settings.

#include "Widget_EnemyBossTitle.h"
#include "UI/Core/WidgetAni_Mng.h"
#include "Runtime/UMG/Public/Animation/WidgetAnimation.h"

#include "Components/RichTextBlock.h"

#include "Styling/SlateBrush.h"
#include "Kismet/KismetMathLibrary.h"

void UWidget_EnemyBossTitle::NativeConstruct()
{
	Super::NativeConstruct();

	m_pTitle = Cast<URichTextBlock>(GetWidgetFromName(TEXT("Title")));
	if (m_pTitle == nullptr)
	{
		ULOG(TEXT("Error URichTextBlock"));
	}

	m_pSubTitle = Cast<URichTextBlock>(GetWidgetFromName(TEXT("SubTitle")));
	if (m_pSubTitle == nullptr)
	{
		ULOG(TEXT("Error URichTextBlock"));
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

}

void UWidget_EnemyBossTitle::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	Super::NativeTick(MyGeometry, InDeltaTime);

}

void UWidget_EnemyBossTitle::SetTextInit(FString sTitle, FString sSubTitle)
{
	SetText_Title(sTitle);
	SetText_SubTitle(sSubTitle);
}

void UWidget_EnemyBossTitle::SetText_Title(FString sText)
{
	FString sResult = FString::Printf(TEXT("%s"), *sText);
	m_pTitle->SetText(FText::FromString(sResult));
}

void UWidget_EnemyBossTitle::SetText_SubTitle(FString sText)
{
	FString sResult = FString::Printf(TEXT("%s"), *sText);
	m_pSubTitle->SetText(FText::FromString(sResult));
}

void UWidget_EnemyBossTitle::SetActive(bool bActive)
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

void UWidget_EnemyBossTitle::SetPlayAnimation(FString sAniName, bool bRevers)
{
	if (m_pWidgetAni == nullptr) return;
	m_bRevers = bRevers;
	m_pWidgetAni->SetPlayAnimation(sAniName, m_bRevers == true ? EUMGSequencePlayMode::Reverse : EUMGSequencePlayMode::Forward);
}

void UWidget_EnemyBossTitle::SetHit(bool bNoHit)
{
	m_bHit = !bNoHit;
	if (bNoHit)
	{
	}
	else
	{
		SetPlayAnimation("Hit");
	}
}