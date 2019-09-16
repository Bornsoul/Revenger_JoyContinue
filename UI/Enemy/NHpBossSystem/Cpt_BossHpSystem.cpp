// Fill out your copyright notice in the Description page of Project Settings.
#include "Cpt_BossHpSystem.h"
#include "Widget_BossHpHUD.h"
#include "Widget_BossHpItem.h"
#include "Widget_BossShieldItem.h"
#include "UI/Enemy/HpBossSystem/Widget_EnemyBossTitle.h"

UCpt_BossHpSystem::UCpt_BossHpSystem()
{
	PrimaryComponentTick.bCanEverTick = true;

	static ConstructorHelpers::FObjectFinder<UClass> Const_TitleWidget(TEXT("/Game/1_Project_Main/1_Blueprints/UI/Enemy/HpSystem/BP_EnemyBossTitle.BP_EnemyBossTitle_C"));
	if (Const_TitleWidget.Succeeded())
	{
		m_pInst_TitleWidget = Const_TitleWidget.Object;
	}

	static ConstructorHelpers::FObjectFinder<UClass> Const_Hud(TEXT("/Game/1_Project_Main/1_Blueprints/UI/Enemy/BossHpSystem/BP_Widget_BossHpHUD.BP_Widget_BossHpHUD_C"));
	if (Const_Hud.Succeeded())
	{
		m_pInst_HUD = Const_Hud.Object;
	}

	static ConstructorHelpers::FObjectFinder<UClass> Const_Item(TEXT("/Game/1_Project_Main/1_Blueprints/UI/Enemy/BossHpSystem/BP_Widget_BossHpItem.BP_Widget_BossHpItem_C"));
	if (Const_Item.Succeeded())
	{
		m_pInst_Item = Const_Item.Object;
	}

	static ConstructorHelpers::FObjectFinder<UClass> Const_Shield(TEXT("/Game/1_Project_Main/1_Blueprints/UI/Enemy/BossHpSystem/BP_Widget_BossShieldItem.BP_Widget_BossShieldItem_C"));
	if (Const_Shield.Succeeded())
	{
		m_pInst_Shield = Const_Shield.Object;
	}
}

void UCpt_BossHpSystem::BeginPlay()
{
	Super::BeginPlay();
			
	m_pController = UGameplayStatics::GetPlayerController(GetWorld(), 0);
	if (m_pController == nullptr)
	{
		UALERT(TEXT("Controller is nullptr"));
		return;
	}	
}


void UCpt_BossHpSystem::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	Super::EndPlay(EndPlayReason);

	m_pHpItemList.Empty();
	m_pShieldItemList.Empty();

	if (m_pHud!= nullptr)
	{
		if (m_pHud->IsValidLowLevel())
		{
			m_pHud->RemoveFromParent();
			m_pHud = nullptr;
		}
	}

	if (m_pTitleWidget != nullptr)
	{
		if (m_pTitleWidget->IsValidLowLevel())
		{
			m_pTitleWidget = nullptr;
		}
	}

	if (m_pController != nullptr)
	{
		if (m_pController->IsValidLowLevel())
		{
			m_pController = nullptr;
		}
	}
}

void UCpt_BossHpSystem::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

}

void UCpt_BossHpSystem::CreateHpShield(float fHp, float fShield)
{
	if (m_pController == nullptr)return;
	if (m_pHud != nullptr)return;

	UWidget_BossHpHUD* pHud = CreateWidget<UWidget_BossHpHUD>(m_pController, m_pInst_HUD);
	if (pHud != nullptr)
	{
		pHud->AddToViewport();
		for (int i = 0; i < FMath::FloorToFloat(fHp); i++)
		{
			pHud->Add_Hp(Add_HpItem());
		}
		for (int i = 0; i < FMath::FloorToFloat(fShield); i++)
		{
			pHud->Add_Shield(Add_ShieldItem());
		}
		Add_TitleItem();
		m_pHud = pHud;
	}
}

void UCpt_BossHpSystem::Hit_Hp(const bool bAll)
{
	if (m_pController == nullptr || m_pHud == nullptr || m_pHpItemList.Num() <= 0) return;

	if (m_pTitleWidget != nullptr)
	{
		m_pTitleWidget->SetPlayAnimation("Hit");
	}

	for (int i = m_pHpItemList.Num() - 1; i >= 0; --i)
	{
		if (bAll == false)
		{
			if (m_pHpItemList[i]->GetAlive() == true)
			{
				m_pHpItemList[i]->SetHit();
				return;
			}
		}
		else
		{
			if (m_pHpItemList[i]->GetAlive() == true)
			{
				m_pHpItemList[i]->SetHit();
			}
		}
	}

}

