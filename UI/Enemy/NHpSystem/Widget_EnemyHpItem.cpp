// Fill out your copyright notice in the Description page of Project Settings.

#include "Widget_EnemyHpItem.h"

void UWidget_EnemyHpItem::NativeConstruct()
{
	Super::NativeConstruct();

	//SetPlayAnimation("Start");
	m_bAlive = true;
}

void UWidget_EnemyHpItem::NativeDestruct()
{
	Super::NativeDestruct();

}

void UWidget_EnemyHpItem::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	Super::NativeTick(MyGeometry, InDeltaTime);

}

void UWidget_EnemyHpItem::SetHit()
{
	if (m_bAlive == false) return;

	SetPlayAnimation("End");
	m_bAlive = false;
}

void UWidget_EnemyHpItem::SetHeal()
{
	if (m_bAlive == true) return;
	SetPlayAnimation("Start");
	m_bAlive = true;
}
