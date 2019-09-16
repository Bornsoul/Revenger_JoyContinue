// Fill out your copyright notice in the Description page of Project Settings.

#include "Cpt_QuestMng.h"
#include "Widget_QuestHud.h"
#include "Widget_QuestItem.h"

UCpt_QuestMng::UCpt_QuestMng()
{
	PrimaryComponentTick.bCanEverTick = true;

	static ConstructorHelpers::FObjectFinder<UClass> Const_Hud(TEXT("/Game/1_Project_Main/1_Blueprints/UI/NEW/Widgets/QuestAlarm_Widget/BP_Widget_QuestAlarmHUD.BP_Widget_QuestAlarmHUD_C"));
	if (Const_Hud.Succeeded())
	{
		m_pInst_Hud = Const_Hud.Object;
	}

	static ConstructorHelpers::FObjectFinder<UClass> Const_Item(TEXT("/Game/1_Project_Main/1_Blueprints/UI/NEW/Widgets/QuestAlarm_Widget/BP_Widget_QuestAlarmItem.BP_Widget_QuestAlarmItem_C"));
	if (Const_Item.Succeeded())
	{
		m_pInst_Item = Const_Item.Object;
	}
}

void UCpt_QuestMng::BeginPlay()
{
	Super::BeginPlay();

	m_pController = UGameplayStatics::GetPlayerController(GetWorld(), 0);
	if (m_pController == nullptr)
	{
		ULOG(TEXT("Controller is nullptr"));
		return;
	}
}

void UCpt_QuestMng::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	Super::EndPlay(EndPlayReason);

	m_pItemList.Empty();
	if (m_pHud != nullptr)
	{
		if (m_pHud->IsValidLowLevel())
		{
			m_pHud->RemoveFromParent();
			m_pHud = nullptr;
		}
	}
}

void UCpt_QuestMng::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

}

void UCpt_QuestMng::SetVisible(bool bVisible)
{
	if (bVisible) 
	{
		m_pHud->SetVisibility(ESlateVisibility::SelfHitTestInvisible);
	}
	else
	{
		m_pHud->SetVisibility(ESlateVisibility::Hidden);		
	}
}

void UCpt_QuestMng::HideHud()
{
	if (m_pHud != nullptr)
	{
		m_pHud->SetPlayAnimation("Hide");
	}
}

void UCpt_QuestMng::ShowHud()
{
	if (m_pHud != nullptr)
	{
		m_pHud->SetPlayAnimation("Show");
	}
}

void UCpt_QuestMng::CreateHud(eQuestIconState eIconState, FText sText, FString sTag, const bool bQuest)
{
	if (m_pController == nullptr) return;
	if (m_pHud != nullptr) return;

	UWidget_QuestHud* pObj = CreateWidget<UWidget_QuestHud>(m_pController, m_pInst_Hud);
	if (pObj != nullptr)
	{
		pObj->AddToViewport();
		
		if ( bQuest == true )
		{
			pObj->Add_ItemList(Add_Item(eIconState, sText, sTag));			
		}
		else
		{
			pObj->Add_WorldList(Add_World(eIconState, sText, sTag));
		}

		m_pHud = pObj;
	}
}

void UCpt_QuestMng::CreateQuest(eQuestIconState eIconState, FText sText, FString sTag)
{
	if (m_pController == nullptr) return;
	if (sTag == "")
	{
		UALERT(TEXT("Quest [%s] Tag is Empty"), *GetName());
		return;
	}

	if (m_pHud == nullptr)
	{
		CreateHud(eIconState, sText, sTag, true);
		return;
	}
	
	m_pHud->Add_ItemList(Add_Item(eIconState, sText, sTag));
}

void UCpt_QuestMng::CreateWorldName(eQuestIconState eIconState, FText sText)
{
	if (m_pController == nullptr) return;
	if (m_pWorldNameItem != nullptr)
	{
		UALERT(TEXT("Already WorldName Item"));
		return;
	}
	if (m_pHud == nullptr)
	{
		CreateHud(eIconState, sText, TEXT("WorldName"), false);
		return;
	}

	m_pHud->Add_WorldList(Add_World(eIconState, sText, TEXT("WorldName")));
}

