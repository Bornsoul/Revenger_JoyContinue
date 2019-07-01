// Fill out your copyright notice in the Description page of Project Settings.

#include "Widget_ResultHUD.h"
#include "Widget/Widget_Result_Item.h"
#include "Widget/Widget_Result_ButtonItem.h"
#include "Widget/Widget_Result_GoodItem.h"

void UWidget_ResultHUD::NativePreConstruct()
{
	Super::NativePreConstruct();

}

void UWidget_ResultHUD::NativeConstruct()
{
	Super::NativeConstruct();

	for (int32 i = 0; i < m_pItemList.Num(); i++)
	{
		FString sText = "Result_Item" + FString::FromInt(i);
		m_pItemList[i] = Cast<UWidget_Result_Item>(GetWidgetFromName(*sText));
		m_pItemList[i]->SetResultTitle(m_pItemTitleList[i]);
		m_pItemList[i]->SetActive(false);		
	}

	for (int32 i = 0; i < m_pButtonItemList.Num(); i++)
	{
		FString sText = "Btn" + FString::FromInt(i);
		m_pButtonItemList[i] = Cast<UWidget_Result_ButtonItem>(GetWidgetFromName(*sText));
		m_pButtonItemList[i]->SetTitle(m_pButtonTitleList[i]);
		m_pButtonItemList[i]->SetActive(false);
	}

	m_pGoodItem = Cast<UWidget_Result_GoodItem>(GetWidgetFromName(TEXT("GoodItem")));
	if (m_pGoodItem == nullptr) return;
	m_pGoodItem->SetActive(false);

	SetActive(false);
}

void UWidget_ResultHUD::NativeDestruct()
{
	Super::NativeDestruct();

	for (int32 i = 0; i < m_pItemList.Num(); i++)
	{
		if (m_pItemList[i] != nullptr)
		{
			if (m_pItemList[i]->IsValidLowLevel())
			{
				m_pItemList[i]->ConditionalBeginDestroy();
				m_pItemList[i] = nullptr;
			}
		}
	}

	for (int32 i = 0; i < m_pButtonItemList.Num(); i++)
	{
		if (m_pButtonItemList[i] != nullptr)
		{
			if (m_pButtonItemList[i]->IsValidLowLevel())
			{
				m_pButtonItemList[i]->ConditionalBeginDestroy();
				m_pButtonItemList[i] = nullptr;
			}
		}
	}

	GetWorld()->GetTimerManager().ClearTimer(m_pTimer_Item);
	GetWorld()->GetTimerManager().ClearAllTimersForObject(this);
}

void UWidget_ResultHUD::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	Super::NativeTick(MyGeometry, InDeltaTime);

	for (int32 i = 0; i < m_pButtonItemList.Num(); i++)
	{
		if (m_pButtonItemList[i] != nullptr)
		{
			if (m_pButtonItemList[i]->GetButtonDown() == true)
			{
				if (m_pButtonItemList[i]->GetName() == "Btn0")
				{
					Button_SelectStage();
					return;
				}
				else if(m_pButtonItemList[i]->GetName() == "Btn1")
				{
					Button_NextStage();
					return;
				}
			}
		}
	}
	if (m_bGoodTick == true)
	{
		if (m_pGoodItem != nullptr)
		{
			if (m_pItemList[m_pItemList.Num() - 1]->GetAniDone() == true)
			{
				m_pGoodItem->SetActive(true);
				m_bGoodTick = false;
				m_bResultDone = true;
				return;
			}
		}
	}
}

void UWidget_ResultHUD::SetActive(bool bActive)
{
	m_bActive = bActive;

	if (m_bActive == true)
	{
		GetRootWidget()->SetVisibility(ESlateVisibility::Visible);
	}
	else
	{
		GetRootWidget()->SetVisibility(ESlateVisibility::Hidden);
	}
}

void UWidget_ResultHUD::Active_HUD()
{
	for (int32 i = 0; i < m_pItemList.Num(); i++)
	{
		if (m_pItemList[i] != nullptr)
		{
			m_pItemList[i]->SetActive(false);
		}
	}

	for (int32 i = 0; i < m_pButtonItemList.Num(); i++)
	{
		if (m_pButtonItemList[i] != nullptr)
		{
			m_pButtonItemList[i]->SetActive(false);
		}
	}

	m_bGoodTick = true;
	m_bResultDone = false;
	m_nItemCount = 0;
	GetWorld()->GetTimerManager().SetTimer(m_pTimer_Item, this, &UWidget_ResultHUD::Cor_ItemActive, m_fItemSpawnTime, true);
}

void UWidget_ResultHUD::DeActive_HUD()
{
	for (int32 i = 0; i < m_pItemList.Num(); i++)
	{
		if (m_pItemList[i] != nullptr)
		{
			m_pItemList[i]->SetPlayAnimation("End", true);
		}
	}

	for (int32 i = 0; i < m_pButtonItemList.Num(); i++)
	{
		if (m_pButtonItemList[i] != nullptr)
		{
			m_pButtonItemList[i]->SetPlayAnimation("End", true);
		}
	}

	m_pGoodItem->SetPlayAnimation("End", true);
}

bool UWidget_ResultHUD::SetItemResult_Text(TArray<FString> pItemTextList)
{
	if (m_pItemList.Num() != pItemTextList.Num())
	{
		ULOG(TEXT("ItemList != ItemResult is not match"));
		return false;
	}

	for (int32 i = 0; i < m_pItemList.Num(); i++)
	{
		if (m_pItemList[i] != nullptr)
		{
			m_pItemList[i]->SetResultText(pItemTextList[i]);
		}
	}

	return true;
}

void UWidget_ResultHUD::Cor_ItemActive()
{
	if (m_nItemCount >= m_pItemList.Num() || m_pItemList[m_nItemCount] == nullptr)
	{
		GetWorld()->GetTimerManager().ClearTimer(m_pTimer_Item);
		SetButtonActive();
		return;
	}

 	m_pItemList[m_nItemCount]->SetActive(true);
 	m_pItemList[m_nItemCount]->SetPlayAnimation("Start");

	m_nItemCount++;
}

void UWidget_ResultHUD::SetButtonActive()
{
	for (int32 i = 0; i < m_pButtonItemList.Num(); i++)
	{
		if (m_pButtonItemList[i] != nullptr)
		{
			m_pButtonItemList[i]->SetPlayAnimation("Start");
		}
	}
}

void UWidget_ResultHUD::Button_NextStage()
{
	UGameplayStatics::OpenLevel(GetWorld(), TEXT("Stage_1"), true);
	ULOG(TEXT("Button_NextStage"));
}

void UWidget_ResultHUD::Button_SelectStage()
{
	UGameplayStatics::OpenLevel(GetWorld(), TEXT("Stage_1"), true);
	ULOG(TEXT("Button_SelectStage"));
}