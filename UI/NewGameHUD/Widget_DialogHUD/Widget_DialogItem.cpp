#include "Widget_DialogItem.h"
#include "Components/Image.h"
#include "Components/RichTextBlock.h"
#include "UI/Core/WidgetAni_Mng.h"
#include "Engine/Texture2D.h"
#include "Kismet/KismetMathLibrary.h"

void UWidget_DialogItem::NativePreConstruct()
{
	Super::NativePreConstruct();

}

void UWidget_DialogItem::NativeConstruct()
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

	m_pImg_Icon = Cast<UImage>(GetWidgetFromName(TEXT("Img_Icon")));
	if (m_pImg_Icon == nullptr)

	if (m_pImgList.Num() >= 2)
	{
		if (m_bImageList_Random == true)
		{
			//! 만약 이미지가 2개 이상이면 랜덤으로 출력
			int32 nRand = FMath::RandRange(0, m_pImgList.Num() - 1);
			m_pImg_Icon->SetBrushFromTexture(m_pImgList[nRand]);
		}
	}
	else if (m_pImgList.Num() > 0)
	{
		m_pImg_Icon->SetVisibility(ESlateVisibility::Visible);
		m_pImg_Icon->SetBrushFromTexture(m_pImgList[0]);
	}
	else
	{
		m_pImg_Icon->SetVisibility(ESlateVisibility::Hidden);
	}

	m_pRich_Name = Cast<URichTextBlock>(GetWidgetFromName(TEXT("Rich_Name")));
	if (m_pRich_Name == nullptr) return;
	m_pRich_Name->SetText(m_sName);

	m_pRich_Text = Cast<URichTextBlock>(GetWidgetFromName(TEXT("Rich_Text")));
	if (m_pRich_Text == nullptr) return;
	m_pRich_Text->SetText(m_sText);

	SetActive(true);
}

void UWidget_DialogItem::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	Super::NativeTick(MyGeometry, InDeltaTime);

	Tick_StringDialog(InDeltaTime);

}

void UWidget_DialogItem::SetPlayAnimation(FString sAniName, bool bRevers)
{
	if (m_pWidgetAni == nullptr) return;
	m_bRevers = bRevers;
	m_pWidgetAni->SetPlayAnimation(sAniName, m_bRevers == true ? EUMGSequencePlayMode::Reverse : EUMGSequencePlayMode::Forward);
}

void UWidget_DialogItem::SetActive(bool bActive)
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

void UWidget_DialogItem::SetDialogData(bool bRandom, TArray<class UTexture2D*> pTextures, FText sName, FText sNameSub, FText sText)
{
	if (m_pImg_Icon == nullptr)
	if (m_pRich_Name == nullptr) return;
	if (m_pRich_Text == nullptr) return;

	SetPlayAnimation("Start");

	m_bImageList_Random = bRandom;
	m_pImgList.Empty();
	m_pImgList = pTextures;
	m_sName = sName;
	m_sNameSub = sNameSub;
	m_sText = sText;
	
	if (m_pImgList.Num() >= 2)
	{
		if (m_bImageList_Random == true)
		{
			//! 만약 이미지가 2개 이상이면 랜덤으로 출력
			int32 nRand = FMath::RandRange(0, m_pImgList.Num() - 1);
			m_pImg_Icon->SetBrushFromTexture(m_pImgList[nRand]);
		}
	}
	else if (m_pImgList.Num() > 0)
	{
		m_pImg_Icon->SetVisibility(ESlateVisibility::Visible);
		m_pImg_Icon->SetBrushFromTexture(m_pImgList[0]);
	}
	else
	{
		m_pImg_Icon->SetVisibility(ESlateVisibility::Hidden);
	}
	
	m_pRich_Name->SetText(m_sName);
	Execute_StringDialog(sText.ToString());
}

void UWidget_DialogItem::Execute_StringDialog(FString sDialog)
{
	m_bStoryDialog = true;
	m_sDialogText.Empty();
	m_sDialogAddText.Empty();
	m_sDialogText = sDialog;

	m_fStoryDialog_Curr = 0.0f;
	m_nDialogStrLen = 0;
}

void UWidget_DialogItem::Tick_StringDialog(float fDeltaTime)
{
	if (m_bStoryDialog == true)
	{
		if (m_sDialogText.Len() > 0)
		{
			m_fStoryDialog_Curr += fDeltaTime;
			if (m_fStoryDialog_Curr >= m_fStoryDialog_End)
			{
				m_fStoryDialog_Curr = 0.0f;

				if (m_nDialogStrLen >= m_sDialogText.Len())
				{
					Skip_Dialog();
					return;
				}

				m_sDialogAddText += FString::Printf(TEXT("%s"), *m_sDialogText.Mid(m_nDialogStrLen, 1));
				m_nDialogStrLen++;

			}
			m_pRich_Text->SetText(FText::FromString(m_sDialogAddText));
		}
	}
}

bool UWidget_DialogItem::Skip_Dialog()
{
	if (m_bStoryDialog == false) return false;

	m_bStoryDialog = false;
	m_pRich_Text->SetText(FText::FromString(m_sDialogText));

	return true;
}
