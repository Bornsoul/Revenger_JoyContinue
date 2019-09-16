// Fill out your copyright notice in the Description page of Project Settings.

#include "Cpt_EnemyHpComponent.h"
#include "Widget_EnemyHpHUD.h"
#include "Widget_EnemyHpItem.h"

UCpt_EnemyHpComponent::UCpt_EnemyHpComponent()
{
	PrimaryComponentTick.bCanEverTick = true;

	static ConstructorHelpers::FObjectFinder<UClass> Const_Hud(TEXT("/Game/1_Project_Main/1_Blueprints/UI/Enemy/NewEnemyHp/BP_Widget_HpHud.BP_Widget_HpHud_C"));
	if (Const_Hud.Succeeded())
	{
		m_pInst_Hud = Const_Hud.Object;
	}

	static ConstructorHelpers::FObjectFinder<UClass> Const_Item(TEXT("/Game/1_Project_Main/1_Blueprints/UI/Enemy/NewEnemyHp/BP_Widget_HpItem.BP_Widget_HpItem_C"));
	if (Const_Item.Succeeded())
	{
		m_pInst_Item = Const_Item.Object;
	}


}

void UCpt_EnemyHpComponent::BeginPlay()
{
	Super::BeginPlay();

	m_pController = UGameplayStatics::GetPlayerController(GetWorld(), 0);
	if (m_pController == nullptr)
	{
		UALERT(TEXT("Controller is Empty"));
		return;
	}

	m_pHpItemList.Empty();
}

void UCpt_EnemyHpComponent::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	Super::EndPlay(EndPlayReason);

	m_pHpItemList.Empty();

	if (m_pHud != nullptr)
	{
		if (m_pHud->IsValidLowLevel())
		{
			m_pHud->RemoveFromParent();
			m_pHud = nullptr;
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

void UCpt_EnemyHpComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if (m_pHud != nullptr)
	{
		Tick_HudTarget();
		if (m_pHpItemList.Num() <= 0)
		{
			m_pHud->RemoveFromParent();
			m_pHud = nullptr;
			return;
		}
	}
}

void UCpt_EnemyHpComponent::CreateHp(const float fHp)
{
	if (m_pHud != nullptr)
	{
		UALERT(TEXT("The HUD has already been created."));
		return;
	}

	if (m_pController != nullptr)
	{
		UWidget_EnemyHpHUD* pObj = CreateWidget<UWidget_EnemyHpHUD>(m_pController, m_pInst_Hud);
		if (pObj != nullptr)
		{
			pObj->AddToViewport();
			pObj->SetTarget(GetOwner());
			//UALERT(TEXT("Target : %s"), *GetOwner()->GetName());
			for (int i = 0; i < FMath::FloorToFloat(fHp); i++)
			{
				pObj->AddHoriBox(Add_Hp());
			}
			m_vHudLocation.X = m_vHudLocation.X + (m_pHpItemList.Num() * 43) / 2;
			m_pHud = pObj;
		}
	}
}


void UCpt_EnemyHpComponent::Hit()
{
	if (m_pController == nullptr || m_pHud == nullptr || m_pHpItemList.Num() <= 0) return;

	for (int i = m_pHpItemList.Num() - 1; i >= 0; --i)
	{
		if (m_pHpItemList[i]->GetAlive() == true)
		{
			m_pHpItemList[i]->SetHit();
			return;
		}
	}
}

void UCpt_EnemyHpComponent::Heal()
{
	if (m_pController == nullptr || m_pHud == nullptr || m_pHpItemList.Num() <= 0) return;

	for (int i = 0; i < m_pHpItemList.Num(); i++)
	{

		if (m_pHpItemList[i]->GetAlive() == false)
		{
			m_pHpItemList[i]->SetHeal();
			return;
		}
	}
}

class UWidget_EnemyHpItem* UCpt_EnemyHpComponent::Add_Hp()
{
	if (m_pController != nullptr)
	{
		UWidget_EnemyHpItem* pObj = CreateWidget<UWidget_EnemyHpItem>(m_pController, m_pInst_Item);
		if (pObj != nullptr)
		{
			pObj->AddToViewport();
			pObj->SetPlayAnimation("Start");
			m_pHpItemList.Add(pObj);
			return pObj;
		}
	}

	return nullptr;
}

void UCpt_EnemyHpComponent::SetHudTarget(AActor* pActorTarget)
{
	if (m_pHud != nullptr)
	{
		m_pHud->SetTarget(pActorTarget);
	}
}

void UCpt_EnemyHpComponent::SetHudLocation(FVector2D vLocation)
{
	if (m_pHud != nullptr)
	{
		m_vHudLocation = vLocation;
	}
}

void UCpt_EnemyHpComponent::DestroyHud()
{
	DestroyComponent(true);
}

void UCpt_EnemyHpComponent::Tick_HudTarget()
{
	if (m_pHud == nullptr) return;
	if (m_pHpItemList.Num() <= 0) return;

	for (int i = 0; i < m_pHpItemList.Num(); i++)
	{
		if (m_pHpItemList[i] != nullptr)
		{
			AActor* pObj = m_pHud->GetTarget();

			if (pObj != nullptr)
			{
				FVector2D vPosResult;
				FVector2D vScreenPos;

				FVector vPos = pObj->GetActorLocation();
				m_pController->ProjectWorldLocationToScreen(vPos, vPosResult);

				vScreenPos.X = vPosResult.X;
				vScreenPos.Y = vPosResult.Y;

				m_pHud->SetPositionInViewport(FVector2D((vScreenPos.X - m_vHudLocation.X), (vScreenPos.Y - m_vHudLocation.Y)), true);
			}
		}
	}

}

