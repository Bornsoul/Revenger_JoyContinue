// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Revenger.h"
#include "UI/NewGameHUD/Widget/Widget_Root.h"
#include "Widget_KeyInputItem.generated.h"

/**
 * 
 */
UCLASS()
class REVENGER_API UWidget_KeyInputItem : public UWidget_Root
{
	GENERATED_BODY()
	
private:

	UPROPERTY()
		class UTextBlock* m_pKeyText;

	UPROPERTY()
		class UImage* m_pKeyImg;

	UPROPERTY()
		FText m_sKeyState;

public:
	virtual void NativeConstruct() override;
	virtual void NativeDestruct() override;
	virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime) override;

	void SetKeyText(const FText sKeyText, UTexture2D* pKeyImg);

	FText GetKeyText();

};
