// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Components/ProgressBar.h"
#include "Components/Image.h"
#include "Components/TextBlock.h"

#include "Revenger.h"
#include "Blueprint/UserWidget.h"
#include "Widget_PlayerDash.generated.h"

/**
 * 
 */
UCLASS()
class REVENGER_API UWidget_PlayerDash : public UUserWidget
{
	GENERATED_BODY()

private:
	UPROPERTY()
		class UProgressBar* m_pGage;

	UPROPERTY()
		class UTextBlock* m_pGageText;
	
	UPROPERTY()
		class UWidgetAni_Mng* m_pWidgetAni;

	bool m_bGage = false;

	/*UPROPERTY()
		class UMaterialInterface* m_pMaterialInstance;

	UPROPERTY()
		class UMaterialInstanceDynamic* m_pMaterialDynamic;*/

public:
	virtual void NativeConstruct() override;
	virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime) override;

	void SetValue(float fValue);
	void SetShow(bool bShow);

	float GetValue() { return m_pGage->Percent;  }
	bool GetShow() { return m_bGage; }

	FORCEINLINE bool GetAlive() { return m_bGage;  }
};
