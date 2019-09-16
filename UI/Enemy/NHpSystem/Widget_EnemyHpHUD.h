// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UI/NewGameHUD/Widget/Widget_Root.h"
#include "Widget_EnemyHpHUD.generated.h"

/**
 * 
 */
UCLASS()
class REVENGER_API UWidget_EnemyHpHUD : public UWidget_Root
{
	GENERATED_BODY()
	
private:

	UPROPERTY()
		class UHorizontalBox* m_pHoriBox;

	UPROPERTY()
		AActor* m_pTarget;

public:		
	virtual void NativeConstruct() override;
	virtual void NativeDestruct() override;
	virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime) override;

	void AddHoriBox(class UWidget_EnemyHpItem* pItem);
	void SetTarget(AActor* pTarget) { m_pTarget = pTarget; }
	AActor* GetTarget() { return m_pTarget; }
};
