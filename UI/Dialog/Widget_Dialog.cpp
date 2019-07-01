// Fill out your copyright notice in the Description page of Project Settings.

#include "Widget_Dialog.h"
#include "UI/Core/WidgetAni_Mng.h"
#include "Runtime/UMG/Public/Animation/WidgetAnimation.h"

#include "Components/Image.h"
#include "Components/TextBlock.h"
#include "Components/RichTextBlock.h"

void UWidget_Dialog::NativeConstruct()
{
	Super::NativeConstruct();

	m_pCharImg = Cast<UImage>(GetWidgetFromName(TEXT("CharImg")));
	if (m_pCharImg == nullptr)
	{
		ULOG(TEXT("Error UProgressBar"));
	}

	m_pDialogTxt = Cast<URichTextBlock>(GetWidgetFromName(TEXT("Dialog")));
	if (m_pDialogTxt == nullptr)
	{
		ULOG(TEXT("Error URichTextBlock"));
	}

	m_pNameTxt = Cast<UTextBlock>(GetWidgetFromName(TEXT("Name")));
	if (m_pNameTxt == nullptr)
	{
		ULOG(TEXT("Error UTextBlock"));
	}

	m_pNameSubTxt= Cast<UTextBlock>(GetWidgetFromName(TEXT("SubName")));
	if (m_pNameSubTxt == nullptr)
	{
		ULOG(TEXT("Error UTextBlock"));
	}

	m_pWidgetAni = NewObject<UWidgetAni_Mng>();
	if (m_pWidgetAni != nullptr)
	{
		m_pWidgetAni->Init(this);
	}
}

void UWidget_Dialog::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	Super::NativeTick(MyGeometry, InDeltaTime);

	if (m_bStr == true)
	{
		if (m_sDialogStr.Len() > 0)
		{
			m_fLenTime_Curr += InDeltaTime;
			if (m_fLenTime_Curr >= m_fLenTime_End)
			{
				m_fLenTime_Curr = 0.0f;

				if (m_nStrLen >= m_sDialogStr.Len()-17)
				{					
					SkipDialog();
					return;
				}

				m_sAddStr += FString::Printf(TEXT("%s"), *m_sDialogStr.Mid(m_nStrLen, 1));		
				m_nStrLen++;

			}
			m_pDialogTxt->SetText(FText::FromString(m_sAddStr));
		}
	}
}

bool UWidget_Dialog::SkipDialog()
{
	if (m_bStr == false) return false;

	m_bStr = false;
	m_sAddStr = FString::Printf(TEXT("%s"), *m_sDialogStr);
	m_pDialogTxt->SetText(FText::FromString(m_sAddStr));

	return true;
}

void UWidget_Dialog::SetDialogInit(FString sName, FString sSubName, FString sDialogTxt)
{
	SetNameText(sName);
	SetSubNameText(sSubName);
	SetDialogText(sDialogTxt);
}

void UWidget_Dialog::SetDialogText(FString sText)
{	
	m_sDialogStr.Empty();
	m_sAddStr.Empty();

	m_sDialogStr = sText;	
	m_nStrLen = 0;
	m_bStr = true;
	/*for (int i = 0; i < sText.Len(); i++)
	{
		FString sResult = FString::Printf(TEXT("%s"), *sText.Mid(i, 1));
		m_pDialogTxt->SetText(FText::FromString(sResult));
	}*/

}

void UWidget_Dialog::SetNameText(FString sText)
{
	FString sResult = FString::Printf(TEXT("%s:"), *sText);
	m_pNameTxt->SetText(FText::FromString(sResult));
}

void UWidget_Dialog::SetNameColor(FLinearColor cColor)
{	
	m_pNameTxt->SetColorAndOpacity(cColor);
}

void UWidget_Dialog::SetSubNameText(FString sText)
{
	m_pNameSubTxt->SetText(FText::FromString(sText));
}

void UWidget_Dialog::SetCharImage(class UTexture2D* pTexture)
{	
	if (pTexture != nullptr)
	{
		// 이미지 존재할때
		m_pCharImg->SetVisibility(ESlateVisibility::Visible);
		m_pCharImg->SetBrushFromTexture(pTexture);
		m_pWidgetAni->SetPlayAnimation("YesImg");
	}
	else
	{
		// 이미지 존재하지 않을때
		m_pCharImg->SetVisibility(ESlateVisibility::Hidden);
		m_pWidgetAni->SetPlayAnimation("NoImg");
	}
}

void UWidget_Dialog::SetShow(bool bShow)
{
	if (bShow)
		SetVisibility(ESlateVisibility::Visible);
	else
		SetVisibility(ESlateVisibility::Hidden);
}

void UWidget_Dialog::SetStartAnimation(FString sAniName, bool bRevers)
{
	if ( bRevers == false )
		m_pWidgetAni->SetPlayAnimation(sAniName);
	else
		m_pWidgetAni->SetPlayAnimation(sAniName, EUMGSequencePlayMode::Reverse);
}