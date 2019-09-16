// Fill out your copyright notice in the Description page of Project Settings.

#include "Widget_AlertHud.h"
#include "Widget_AlertPopup.h"
#include "Components/ScrollBox.h"

void UWidget_AlertHud::NativeConstruct()
{

	m_pScrollBox = Cast<UScrollBox>(GetWidgetFromName(TEXT("AlertScroll")));
	if (m_pScrollBox == nullptr)
	{
		UALERT(TEXT("ScrollBox is Empty"));
		return;
	}
}

void UWidget_AlertHud::NativeDestruct()
{

}

void UWidget_AlertHud::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	Super::NativeTick(MyGeometry, InDeltaTime); 
	//ULOG(TEXT("Child : %d"), m_pScrollBox->GetChildrenCount());
}

void UWidget_AlertHud::AddAlert(class UWidget_AlertPopup* pAlert)
{
	if (m_pScrollBox != nullptr)
	{
		m_pScrollBox->AddChild(pAlert);
	}
}
