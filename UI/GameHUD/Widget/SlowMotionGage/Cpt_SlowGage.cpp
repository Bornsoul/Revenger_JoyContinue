// Fill out your copyright notice in the Description page of Project Settings.

#include "Cpt_SlowGage.h"
#include "Widget_SlowTimeGage.h"
#include "Actor/Characters/GameCharacter.h"
#include "Kismet/GameplayStatics.h"

UCpt_SlowGage::UCpt_SlowGage()
{
	PrimaryComponentTick.bCanEverTick = true;

	static ConstructorHelpers::FObjectFinder<UClass> Const_Widget(TEXT("/Game/1_Project_Main/1_Blueprints/UI/GameHUD/BP_Widget_PlayerSlowMotion.BP_Widget_PlayerSlowMotion_C"));
	if (Const_Widget.Succeeded())
	{
		m_pInst_Widget = Const_Widget.Object;
	}

}

void UCpt_SlowGage::BeginPlay()
{
	Super::BeginPlay();
	
}

void UCpt_SlowGage::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	Super::EndPlay(EndPlayReason);

}

void UCpt_SlowGage::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if (m_pWidget == nullptr) return;

	switch (m_eState)
	{
		case static_cast<int32>(E_State_SlowGage::E_SLOW_NONE) :
			break;
			case static_cast<int32>(E_State_SlowGage::E_SLOW_ACTIVE) :

			if (m_fGageValue >= 1.0f)
			{
				m_fGageValue = 1.0f;
				m_bIsFullGage = true;
				m_eState = static_cast<int32>(E_State_SlowGage::E_SLOW_DEACTIVE);

				return;
			}

			m_fGageValue += m_fGageSpeed *DeltaTime;
			m_pWidget->SetValue(m_fGageValue);
			break;
		case static_cast<int32>(E_State_SlowGage::E_SLOW_DEACTIVE) :
			if (m_fGageValue <= 0.0f)
			{
				m_fGageValue = 0.0f;
				m_pWidget->SetShow(false);
				m_eState = static_cast<int32>(E_State_SlowGage::E_SLOW_NONE);				
				return;
			}

			m_fGageValue -= m_fGageSpeed *DeltaTime;
			m_pWidget->SetValue(m_fGageValue);
			break;
	}
}

void UCpt_SlowGage::SetInit(class AActor* pActor, FVector2D vPos)
{
	if (m_pInst_Widget == nullptr)
	{
		ULOG(TEXT("Widget Inst nullptr"));
		return;
	}

	m_fGageValue = 0.0f;	

	APlayerController* pPlayerController = UGameplayStatics::GetPlayerController(GetWorld(), 0);
	UWidget_SlowTimeGage* pObj = CreateWidget<UWidget_SlowTimeGage>(pPlayerController, m_pInst_Widget);
	if (pObj != nullptr)
	{
		m_pWidget = pObj;		
		pObj->SetInit(pActor, vPos);				
		pObj->SetValue(m_fGageValue);
		pObj->AddToViewport();
		pObj->SetActive(false);

	}
		
}

void UCpt_SlowGage::SlowTargetTick(AActor* pTarget)
{
	if (m_pWidget == nullptr) return;
	m_pWidget->Tick_Target(pTarget);
}

void UCpt_SlowGage::SetDestroy()
{
	m_pWidget->SetActive(false);
	m_pWidget->RemoveFromParent();
}

void UCpt_SlowGage::Active_Slow()
{
	if (m_eState == static_cast<int32>(E_State_SlowGage::E_SLOW_ACTIVE)) return;
	
	//if (m_pWidget->GetShow() == false)
	m_pWidget->SetActive(true);
	m_pWidget->SetShow(true);
	ULOG(TEXT("ActiveSlow"));
	m_eState = static_cast<int32>(E_State_SlowGage::E_SLOW_ACTIVE);

}

void UCpt_SlowGage::DeActive_Slow()
{
	m_bIsFullGage = false;
	m_eState = static_cast<int32>(E_State_SlowGage::E_SLOW_DEACTIVE);
	ULOG(TEXT("DeActiveSlow"));
}