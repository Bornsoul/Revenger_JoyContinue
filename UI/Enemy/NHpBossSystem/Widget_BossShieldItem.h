// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UI/NewGameHUD/Widget/Widget_Root.h"
#include "Widget_BossShieldItem.generated.h"

/**
 * 
 */
UCLASS()
class REVENGER_API UWidget_BossShieldItem : public UWidget_Root
{
	GENERATED_BODY()
	
private:
	bool m_bAlive = false;

public:
	virtual void NativeConstruct() override;
	virtual void NativeDestruct() override;
	virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime) override;

	void SetHit();
	void SetHeal();

	bool GetAlive() { return m_bAlive; }

};
