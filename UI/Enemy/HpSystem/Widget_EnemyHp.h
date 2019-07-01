// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Components/ProgressBar.h"

#include "Revenger.h"
#include "Blueprint/UserWidget.h"
#include "Widget_EnemyHp.generated.h"

/**
 * 
 */
UCLASS()
class REVENGER_API UWidget_EnemyHp : public UUserWidget
{
	GENERATED_BODY()
	
private:
	UPROPERTY()
		class UProgressBar* m_pHp;

	UPROPERTY()
		class UWidgetAni_Mng* m_pWidgetAni;

	UPROPERTY()
		class AActor* m_pTargetRoot;

	bool m_bActive = false;
	bool m_bHit = false;
	bool m_bRevers = false;

public:
	virtual void NativeConstruct() override;
	virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime) override;

	void SetActive(bool bActive);
	void SetPlayAnimation(FString sAniName, bool bRevers = false);
	void SetHit(bool bNoHit = false);
	void SetDestroy();

	void SetTarget(class AActor* pTarget) { m_pTargetRoot = pTarget; }
	AActor* GetTarget() { return m_pTargetRoot; }

public:
	FORCEINLINE bool GetActive() { return m_bActive; }
	FORCEINLINE bool GetIsHit() { return m_bHit; }
};