void UCpt_BossHpSystem::Hit_Shield(const bool bAll)
{
	if (m_pController == nullptr || m_pHud == nullptr || m_pShieldItemList.Num() <= 0) return;

	if (m_pTitleWidget != nullptr)
	{
		m_pTitleWidget->SetPlayAnimation("HitShield");
	}

	for (int i = m_pShieldItemList.Num() - 1; i >= 0; --i)
	{
		if (bAll == false)
		{
			if (m_pShieldItemList[i]->GetAlive() == true)
			{
				m_pShieldItemList[i]->SetHit();
				return;
			}			
		}
		else
		{
			if (m_pShieldItemList[i]->GetAlive() == true)
			{
				m_pShieldItemList[i]->SetHit();
			}
		}
	}
}

void UCpt_BossHpSystem::Heal_Hp(const bool bAll)
{
	if (m_pController == nullptr || m_pHud == nullptr || m_pHpItemList.Num() <= 0) return;

	for (int i = 0; i < m_pHpItemList.Num(); i++)
	{
		if (bAll == false)
		{
			if (m_pHpItemList[i]->GetAlive() == false)
			{
				m_pHpItemList[i]->SetHeal();
				return;
			}
		}
		else
		{
			m_pHpItemList[i]->SetHeal();			
		}
	}
}

void UCpt_BossHpSystem::Heal_Shield(const bool bAll)
{
	if (m_pController == nullptr || m_pHud == nullptr || m_pShieldItemList.Num() <= 0) return;

	for (int i = 0; i < m_pShieldItemList.Num(); i++)
	{
		if (bAll == false)
		{
			if (m_pShieldItemList[i]->GetAlive() == false)
			{
				m_pShieldItemList[i]->SetHeal();
				return;
			}
		}
		else
		{
			m_pShieldItemList[i]->SetHeal();
		}
	}
}

void UCpt_BossHpSystem::Animation_Hp(const FString sAniName, const bool bRevers)
{
	if (m_pController == nullptr || m_pHud == nullptr || m_pHpItemList.Num() <= 0) return;

	for (int i = 0; i < m_pHpItemList.Num(); i++)
	{
		m_pHpItemList[i]->SetPlayAnimation(sAniName, bRevers);
	}
}

void UCpt_BossHpSystem::Animation_Shield(const FString sAniName, const bool bRevers)
{
	if (m_pController == nullptr || m_pHud == nullptr || m_pShieldItemList.Num() <= 0) return;

	for (int i = 0; i < m_pShieldItemList.Num(); i++)
	{
		m_pShieldItemList[i]->SetPlayAnimation(sAniName, bRevers);
	}
}

void UCpt_BossHpSystem::DestroySystem()
{
	Animation_Hp("End");
	Animation_Shield("End");	
	m_pTitleWidget->SetPlayAnimation("Destroy");
	
	m_pController->GetWorldTimerManager().SetTimer(m_pDestroyTime, this, &UCpt_BossHpSystem::DestroySelf, 2.0f, false);	
}

void UCpt_BossHpSystem::DestroySelf()
{
	if (m_pController == nullptr) return;

	m_pController->GetWorldTimerManager().ClearTimer(m_pDestroyTime);
	DestroyComponent();
}

class UWidget_BossHpItem* UCpt_BossHpSystem::Add_HpItem()
{
	if (m_pController == nullptr) return nullptr;

	UWidget_BossHpItem* pItem = CreateWidget<UWidget_BossHpItem>(m_pController, m_pInst_Item);
	if (pItem != nullptr)
	{
		pItem->AddToViewport();
		pItem->SetPlayAnimation("Start");
		m_pHpItemList.Add(pItem);
		return pItem;
	}
	return nullptr;
}

class UWidget_BossShieldItem* UCpt_BossHpSystem::Add_ShieldItem()
{
	if (m_pController == nullptr) return nullptr;

	UWidget_BossShieldItem* pItem = CreateWidget<UWidget_BossShieldItem>(m_pController, m_pInst_Shield);
	if (pItem != nullptr)
	{
		pItem->AddToViewport();
		pItem->SetPlayAnimation("Start");
		m_pShieldItemList.Add(pItem);
		return pItem;
	}
	return nullptr;
}

class UWidget_EnemyBossTitle* UCpt_BossHpSystem::Add_TitleItem()
{
	if (m_pController == nullptr) return nullptr;

	UWidget_EnemyBossTitle* pItem = CreateWidget<UWidget_EnemyBossTitle>(m_pController, m_pInst_TitleWidget);
	if (pItem != nullptr)
	{
		pItem->AddToViewport();
		pItem->SetActive(true);
		m_pTitleWidget = pItem;
		return pItem;
	}
	return nullptr;
}
