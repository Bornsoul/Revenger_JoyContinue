// Fill out your copyright notice in the Description page of Project Settings.

#include "WCpt_PressKey.h"
#include "Widget_PressKeyItem.h"

UWCpt_PressKey::UWCpt_PressKey()
{
	PrimaryComponentTick.bCanEverTick = false;

	static ConstructorHelpers::FObjectFinder<UClass> Const_Widget(TEXT("/Game/1_Project_Main/1_Blueprints/UI/NEW/Widgets/PressKey_Widget/BP_Wdiget_PressF.BP_Wdiget_PressF_C"));
	if (Const_Widget.Succeeded())
	{
		m_pInst_PressKey = Const_Widget.Object;
	}

	SetWidgetSpace(EWidgetSpace::Screen);
}

void UWCpt_PressKey::BeginPlay()
{
	Super::BeginPlay();

	if (m_pInst_PressKey != nullptr)
	{
		SetWidgetClass(m_pInst_PressKey);
	}

	m_pPressKeyItem = Cast<UWidget_PressKeyItem>(GetUserWidgetObject());
	if (m_pPressKeyItem != nullptr)
	{
		ULOG(TEXT("PressKey is Ready"));
	}

}

void UWCpt_PressKey::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	Super::EndPlay(EndPlayReason);

}

void UWCpt_PressKey::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

}
