// Fill out your copyright notice in the Description page of Project Settings.

#include "Cpt_PressKey.h"
#include "Widget_PressKeyItem.h"

UCpt_PressKey::UCpt_PressKey()
{
	PrimaryComponentTick.bCanEverTick = true;

	static ConstructorHelpers::FObjectFinder<UClass> Const_Widget(TEXT("/Game/1_Project_Main/1_Blueprints/UI/NEW/Widgets/PressKey_Widget/BP_Wdiget_PressF.BP_Wdiget_PressF_C"));
	if (Const_Widget.Succeeded())
	{
		m_pInst_PressKey = Const_Widget.Object;
	}
}

void UCpt_PressKey::BeginPlay()
{
	Super::BeginPlay();

	APlayerController* pPlayerController = UGameplayStatics::GetPlayerController(GetWorld(), 0);
	m_pPressKeyItem = CreateWidget<UWidget_PressKeyItem>(pPlayerController, m_pInst_PressKey);
	if (m_pPressKeyItem != nullptr)
	{
		m_pPressKeyItem->AddToViewport();
	}
	
}

void UCpt_PressKey::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	Super::EndPlay(EndPlayReason);

	if (m_pPressKeyItem != nullptr)
	{
		if (m_pPressKeyItem->IsValidLowLevel())
		{
			m_pPressKeyItem = nullptr;
		}
	}
}

void UCpt_PressKey::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

}

void UCpt_PressKey::Tick_IconLocation(FVector vLoc, float fWidth, float fHeight)
{		

		APlayerController* pPlayerController = UGameplayStatics::GetPlayerController(GetWorld(), 0);

		FVector2D vScreenPos;
		
		pPlayerController->ProjectWorldLocationToScreen(vLoc, vScreenPos);

		int32 nScreen_Width = 0.0f;
		int32 nScreen_Height = 0.0f;

		pPlayerController->GetViewportSize(nScreen_Width, nScreen_Height);

		int32 nScreenX = (int32)vScreenPos.X+fWidth;
		int32 nScreenY = (int32)vScreenPos.Y+fHeight;

		m_pPressKeyItem->SetPositionInViewport(FVector2D(nScreenX, nScreenY));		
}
