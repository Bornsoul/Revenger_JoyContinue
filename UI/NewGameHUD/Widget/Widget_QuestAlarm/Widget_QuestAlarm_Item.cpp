// Fill out your copyright notice in the Description page of Project Settings.

#include "Widget_QuestAlarm_Item.h"
#include "UI/Core/WidgetAni_Mng.h"
#include "Components/Image.h"
#include "Components/TextBlock.h"
#include "Components/VerticalBox.h"
#include "Kismet/KismetMathLibrary.h"
#include "Runtime/Engine/Classes/Engine/Texture2D.h"

void UWidget_QuestAlarm_Item::NativeConstruct()
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

	m_pImg_Icon = Cast<UImage>(GetWidgetFromName(TEXT("IconImg")));
	if (m_pImg_Icon == nullptr)
	{
		ULOG(TEXT("IconImg is nullptr"));
		return;
	}

	m_pTxt_Text = Cast<UTextBlock>(GetWidgetFromName(TEXT("TextInfo")));
	if (m_pTxt_Text == nullptr)
	{
		ULOG(TEXT("TextInfo is nullptr"));
		return;
	}


	m_bDone = false;
	m_bDestroyed = false;
}

void UWidget_QuestAlarm_Item::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	Super::NativeTick(MyGeometry, InDeltaTime);

}

void UWidget_QuestAlarm_Item::NativeDestruct()
{
	if (m_pWidgetAni != nullptr)
	{
		if (m_pWidgetAni->IsValidLowLevel())
		{
			m_pWidgetAni->Destroy();
			m_pWidgetAni = nullptr;
		}
	}

	if (m_pTxt_Text != nullptr)
	{
		if (m_pTxt_Text->IsValidLowLevel())
		{
			m_pTxt_Text = nullptr;
		}
	}

	if (m_pImg_Icon != nullptr)
	{
		if (m_pImg_Icon->IsValidLowLevel())
		{
			m_pImg_Icon = nullptr;
		}
	}

	m_pQuestItem.Empty();
	m_pVertBoxList.Empty();
	//GetOwningPlayer()->GetWorldTimerManager().ClearAllTimersForObject();
	//GetOwningPlayer()->GetWorldTimerManager().ClearTimer(m_pDestroyTimer);
}

void UWidget_QuestAlarm_Item::SetActive(bool bActive)
{
	m_bActive = bActive;

	if (m_bActive)
	{
		GetRootWidget()->SetVisibility(ESlateVisibility::Visible);
		SetPlayAnimation("Start");
	}
	else
	{
		m_bDestroyed = true;

		GetOwningPlayer()->GetWorldTimerManager().ClearTimer(m_pDestroyTimer);

		if (m_nVertIndex >= 0)
		{
			m_pVertBoxList[0]->RemoveChildAt(m_nVertIndex);
			m_pQuestItem.RemoveAt(m_nVertIndex);
		}
		else
		{
			m_pVertBoxList[0]->RemoveChildAt(0);
			m_pQuestItem.RemoveAt(0);
		}

		GetRootWidget()->SetVisibility(ESlateVisibility::Hidden);		
		
		if (m_pWidgetAni)
		{
			if (m_pWidgetAni->IsValidLowLevel())
			{
				m_pWidgetAni = nullptr;
			}
		}

		if (m_pImg_Icon)
		{
			if (m_pImg_Icon->IsValidLowLevel())
			{
				m_pImg_Icon = nullptr;
			}
		}

		if (m_pTxt_Text)
		{
			if (m_pTxt_Text->IsValidLowLevel())
			{
				m_pTxt_Text = nullptr;
			}
		}

		if (GetRootWidget())
		{
			if (GetRootWidget()->IsValidLowLevel())
			{
				GetRootWidget()->RemoveFromParent();
			}
		}

	}
}

void UWidget_QuestAlarm_Item::SetPlayAnimation(FString sAniName, bool bRevers)
{
	if (m_pWidgetAni == nullptr) return;
	m_bRevers = bRevers;
	m_pWidgetAni->SetPlayAnimation(sAniName, m_bRevers == true ? EUMGSequencePlayMode::Reverse : EUMGSequencePlayMode::Forward);
}

void UWidget_QuestAlarm_Item::SetIcon(UTexture2D* pTextrue)
{
	if (m_pImg_Icon == nullptr)
	{
		ULOG(TEXT("m_pImg_Icon is nullptr"));
		return;
	}
	m_pImg_Icon->SetBrushFromTexture(pTextrue, true);
}

void UWidget_QuestAlarm_Item::SetText(FText sText)
{
	if (m_pTxt_Text == nullptr)
	{
		ULOG(TEXT("m_pTxt_Text is nullptr"));
		return;
	}

	m_pTxt_Text->SetText(sText);
}

void UWidget_QuestAlarm_Item::Quest_Done(class UVerticalBox* pVertBox, int nIndex)
{
	if (m_pWidgetAni == nullptr) return;

	if (pVertBox)
	{
		m_pVertBoxList.Add(pVertBox); 
	}

	if (nIndex >= 0)
	{
		m_nVertIndex = nIndex;
	}
	SetPlayAnimation("End");

	m_bDone = true;

}

void UWidget_QuestAlarm_Item::Quest_Destroy(float fDestroyDelay)
{
	if (m_pWidgetAni == nullptr) return;

	GetOwningPlayer()->GetWorldTimerManager().SetTimer(m_pDestroyTimer, this, &UWidget_QuestAlarm_Item::Cor_Destroy, fDestroyDelay, false);	
}

void UWidget_QuestAlarm_Item::Cor_Destroy()
{
	SetPlayAnimation("Destroy");
	GetOwningPlayer()->GetWorldTimerManager().ClearTimer(m_pDestroyTimer);
}

void UWidget_QuestAlarm_Item::SetQuestItem(TArray<UWidget_QuestAlarm_Item*> &pQuestItem)
{
	m_pQuestItem.Empty();
	m_pQuestItem = pQuestItem;
}
