// Fill out your copyright notice in the Description page of Project Settings.

#include "Widget_QuestHud.h"
#include "Widget_QuestItem.h"
#include "Components/VerticalBox.h"

void UWidget_QuestHud::NativeConstruct()
{
	Super::NativeConstruct();
	
	if (m_pIconList.Num() <= 0)
	{
		UALERT(TEXT("Quest Icon List is Empty!"));
		return;
	}

	m_pVert_World = Cast<UVerticalBox>(GetWidgetFromName(TEXT("WorldList")));
	if (m_pVert_World == nullptr)
	{
		ULOG(TEXT("VerticalBox is nullptr"));
		return;
	}

	m_pVert_Item = Cast<UVerticalBox>(GetWidgetFromName(TEXT("QuestList")));
	if (m_pVert_Item == nullptr)
	{
		ULOG(TEXT("VerticalBox is nullptr"));
		return;
	}	
}

void UWidget_QuestHud::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	Super::NativeTick(MyGeometry, InDeltaTime);

}

void UWidget_QuestHud::NativeDestruct()
{
	Super::NativeDestruct();

}

void UWidget_QuestHud::Add_WorldList(class UWidget_QuestItem* pItem)
{
	if (m_pIconList.Num() <= 0) return;
	if (m_pVert_World != nullptr)
	{
		for (int i = 0; i < m_pIconList.Num(); i++)
		{
			if (m_pIconList[i].eIconType == pItem->GetIconState())
			{
				pItem->SetImage_Icon(m_pIconList[i].m_pIconImage);
				break;
			}
		}
		m_pVert_World->AddChild(pItem);		
	}
}

void UWidget_QuestHud::Add_ItemList(class UWidget_QuestItem* pItem)
{
	if (m_pIconList.Num() <= 0) return;
	if (m_pVert_Item != nullptr)
	{
		for (int i = 0; i < m_pIconList.Num(); i++)
		{
			if (m_pIconList[i].eIconType == pItem->GetIconState())
			{
				pItem->SetImage_Icon(m_pIconList[i].m_pIconImage);
				break;
			}
		}
		m_pVert_Item->AddChild(pItem);
	}
}

void UWidget_QuestHud::Remove_ItemList(class UWidget_QuestItem* pItem)
{
	if (m_pVert_Item != nullptr)
	{
		m_pVert_Item->RemoveChild(pItem);
	}
}

void UWidget_QuestHud::Remove_ItemListIndex(int32 nIndex)
{
	if (m_pVert_Item != nullptr)
	{
		m_pVert_Item->RemoveChildAt(nIndex);
	}
}
