// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Widget_StageIntro.generated.h"

/**
 * 
 */
UCLASS()
class REVENGER_API UWidget_StageIntro : public UUserWidget
{
	GENERATED_BODY()
	
private:
	UPROPERTY()
		class URichTextBlock* m_pTitleTxt;

	UPROPERTY()
		class UWidgetAni_Mng* m_pWidgetAni;

	bool m_bActive = false;
	bool m_bRevers = false;

public:
	virtual void NativeConstruct() override;
	virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime) override;

	void SetActive(bool bActive);

	void SetTitleText(FText sText);

	UFUNCTION(BlueprintCallable)
		void SetDestroy();

	void SetAnimation(FString sAniName, bool bRevers = false);
};
