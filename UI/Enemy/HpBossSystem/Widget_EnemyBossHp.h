// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Revenger.h"
#include "Blueprint/UserWidget.h"
#include "Widget_EnemyBossHp.generated.h"

/**
 * 
 */
UCLASS()
class REVENGER_API UWidget_EnemyBossHp : public UUserWidget
{
	GENERATED_BODY()
	
private:
	UPROPERTY()
		class UProgressBar* m_pHp;

	UPROPERTY()
		class UWidgetAni_Mng* m_pWidgetAni;

	bool m_bActive = false;
	bool m_bHit = false;
	bool m_bRevers = false;

public:
	virtual void NativeConstruct() override;
	virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime) override;

	void SetHit(bool bNoHit = false);
	void SetActive(bool bActive);
	void SetPlayAnimation(FString sAniName, bool bRevers = false);

public:
	FORCEINLINE bool GetActive() { return m_bActive;  }
	FORCEINLINE bool GetIsHit() { return m_bHit; }
};
