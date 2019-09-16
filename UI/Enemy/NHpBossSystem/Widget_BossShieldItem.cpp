// Fill out your copyright notice in the Description page of Project Settings.

#include "Widget_BossShieldItem.h"

void UWidget_BossShieldItem::NativeConstruct()
{
	Super::NativeConstruct();

	m_bAlive = true;
}

void UWidget_BossShieldItem::NativeDestruct()
{
	Super::NativeDestruct();

}

void UWidget_BossShieldItem::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	Super::NativeTick(MyGeometry, InDeltaTime);

}

void UWidget_BossShieldItem::SetHit()
{
	if (m_bAlive == false) return;

	SetPlayAnimation("Hit");
	m_bAlive = false;
}

void UWidget_BossShieldItem::SetHeal()
{
	if (m_bAlive == true) return;

	SetPlayAnimation("NoHit");
	m_bAlive = true;
}
