// Fill out your copyright notice in the Description page of Project Settings.

#include "Widget_StageIntro.h"
#include "UI/Core/WidgetAni_Mng.h"
#include "Runtime/UMG/Public/Animation/WidgetAnimation.h"

#include "Components/Image.h"
#include "Components/TextBlock.h"
#include "Components/RichTextBlock.h"
#include "Kismet/KismetMathLibrary.h"

void UWidget_StageIntro::NativeConstruct()
{
	Super::NativeConstruct();

	m_pTitleTxt = Cast<URichTextBlock>(GetWidgetFromName(TEXT("Title")));
	if (m_pTitleTxt == nullptr)
	{
		ULOG(TEXT("Error UProgressBar"));
	}

	m_pWidgetAni = NewObject<UWidgetAni_Mng>();
	if (m_pWidgetAni != nullptr)
	{
		m_pWidgetAni->Init(this);
	}
	m_bRevers = false;
	m_bActive = false;
}

void UWidget_StageIntro::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	Super::NativeTick(MyGeometry, InDeltaTime);


}

void UWidget_StageIntro::SetActive(bool bActive)
{
	m_bActive = bActive;
	bActive == false ? SetVisibility(ESlateVisibility::Hidden) : SetVisibility(ESlateVisibility::Visible);
}

void UWidget_StageIntro::SetTitleText(FText sText)
{
	m_pTitleTxt->SetText(sText);
}

void UWidget_StageIntro::SetDestroy()
{
	if (m_bRevers == false) return;
	SetActive(false);
}

void UWidget_StageIntro::SetAnimation(FString sAniName, bool bRevers)
{
	if (m_pWidgetAni == nullptr) return;
	SetActive(true);

	m_bRevers = bRevers;	
	m_pWidgetAni->SetPlayAnimation(sAniName, bRevers == true ? EUMGSequencePlayMode::Reverse : EUMGSequencePlayMode::Forward);
}