void UCpt_QuestMng::DoneQuest(FString sTagName)
{
	for (int i = 0; i < m_pItemList.Num(); i++)
	{
		if (m_pItemList[i]->GetTag() == sTagName)
		{						
			if (m_pItemList[i]->GetDone() == false)
			{
				m_pItemList[i]->SetDone(true);
				m_pItemList[i]->SetPlayAnimation("End");
				return;
			}
		}
	}
}

void UCpt_QuestMng::DoneQuest_Index(int32 nIndex)
{
	if (nIndex < 0 || nIndex > m_pItemList.Num()) return;

	if (m_pItemList[nIndex]->GetDone() == false)
	{
		m_pItemList[nIndex]->SetDone(true);
		m_pItemList[nIndex]->SetPlayAnimation("End");
	}
}

void UCpt_QuestMng::DoneQuest_All()
{
	for (int i = 0; i < m_pItemList.Num(); i++)
	{		
		if (m_pItemList[i]->GetDone() == false)
		{
			m_pItemList[i]->SetDone(true);
			m_pItemList[i]->SetPlayAnimation("End");
		}	
	}
}

void UCpt_QuestMng::RemoveQuest(FString sTagName)
{
	for (int i = 0; i < m_pItemList.Num(); i++)
	{		
		if (m_pItemList[i]->GetTag() == sTagName)
		{
			m_pItemList[i]->SetDone(true);
			m_pItemList[i]->SetTag("");
			m_pItemList[i]->SetPlayAnimation("Destroy");

			return;			
		}
	}
}

void UCpt_QuestMng::RemoveQuest_Index(int32 nIndex)
{
	m_pItemList[nIndex]->SetDone(true);
	m_pItemList[nIndex]->SetTag("");
	m_pItemList[nIndex]->SetPlayAnimation("Destroy");
}

void UCpt_QuestMng::RemoveQuest_All(const bool bIncludeDone)
{
	for (int i = 0; i < m_pItemList.Num(); i++)
	{
		if (bIncludeDone == true)
		{
			m_pItemList[i]->SetDone(true);
			m_pItemList[i]->SetTag("");
			m_pItemList[i]->SetPlayAnimation("Destroy");
		}
		else
		{
			if (m_pItemList[i]->GetDone() == false)
			{
				m_pItemList[i]->SetDone(true);
				m_pItemList[i]->SetTag("");
				m_pItemList[i]->SetPlayAnimation("Destroy");
			}
		}
		
	}
}

class UWidget_QuestItem* UCpt_QuestMng::Add_Item(eQuestIconState eIconState, FText sText, FString sTag)
{
	if (m_pController == nullptr) return nullptr;
	

	UWidget_QuestItem* pObj = CreateWidget<UWidget_QuestItem>(m_pController, m_pInst_Item);
	if (pObj != nullptr)
	{
		pObj->AddToViewport();
		pObj->SetTag(sTag);
		pObj->SetDone(false);
		pObj->SetIconState(eIconState);
		pObj->SetText_Quest(sText);
		pObj->SetPlayAnimation("Start");

		m_pItemList.Add(pObj);		
		return pObj;
	}

	return nullptr;
}

class UWidget_QuestItem* UCpt_QuestMng::Add_World(eQuestIconState eIconState, FText sText, FString sTag)
{
	if (m_pController == nullptr) return nullptr;
	if (m_pWorldNameItem != nullptr)
	{
		UALERT(TEXT("Already WorldName Item"));
		return nullptr;
	}

	UWidget_QuestItem* pObj = CreateWidget<UWidget_QuestItem>(m_pController, m_pInst_Item);
	if (pObj != nullptr)
	{
		pObj->AddToViewport();
		pObj->SetTag(sTag);
		pObj->SetIconState(eIconState);
		pObj->SetText_Quest(sText);
		pObj->SetPlayAnimation("Start");

		m_pWorldNameItem = pObj;
		return pObj;
	}

	return nullptr;
}

