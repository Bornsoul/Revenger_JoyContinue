// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Revenger.h"
#include "Blueprint/UserWidget.h"
#include "Widget_SaveDataItem.generated.h"

/**
 * 
 */
UCLASS()
class REVENGER_API UWidget_SaveDataItem : public UUserWidget
{
	GENERATED_BODY()

private:
	UPROPERTY()
		class UWidgetAni_Mng* m_pWidgetAni;
	
	UPROPERTY()
		class UVerticalBox* m_pVerticalBox;

	UPROPERTY()
		class UImage* m_pImg_Slide;

	UPROPERTY()
		class UCpt_SaveDataAlert* m_pRoot;

	FTimerHandle m_pTimer;
	float m_fSlideTime = 0.0f;
	float m_fShowTime = 0.0f;
	bool m_bSlideActive = false;

	bool m_bActive = false;
	bool m_bRevers = false;

	bool m_bDestroy = false;

public:
	virtual void NativePreConstruct() override;
	virtual void NativeConstruct() override;
	virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime) override;
	virtual void NativeDestruct() override;


	void SetDestroyTimer(float fTimer);
	void SetVericalBox(class UVerticalBox* pVertBox, class UCpt_SaveDataAlert* pRoot);
	void Destroy();

	UFUNCTION(BlueprintCallable)
		void SetActive(bool bActive);

	UFUNCTION(BlueprintCallable)
		void SetPlayAnimation(FString sAniName, bool bRevers = false);

};
