// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Revenger.h"
#include "Blueprint/UserWidget.h"
#include "Widget_BossHpHUD.generated.h"

/**
 * 
 */
UCLASS()
class REVENGER_API UWidget_BossHpHUD : public UUserWidget
{
	GENERATED_BODY()

private:
	UPROPERTY()
		class UWidgetAni_Mng* m_pWidgetAni;

	UPROPERTY()
		class UHorizontalBox* m_pHeartBoxList;

	UPROPERTY()
		class UHorizontalBox* m_pShieldBoxList;;

	bool m_bActive = false;
	bool m_bRevers = false;

public:
	virtual void NativeConstruct() override;
	virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime) override;
	virtual void NativeDestruct() override;

	UFUNCTION(BlueprintCallable)
		void SetActive(bool bActive);

	UFUNCTION(BlueprintCallable)
		void SetPlayAnimation(FString sAniName, bool bRevers = false);


	void Add_Hp(class UWidget_BossHpItem* pItem);
	void Add_Shield(class UWidget_BossShieldItem* pItem);
};
