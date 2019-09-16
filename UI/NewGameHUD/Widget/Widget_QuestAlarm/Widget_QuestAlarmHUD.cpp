// Fill out your copyright notice in the Description page of Project Settings.

#include "Widget_QuestAlarmHUD.h"
#include "Widget_QuestAlarm_Item.h"

#include "UI/Core/WidgetAni_Mng.h"
#include "Components/VerticalBox.h"
#include "Kismet/KismetMathLibrary.h"

void UWidget_QuestAlarmHUD::NativePreConstruct()
{
	Super::NativePreConstruct();

}

void UWidget_QuestAlarmHUD::NativeConstruct()
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

	m_pVert_ItemList = Cast<UVerticalBox>(GetWidgetFromName("QuestList"));
	if (m_pVert_ItemList == nullptr)
	{
		ULOG(TEXT("Item is nullptr"));
		return;
	}

	m_pWorldItem = Cast<UWidget_QuestAlarm_Item>(GetWidgetFromName("WorldName"));
	if (m_pWorldItem != nullptr)
	{
		
	}
		
}

void UWidget_QuestAlarmHUD::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	Super::NativeTick(MyGeometry, InDeltaTime);

}

void UWidget_QuestAlarmHUD::NativeDestruct()
{
	Super::NativeDestruct();

	if (m_pWorldItem != nullptr)
	{
		if (m_pWorldItem->IsValidLowLevel())
		{
			m_pWorldItem->RemoveFromParent();
			m_pWorldItem = nullptr;
		}
	}

	if (m_pVert_ItemList != nullptr)
	{
		if (m_pVert_ItemList->IsValidLowLevel())
		{
			m_pVert_ItemList->RemoveFromParent();
			m_pVert_ItemList = nullptr;
		}
	}

	if (m_pWidgetAni != nullptr)
	{
		if (m_pWidgetAni->IsValidLowLevel())
		{
			m_pWidgetAni->Destroy();
			m_pWidgetAni = nullptr;
		}
	}
		
	m_pIconList.Empty();
	m_pQuestItem.Empty();
}

void UWidget_QuestAlarmHUD::SetActive(bool bActive)
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

void UWidget_QuestAlarmHUD::SetPlayAnimation(FString sAniName, bool bRevers)
{
	if (m_pWidgetAni == nullptr) return;
	m_bRevers = bRevers;
	m_pWidgetAni->SetPlayAnimation(sAniName, m_bRevers == true ? EUMGSequencePlayMode::Reverse : EUMGSequencePlayMode::Forward);
}

void UWidget_QuestAlarmHUD::SetWorldName(eQuestIcon eIcon, FText sText)
{
	if (m_pWorldItem == nullptr)
	{
		ULOG(TEXT("Item is nullptr"));
		return;
	}
	m_pWorldItem->SetIcon(GetQuestIcon(eIcon));
	m_pWorldItem->SetText(sText);
	m_pWorldItem->SetActive(true);
}

void UWidget_QuestAlarmHUD::Add_Quest(eQuestIcon eIcon, FText sText)
{	
	APlayerController* pPlayerController = UGameplayStatics::GetPlayerController(GetWorld(), 0);	
	UWidget_QuestAlarm_Item* pObj = CreateWidget<UWidget_QuestAlarm_Item>(pPlayerController, m_pInst_QuestItem);	
	
	if (pObj != nullptr)
	{				
		pObj->AddToViewport();
		pObj->SetIcon(GetQuestIcon(eIcon));
		pObj->SetText(sText);		

		m_pVert_ItemList->AddChildToVerticalBox(pObj);		
		pObj->SetActive(true);

		m_pQuestItem.Add(pObj);
	}	
}

void UWidget_QuestAlarmHUD::Done_Quest(int nIndex, float fDestroyDelay)
{
	m_pQuestItem[nIndex]->Quest_Done(m_pVert_ItemList, nIndex);
	if (fDestroyDelay > 0.0f)
	{
		Destroy_Quest(nIndex, fDestroyDelay);
		return;
	}
}

void UWidget_QuestAlarmHUD::Destroy_Quest(int nIndex, float fDestroyDelay)
{
	if (m_pQuestItem[nIndex]->GetIsQuestDone() == false)
	{
		Done_Quest(nIndex, 1.0f);
		return;
	}
	
	m_pQuestItem[nIndex]->Cor_Destroy();// Quest_Destroy(0.0f);
	m_pQuestItem.RemoveAt(nIndex);

}

bool UWidget_QuestAlarmHUD::DestroyAll_Quest()
{
	for (int i = 0; i < m_pQuestItem.Num(); i++)
	{
		if (m_pQuestItem[i]->GetIsQuestDone() == false)
		{			
			Done_Quest(i, 0.1f);
			/*m_pQuestItem[i]->Quest_Done(m_pVert_ItemList);
			m_pQuestItem[i]->Quest_Destroy(0.3f * (i+1));			*/
			m_pQuestItem[i]->SetQuestItem(m_pQuestItem);
		}
		else
		{
			m_pQuestItem[i]->Quest_Destroy(0.3f * (i + 1));
			m_pQuestItem[i]->SetQuestItem(m_pQuestItem);
		}
	}

	return true;
}

void UWidget_QuestAlarmHUD::SetAlarmItemRoot(const TSubclassOf<UWidget_QuestAlarm_Item> pInstWidget)
{
	m_pInst_QuestItem = pInstWidget;
}

UTexture2D* UWidget_QuestAlarmHUD::GetQuestIcon(eQuestIcon eIcon)
{
	if (m_pIconList.Num() < 0) return nullptr;

	for (int i = 0; i < m_pIconList.Num(); i++)
	{
		if (m_pIconList[i].eIconType == eIcon)
		{
			//ULOG(TEXT("IconName : %s"), *m_pIconList[i].m_pIconImage->GetName());
			return m_pIconList[i].m_pIconImage;
		}
	}

	return nullptr;
}