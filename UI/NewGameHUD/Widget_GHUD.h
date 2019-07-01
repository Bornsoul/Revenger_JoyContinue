// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Revenger.h"
#include "Blueprint/UserWidget.h"
#include "Widget_GHUD.generated.h"

/**
 * 
 */
UCLASS()
class REVENGER_API UWidget_GHUD : public UUserWidget
{
	GENERATED_BODY()

private:
	UPROPERTY()
		class UWidgetAni_Mng* m_pWidgetAni;

	UPROPERTY()
		class UWidget_SlowGageHUD* m_pSlowGage_HUD;

	UPROPERTY()
		class UWidget_SkillHUD* m_pSkill_HUD;

	UPROPERTY()
		class UWidget_TopTitleItem* m_pTopTitle;

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

	UFUNCTION(BlueprintCallable)
		void Active_TopTitle(bool bActive);

	UFUNCTION(BlueprintPure)
		FORCEINLINE bool GetActive() { return m_bActive; }

	UFUNCTION(BlueprintPure)
		FORCEINLINE UWidget_SlowGageHUD* GetSlowGageHUD() { return m_pSlowGage_HUD; }

	UFUNCTION(BlueprintPure)
		FORCEINLINE UWidget_SkillHUD* GetSkillHUD() { return m_pSkill_HUD; }
};
