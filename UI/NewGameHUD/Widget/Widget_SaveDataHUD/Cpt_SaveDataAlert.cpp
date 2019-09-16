// Fill out your copyright notice in the Description page of Project Settings.

#include "Cpt_SaveDataAlert.h"
#include "Widget_SaveDataItem.h"
//#include "UI/NewGameHUD/Widget_GHUD.h"
#include "UI/NewGameHUD/HUD_Game.h"
#include "Components/VerticalBox.h"
#include "Kismet/GameplayStatics.h"

UCpt_SaveDataAlert::UCpt_SaveDataAlert()
{
	PrimaryComponentTick.bCanEverTick = true;

	static ConstructorHelpers::FObjectFinder<UClass> Const_Widget(TEXT("/Game/1_Project_Main/1_Blueprints/UI/NEW/Widgets/BP_Widget_SaveData.BP_Widget_SaveData_C"));
	if (Const_Widget.Succeeded())
	{
		m_pInst_Widget = Const_Widget.Object;
	}
}


void UCpt_SaveDataAlert::BeginPlay()
{
	Super::BeginPlay();

	m_pController = Cast<APlayerController>(UGameplayStatics::GetPlayerController(GetWorld(), 0));
	if (m_pController == nullptr)
	{		
		return;
	}

	m_pHud = Cast<AHUD_Game>(m_pController->GetHUD());
	if (m_pHud == nullptr)
	{
		ULOG(TEXT("Hud is nullptr"));
		return;
	}

	m_bDestroy = false;
}

void UCpt_SaveDataAlert::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	Super::EndPlay(EndPlayReason);

	DestroyAll_Alerts();

	if (m_pInst_Widget != nullptr)
	{
		if (m_pInst_Widget->IsValidLowLevel())
		{
			m_pInst_Widget = nullptr;
		}
	}

	if (m_pHud != nullptr)
	{
		if (m_pHud->IsValidLowLevel())
		{			
			m_pHud = nullptr;
		}
	}
	
}

void UCpt_SaveDataAlert::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

}

class UWidget_SaveDataItem* UCpt_SaveDataAlert::Create_Alert(float fAlertTime /*= 2.0f*/)
{	
	if (m_pController == nullptr)
	{
		m_pController = Cast<APlayerController>(UGameplayStatics::GetPlayerController(GetWorld(), 0));
		m_pHud = Cast<AHUD_Game>(m_pController->GetHUD());

		Create_Alert(fAlertTime);
		return nullptr;
	}

	if (m_bDestroy == true)
	{
		return nullptr;
	}
	else
	{
		if (m_pHud == nullptr || 
			m_pHud->GetRootHUD() == nullptr ||
			m_pHud->GetRootHUD()->GetVerticalStatus() == nullptr)
		{
			ULOG(TEXT("HUD is nullptr"));
			return nullptr;
		}

		UWidget_SaveDataItem* pObj = CreateWidget<UWidget_SaveDataItem>(m_pController, m_pInst_Widget);
		if (pObj != nullptr)
		{
			pObj->AddToViewport();		
			m_pHud->GetRootHUD()->GetVerticalStatus()->AddChildToVerticalBox(pObj);
			pObj->SetVericalBox(m_pHud->GetRootHUD()->GetVerticalStatus(), this);
			pObj->SetDestroyTimer(fAlertTime);
			pObj->SetActive(true);
			m_bDestroy = true;

			return pObj;
		}
	}
	
	return nullptr;
}

void UCpt_SaveDataAlert::Destroy_Alert(int nIndex)
{	
	if (m_pSaveDataItem[nIndex] == nullptr)
	{
		return;
	}

	m_pSaveDataItem[nIndex]->RemoveFromParent();
	m_pSaveDataItem.RemoveAt(nIndex);
}

void UCpt_SaveDataAlert::DestroyAll_Alerts()
{
	if (m_pSaveDataItem.Num() < 0)
	{
		return;
	}

	for (int i = 0; i < m_pSaveDataItem.Num(); i++)
	{
		if (m_pSaveDataItem[i] != nullptr)
		{
			//m_pSaveDataItem[i]->RemoveFromParent();
			m_pSaveDataItem[i] = nullptr;
		}
	}
	m_pSaveDataItem.Empty();
}

