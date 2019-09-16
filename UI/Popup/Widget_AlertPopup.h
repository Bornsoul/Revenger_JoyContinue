// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UI/NewGameHUD/Widget/Widget_Root.h"
#include "Widget_AlertPopup.generated.h"

/**
 * 
 */
UCLASS()
class REVENGER_API UWidget_AlertPopup : public UWidget_Root
{
	GENERATED_BODY()

private:

	UPROPERTY()
		class UTextBlock* m_pText;
		
	float m_fDestroyTime_Cur = 0.0f;
	float m_fDestroyTime_End = 0.0f;
	bool m_bDestroy = false;

public:
	virtual void NativeConstruct() override;
	virtual void NativeDestruct() override;
	virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime) override;

	void SetText(FText sText);
	void SetTimer(float fDestroyTime);
	
	UFUNCTION(BlueprintCallable)
		void DestroyWidget();

	UFUNCTION(BlueprintCallable)
		void SetDestroyAlert(bool bDestroy) { m_bDestroy = bDestroy; }

	UFUNCTION(BlueprintPure)
		bool GetDestroyAlert() { return m_bDestroy; }
};
