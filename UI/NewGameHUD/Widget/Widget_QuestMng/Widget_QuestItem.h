// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Cpt_QuestMng.h"

#include "CoreMinimal.h"
#include "UI/NewGameHUD/Widget/Widget_Root.h"
#include "Widget_QuestItem.generated.h"

enum class eQuestIconState : uint8;

UCLASS()
class REVENGER_API UWidget_QuestItem : public UWidget_Root
{
	GENERATED_BODY()

private:

	UPROPERTY()
		class UImage* m_pImg_Icon;

	UPROPERTY()
		class UTextBlock* m_pTxt_Quest;

	UPROPERTY()
		eQuestIconState m_eIconState;

	FString m_sMyTag;
	bool m_bDone = false;

public:
	virtual void NativeConstruct() override;
	virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime) override;
	virtual void NativeDestruct() override;

	void SetImage_Icon(class UTexture2D* pTexture);
	void SetText_Quest(const FText sText);
	
	void SetDone(bool bDone) { m_bDone = bDone; }
	bool GetDone() { return m_bDone; }

	void SetTag(FString sTagName);
	FString GetTag();

	void SetIconState(const eQuestIconState eIconState) { m_eIconState = eIconState; }
	eQuestIconState GetIconState() { return m_eIconState; }
};
