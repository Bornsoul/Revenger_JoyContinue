// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Widget_Result_ButtonItem.generated.h"

/**
 * 
 */
UCLASS()
class REVENGER_API UWidget_Result_ButtonItem : public UUserWidget
{
	GENERATED_BODY()

private:
	UPROPERTY()
		class UWidgetAni_Mng* m_pWidgetAni;

	UPROPERTY()
		class UButton* m_pButton;

	UPROPERTY()
		class UTextBlock* m_pBtnTitle;

	bool m_bRevers = false;
	bool m_bActive = false;
	bool m_bPress = false;

public:
	virtual void NativePreConstruct() override;
	virtual void NativeConstruct() override;
	virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime) override;


	void SetPlayAnimation(FString sAniName, bool bRevers = false);
	void SetTitle(FString sText);
	void SetActive(bool bActive);

	bool GetButtonDown();

	FORCEINLINE class UWidgetAni_Mng* GetAnimation() { return m_pWidgetAni; }

};
