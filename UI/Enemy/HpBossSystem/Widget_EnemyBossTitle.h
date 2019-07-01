// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Widget_EnemyBossTitle.generated.h"

/**
 * 
 */
UCLASS()
class REVENGER_API UWidget_EnemyBossTitle : public UUserWidget
{
	GENERATED_BODY()
	
private:
	UPROPERTY()
		class URichTextBlock* m_pTitle;

	UPROPERTY()
		class URichTextBlock* m_pSubTitle;

	UPROPERTY()
		class UWidgetAni_Mng* m_pWidgetAni;

	bool m_bActive = false;
	bool m_bHit = false;
	bool m_bRevers = false;

public:
	virtual void NativeConstruct() override;
	virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime) override;

	void SetHit(bool bNoHit = false);

	void SetTextInit(FString sTitle, FString sSubTitle);
	void SetText_Title(FString sText);
	void SetText_SubTitle(FString sText);

	void SetActive(bool bActive);
	void SetPlayAnimation(FString sAniName, bool bRevers = false);
};
