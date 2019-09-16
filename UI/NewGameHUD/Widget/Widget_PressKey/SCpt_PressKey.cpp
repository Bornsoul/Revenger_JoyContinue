// Fill out your copyright notice in the Description page of Project Settings.

#include "SCpt_PressKey.h"
#include "WCpt_PressKey.h"
#include "Widget_PressKeyItem.h"

USCpt_PressKey::USCpt_PressKey()
{
	PrimaryComponentTick.bCanEverTick = true;

	m_pWidgetComp_PressKey = CreateDefaultSubobject<UWCpt_PressKey>(TEXT("Widget"));
	if (m_pWidgetComp_PressKey == nullptr)
	{
		ULOG(TEXT("Widget is nullptr"));
		return;
	}

}

void USCpt_PressKey::BeginPlay()
{
	Super::BeginPlay();

}

void USCpt_PressKey::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	Super::EndPlay(EndPlayReason);

	if (m_pWidgetComp_PressKey != nullptr)
	{
		if (m_pWidgetComp_PressKey->IsValidLowLevel())
		{
			m_pWidgetComp_PressKey = nullptr;
		}
	}
}

void USCpt_PressKey::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	/*if (m_pWidgetComp_PressKey != nullptr)
	{
		m_pWidgetComp_PressKey->SetWorldLocation(m_vLocation);
	}*/
}

