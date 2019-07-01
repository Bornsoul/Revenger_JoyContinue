// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Revenger.h"
#include "Blueprint/UserWidget.h"
#include "Widget_Dialog.generated.h"

/**
 * 
 */
UCLASS()
class REVENGER_API UWidget_Dialog : public UUserWidget
{
	GENERATED_BODY()
	
private:

	UPROPERTY()
		class UImage* m_pCharImg;

	UPROPERTY()
		class URichTextBlock* m_pDialogTxt;

	UPROPERTY()
		class UTextBlock* m_pNameTxt;

	UPROPERTY()
		class UTextBlock* m_pNameSubTxt;

	UPROPERTY()
		class UWidgetAni_Mng* m_pWidgetAni;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category=DefaultOption, Meta=(AllowPrivateAccess = true))
		class UTexture2D* m_pDefaultCharImg;

	float m_fLenTime_Curr = 0.0f;
	float m_fLenTime_End = 0.055f;
	int32 m_nStrLen = 0;
	bool m_bStr = false;

	FString m_sDialogStr;
	FString m_sAddStr;

public:
	virtual void NativeConstruct() override;
	virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime) override;

	void SetDialogInit(FString sName, FString sSubName, FString sDialogTxt);

	void SetDialogText(FString sText);
	void SetNameText(FString sText);
	void SetNameColor(FLinearColor cColor);
	void SetSubNameText(FString sText);
	void SetCharImage(class UTexture2D* pTexture);

	bool SkipDialog();

	void SetShow(bool bShow);
	void SetStartAnimation(FString sAniName, bool bRevers = false);

public:
	FORCEINLINE bool GetIsTyping() { return m_bStr; }
};
