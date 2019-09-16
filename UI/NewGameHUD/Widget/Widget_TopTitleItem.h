// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Widget_TopTitleItem.generated.h"

/**
 * 
 */
UCLASS()
class REVENGER_API UWidget_TopTitleItem : public UUserWidget
{
	GENERATED_BODY()
	
private:
	UPROPERTY()
		class UWidgetAni_Mng* m_pWidgetAni;

	bool m_bActive = false;
	bool m_bRevers = false;

	bool m_bActiveTime = false;

	bool m_bDeActiveTime = false;
	float m_fDeActiveTime_Cur = 0.0f;

	UPROPERTY(EditAnywhere)
	float m_fDeActiveTime_End = 2.0f;

public:
	virtual void NativePreConstruct() override;
	virtual void NativeConstruct() override;
	virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime) override;
	virtual void NativeDestruct() override;

	UFUNCTION(BlueprintCallable)
		void SetActive(bool bActive);

	UFUNCTION(BlueprintCallable)
		void SetPlayAnimation(FString sAniName, bool bRevers = false);

	UFUNCTION(BlueprintCallable)
		void Active_Title();

	UFUNCTION(BlueprintCallable)
		void DeActive_Title();

};
