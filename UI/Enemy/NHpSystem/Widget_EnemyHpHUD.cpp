// Fill out your copyright notice in the Description page of Project Settings.

#include "Widget_EnemyHpHUD.h"
#include "Components/HorizontalBox.h"

void UWidget_EnemyHpHUD::NativeConstruct()
{
	Super::NativeConstruct();

	m_pHoriBox = Cast<UHorizontalBox>(GetWidgetFromName(TEXT("HpBox")));
	if (m_pHoriBox == nullptr)
	{
		UALERT(TEXT("Hp Horibox is Empty"));
		return;
	}

}

void UWidget_EnemyHpHUD::NativeDestruct()
{
	Super::NativeDestruct();

	if (m_pHoriBox != nullptr)
	{
		if (m_pHoriBox->IsValidLowLevel())
		{
			m_pHoriBox = nullptr;
		}
	}
}

void UWidget_EnemyHpHUD::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	Super::NativeTick(MyGeometry, InDeltaTime);

}

void UWidget_EnemyHpHUD::AddHoriBox(class UWidget_EnemyHpItem* pItem)
{
	if (m_pHoriBox != nullptr)
	{
		m_pHoriBox->AddChild(pItem);
	}
}
