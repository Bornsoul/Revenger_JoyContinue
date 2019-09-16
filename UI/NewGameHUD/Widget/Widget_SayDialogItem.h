// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Widget_SayDialogItem.generated.h"

/**
 * 
 */
UCLASS()
class REVENGER_API UWidget_SayDialogItem : public UUserWidget
{
	GENERATED_BODY()

private:
	UPROPERTY()
		class UWidgetAni_Mng* m_pWidgetAni;

	UPROPERTY()
		class UTextBlock* m_pSayText;

	UPROPERTY()
		class AActor* m_pTarget;

	bool m_bActive = false;
	bool m_bRevers = false;

	bool m_bStartAniEnd = false;
	bool m_bHideAniEnd = false;

public:
	virtual void NativePreConstruct() override;
	virtual void NativeConstruct() override;
	virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime) override;
	virtual void NativeDestruct() override;

	UFUNCTION(BlueprintCallable)
		void SetStartAniEnd(bool bEnd) { m_bStartAniEnd = bEnd; }

	UFUNCTION(BlueprintPure)
		bool GetStartAniEnd() { return m_bStartAniEnd; }

	UFUNCTION(BlueprintCallable)
		void SetSayText(FText sSaying);

	UFUNCTION(BlueprintCallable)
		void SetActive(bool bActive);

	UFUNCTION(BlueprintCallable)
		void SetPlayAnimation(FString sAniName, bool bRevers = false);

	UFUNCTION()
		void SetTargetActor(class AActor* pTarget) { m_pTarget = pTarget; }


	UFUNCTION(BlueprintCallable)
		void SetHideAniEnd(bool bEnd) { m_bHideAniEnd = bEnd; }

	UFUNCTION(BlueprintPure)
		bool GetHideAniEnd() { return m_bHideAniEnd; }


		AActor* GetTargetActor() { return m_pTarget; }
};
