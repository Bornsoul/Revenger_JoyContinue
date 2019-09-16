// Fill out your copyright notice in the Description page of Project Settings.

#include "Widget_DialogHUD.h"
#include "UI/Core/WidgetAni_Mng.h"
#include "Widget_DialogItem.h"
#include "Runtime/MediaAssets/Public/MediaPlayer.h"
#include "Runtime/MediaAssets/Public/MediaSource.h"
#include "Components/Image.h"
#include "Kismet/KismetMathLibrary.h"

void UWidget_DialogHUD::NativePreConstruct()
{
	Super::NativePreConstruct();

}

void UWidget_DialogHUD::NativeConstruct()
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

	m_pDialogItem = Cast<UWidget_DialogItem>(GetWidgetFromName(TEXT("DialogItem")));
	if (m_pDialogItem == nullptr)
	{
		ULOG(TEXT("DialogItem is Nullptr"));
		return;
	}

	m_pImg_Media = Cast<UImage>(GetWidgetFromName(TEXT("Media")));
	if (m_pImg_Media == nullptr)
	{
		ULOG(TEXT("nullptr"));
		return;
	}
	m_pImg_Media->SetVisibility(ESlateVisibility::Hidden);

	
	//SetPlayAnimation("Start");
}

void UWidget_DialogHUD::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	Super::NativeTick(MyGeometry, InDeltaTime);

}

void UWidget_DialogHUD::NativeDestruct()
{
	Super::NativeDestruct();

	if (m_pWidgetAni != nullptr)
	{
		if (m_pWidgetAni->IsValidLowLevel())
		{
			//m_pWidgetAni->ConditionalBeginDestroy();
			m_pWidgetAni = nullptr;
		}
	}

	if (m_pDialogItem != nullptr)
	{
		if (m_pDialogItem->IsValidLowLevel())
		{
			m_pDialogItem->RemoveFromParent();
			//m_pDialogItem->ConditionalBeginDestroy();
			m_pDialogItem = nullptr;
		}
	}

	if (m_pImg_Media != nullptr)
	{
		if (m_pImg_Media->IsValidLowLevel())
		{
			//m_pImg_Media->RemoveFromParent();
			//m_pImg_Media->ConditionalBeginDestroy();
			m_pImg_Media = nullptr;
		}
	}

	if (m_pMediaPlayer != nullptr)
	{
		if (m_pMediaPlayer->IsValidLowLevel())
		{
			//m_pMediaPlayer->ConditionalBeginDestroy();
			m_pMediaPlayer = nullptr;
		}
	}
}

void UWidget_DialogHUD::SetActive(bool bActive)
{
	m_bActive = bActive;

	if (m_bActive)
	{
		GetRootWidget()->SetVisibility(ESlateVisibility::Visible);
		SetPlayAnimation("Start");
	}
	else
	{
		GetRootWidget()->SetVisibility(ESlateVisibility::Hidden);
	}
	
}

void UWidget_DialogHUD::SetPlayAnimation(FString sAniName, bool bRevers)
{
	if (m_pWidgetAni == nullptr)
	{
		return;
	}

	m_bRevers = bRevers;
	m_pWidgetAni->SetPlayAnimation(sAniName, m_bRevers == true ? EUMGSequencePlayMode::Reverse : EUMGSequencePlayMode::Forward);
}

void UWidget_DialogHUD::SetDialogData(bool bRandom, TArray<class UTexture2D*> pTextures, FText sName, FText sNameSub, FText sText)
{
	if (m_pDialogItem == nullptr) return;

	m_pDialogItem->SetDialogData(bRandom, pTextures, sName, sNameSub, sText);
}

void UWidget_DialogHUD::Skip_Dialog()
{
	m_pDialogItem->Skip_Dialog();
}

void UWidget_DialogHUD::SetMediaData(UMaterial* pMat, UMediaSource* pMediaSource)
{
	if (pMat == nullptr) return;

	m_pMediaPlayer->Pause();
	m_pMediaPlayer->OpenSource(pMediaSource);
	m_pMediaPlayer->Play();
	
	m_pImg_Media->SetVisibility(ESlateVisibility::Visible);
	m_pImg_Media->SetBrushFromMaterial(pMat);
	SetPlayAnimation("MediaStart");

	//ULOG(TEXT("Vedio : %s"), *pMediaSource->GetName());
	
}

bool UWidget_DialogHUD::GetIsPlaying()
{
	if (m_pDialogItem == nullptr) return false;
		
	return m_pDialogItem->GetDialogPlaying();
}
void UWidget_DialogHUD::SetDialogTextSpeed(float fSpeed)
{
	if (m_pDialogItem == nullptr) return;

	m_pDialogItem->SetDialogTextSpeed(fSpeed);
}

void UWidget_DialogHUD::SetDialogCount(int32 nCurCount, int32 nMaxCount)
{
	if (m_pDialogItem == nullptr) return;

	//UALERT(TEXT("%d / %d"), nCurCount, nMaxCount);
	m_pDialogItem->SetCountText(nCurCount, nMaxCount);
}
