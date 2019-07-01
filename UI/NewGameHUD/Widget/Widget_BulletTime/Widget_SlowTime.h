// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Revenger.h"
#include "Blueprint/UserWidget.h"
#include "Widget_SlowTime.generated.h"

/**
 * 
 */
UCLASS()
class REVENGER_API UWidget_SlowTime : public UUserWidget
{
	GENERATED_BODY()

private:
	UPROPERTY()
		class UWidgetAni_Mng* m_pWidgetAni;

	UPROPERTY()
		class UTextBlock* m_pTimerTxt;

	bool m_bActive = false;
	bool m_bRevers = false;

public:
	virtual void NativePreConstruct() override;
	virtual void NativeConstruct() override;
	virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime) override;

	UFUNCTION(BlueprintCallable)
		void SetActive(bool bActive);

	UFUNCTION(BlueprintCallable)
		void SetPlayAnimation(FString sAniName, bool bRevers = false);

	void SetTimerValue(float fTimer);

	UFUNCTION(BlueprintPure)
		FORCEINLINE bool GetActive() { return m_bActive; }
};
