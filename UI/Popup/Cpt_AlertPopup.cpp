// Fill out your copyright notice in the Description page of Project Settings.

#include "Cpt_AlertPopup.h"
#include "Widget_AlertPopup.h"
#include "Widget_AlertHud.h"

UCpt_AlertPopup::UCpt_AlertPopup()
{
	PrimaryComponentTick.bCanEverTick = true;

	static ConstructorHelpers::FObjectFinder<UClass> Const_HudWidget(TEXT("/Game/1_Project_Main/1_Blueprints/UI/Popup/BP_Widget_AlertHud.BP_Widget_AlertHud_C"));
	if (Const_HudWidget.Succeeded())
	{
		m_pInst_AlertHud = Const_HudWidget.Object;
	}

	static ConstructorHelpers::FObjectFinder<UClass> Const_Widget(TEXT("/Game/1_Project_Main/1_Blueprints/UI/Popup/BP_Widget_Alert.BP_Widget_Alert_C"));
	if (Const_Widget.Succeeded())
	{
		m_pInst_Alert = Const_Widget.Object;
	}

}

void UCpt_AlertPopup::BeginPlay()
{
	Super::BeginPlay();

}

void UCpt_AlertPopup::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	Super::EndPlay(EndPlayReason);

	if (m_pAlertHud != nullptr)
	{
		if (m_pAlertHud->IsValidLowLevel())
		{
			m_pAlertHud->RemoveFromParent();
			m_pAlertHud = nullptr;
		}
	}

	if (m_pAlertPop != nullptr)
	{
		if (m_pAlertPop->IsValidLowLevel())
		{
			m_pAlertPop->RemoveFromParent();
			m_pAlertPop = nullptr;
		}
	}
}

void UCpt_AlertPopup::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if (m_pAlertHud != nullptr)
	{
		if (m_bCreated)
		{
			m_fCreatedTime += DeltaTime;
			if (m_fCreatedTime >= m_fDestroyTime + 2.0f)
			{
				m_fCreatedTime = 0.0f;
				m_pAlertHud->RemoveFromParent();
				m_pAlertHud = nullptr;
				m_bCreated = false;
			}
		}
	}
}

void UCpt_AlertPopup::CreateAlert(const FString sText, const float fDestroyTime)
{
	if (m_pAlertHud == nullptr)
	{
		APlayerController* pController = UGameplayStatics::GetPlayerController(UObject::GetWorld(), 0);
		if (pController != nullptr)
		{
			UWidget_AlertHud* pHud = CreateWidget<UWidget_AlertHud>(pController, m_pInst_AlertHud);
			if (pHud != nullptr)
			{
				pHud->AddToViewport(50);
				pHud->AddAlert(Add_Alert(sText, fDestroyTime));
				m_pAlertHud = pHud;

				m_fCreatedTime = 0.0f;
				m_fDestroyTime = fDestroyTime;
				m_bCreated = true;
			}
		}
	}
	else
	{
		m_pAlertHud->AddAlert(Add_Alert(sText, fDestroyTime));

		m_fCreatedTime = 0.0f;
		m_fDestroyTime = fDestroyTime;
		m_bCreated = true;
	}

}

class UWidget_AlertPopup* UCpt_AlertPopup::Add_Alert(const FString sText, const float fDestroyTime /*= 5.0f*/)
{
	APlayerController* pController = UGameplayStatics::GetPlayerController(UObject::GetWorld(), 0);
	if (pController != nullptr)
	{
		UWidget_AlertPopup* pObj = CreateWidget<UWidget_AlertPopup>(pController, m_pInst_Alert);
		if (pObj != nullptr)
		{
			pObj->AddToViewport(50);
			pObj->SetTimer(fDestroyTime);
			pObj->SetText(FText::FromString(sText));
			pObj->SetPlayAnimation("Start");

			return pObj;
		}
	}

	return nullptr;
}
