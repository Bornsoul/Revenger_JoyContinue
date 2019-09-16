// Fill out your copyright notice in the Description page of Project Settings.

#include "Widget_KeyInputHUD.h"
#include "Widget_KeyInputItem.h"
#include "Components/HorizontalBox.h"
#include "Components/TextBlock.h"

void UWidget_KeyInputHUD::NativeConstruct()
{
	Super::NativeConstruct();

	m_pHoriBox = Cast<UHorizontalBox>(GetWidgetFromName(TEXT("Hori_Item")));
	if (m_pHoriBox == nullptr)
	{
		ULOG(TEXT("HorizontalBox is nullptr"));
		return;
	}

	m_pTxt_Title = Cast<UTextBlock>(GetWidgetFromName(TEXT("Title")));
	if (m_pTxt_Title == nullptr)
	{
		ULOG(TEXT("Text is nullptr"));
		return;
	}

	m_pTxt_SubTitle = Cast<UTextBlock>(GetWidgetFromName(TEXT("SubTitle")));
	if (m_pTxt_SubTitle == nullptr)
	{
		ULOG(TEXT("Text is nullptr"));
		return;
	}

}

void UWidget_KeyInputHUD::NativeDestruct()
{
	Super::NativeDestruct();
	
	if (m_pHoriBox != nullptr)
	{
		if (m_pHoriBox->IsValidLowLevel())
		{
			m_pHoriBox->ClearChildren();			
			m_pHoriBox = nullptr;
		}
	}

	if (m_pTxt_Title != nullptr)
	{
		if (m_pTxt_Title->IsValidLowLevel())
		{
			m_pTxt_Title = nullptr;
		}
	}

	if (m_pTxt_SubTitle != nullptr)
	{
		if (m_pTxt_SubTitle->IsValidLowLevel())
		{
			m_pTxt_SubTitle = nullptr;
		}
	}	

	m_pKeyItemList.Empty();
	m_stInputName.Empty();
	
}

void UWidget_KeyInputHUD::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	Super::NativeTick(MyGeometry, InDeltaTime);

}

UTexture2D* UWidget_KeyInputHUD::GetChangeKeyName(FText sKeyName)
{
	
	for (int i = 0; i < m_stInputName.Num(); i++)
	{
		if (m_stInputName[i].m_sOriginalName_Kor.ToString() == sKeyName.ToString() ||
			m_stInputName[i].m_sOriginalName_Eng.ToString() == sKeyName.ToString())
		{
			return m_stInputName[i].m_pTexture;
		}
	}

	return nullptr;	
}

void UWidget_KeyInputHUD::DestroyItemChild()
{
	if (m_pHoriBox != nullptr)
	{
		m_pHoriBox->ClearChildren();
		m_pKeyItemList.Empty();
	}

	m_bKeyInputSuccess = true;
}

void UWidget_KeyInputHUD::SetTitleAndSubTitle(const FText sTitle, const FText sSubTitle)
{
	if (m_pTxt_SubTitle == nullptr || m_pTxt_Title == nullptr)
	{
		ULOG(TEXT("Text is nullptr"));
		return;
	}

	m_pTxt_Title->SetText(sTitle);
	m_pTxt_SubTitle->SetText(sSubTitle);
	m_bKeyInputSuccess = false;
}

class UWidget_KeyInputItem* UWidget_KeyInputHUD::Create_KeyItem(const FText sKeyName)
{
	APlayerController* pController = UGameplayStatics::GetPlayerController(GetWorld(), 0);

	if (m_pInst_KeyItem != nullptr)
	{
		UWidget_KeyInputItem* pObj = CreateWidget<UWidget_KeyInputItem>(pController, m_pInst_KeyItem);
		if (pObj != nullptr)
		{
			pObj->AddToViewport();
			pObj->SetKeyText(sKeyName, GetChangeKeyName(sKeyName));
			pObj->SetPlayAnimation("Start");
			m_pHoriBox->AddChildToHorizontalBox(pObj);	

			m_pKeyItemList.Add(pObj);
			return pObj;
		}
	}

	return nullptr;
}

bool UWidget_KeyInputHUD::Success_KeyInput(const FText sKeyName)
{
	if (m_pKeyItemList.Num() <= 0)
	{
		ULOG(TEXT("KeyItem Count is 0"));
		return false;
	}

	for (int i = 0; i < m_pKeyItemList.Num(); i++)
	{
		if (m_pKeyItemList[i]->GetKeyText().ToString() == sKeyName.ToString())
		{			
			m_pKeyItemList[i]->SetPlayAnimation("Pass");
			return true;
		}
	}

	return false;
}

bool UWidget_KeyInputHUD::Fail_KeyInput(const FText sKeyName)
{
	if (m_pKeyItemList.Num() <= 0)
	{
		ULOG(TEXT("KeyItem Count is 0"));
		return false;
	}

	for (int i = 0; i < m_pKeyItemList.Num(); i++)
	{
		if (m_pKeyItemList[i]->GetKeyText().ToString() == sKeyName.ToString())
		{
			m_pKeyItemList[i]->SetPlayAnimation("Pass", true);
			return true;
		}
	}

	return false;
}
