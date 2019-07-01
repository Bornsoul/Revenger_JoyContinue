// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Revenger.h"
#include "Blueprint/UserWidget.h"
#include "Widget_SlowArrowUp.generated.h"

/**
 * 
 */
UCLASS()
class REVENGER_API UWidget_SlowArrowUp : public UUserWidget
{
	GENERATED_BODY()
	
private:
	UPROPERTY()
		class UWidgetAni_Mng* m_pWidgetAni;

	UPROPERTY()
		class UImage* m_pFullImg;

	bool m_bActive = false;
	bool m_bRevers = false;

	bool m_bUsed = false;

public:
	virtual void NativePreConstruct() override;
	virtual void NativeConstruct() override;
	virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime) override;

	UFUNCTION(BlueprintCallable)
		void SetActive(bool bActive);

	UFUNCTION(BlueprintCallable)
		void SetPlayAnimation(FString sAniName, bool bRevers = false);

	UFUNCTION(BlueprintCallable)
		void SetFullArrowActive(bool bActive);

	UFUNCTION(BlueprintCallable)
		void SetUseArrow(bool bUse) { m_bUsed = bUse; }

	UFUNCTION(BlueprintPure)
		FORCEINLINE bool GetActive() { return m_bActive; }	

	FORCEINLINE bool GetUsedArrow() { return m_bUsed; }

};
