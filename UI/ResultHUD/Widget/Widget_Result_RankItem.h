// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Widget_Result_RankItem.generated.h"

/**
 * 
 */
UCLASS()
class REVENGER_API UWidget_Result_RankItem : public UUserWidget
{
	GENERATED_BODY()
	
private:
	UPROPERTY()
		class UWidgetAni_Mng* m_pWidgetAni;

	bool m_bActive = false;
	bool m_bRevers = false;

public:
	virtual void NativePreConstruct() override;
	virtual void NativeConstruct() override;
	virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime) override;

	void SetActive(bool bActive);

	void SetPlayAnimation(FString sAniName, bool bRevers = false);

};
