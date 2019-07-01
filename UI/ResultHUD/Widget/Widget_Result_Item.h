// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Widget_Result_Item.generated.h"

/**
 * 
 */
UCLASS()
class REVENGER_API UWidget_Result_Item : public UUserWidget
{
	GENERATED_BODY()
	
private:
	UPROPERTY()
		class UWidgetAni_Mng* m_pWidgetAni;

	UPROPERTY()
		class UTextBlock* m_pTitle;

	UPROPERTY()
		class UTextBlock* m_pResult;

private:
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = AUser_Option, Meta = (AllowPrivateAccess = true))
		FString m_sTitleText = "Blank";

	bool m_bRevers = false;	
	bool m_bActive = false;

	bool m_bAniDone = false;

public:
	virtual void NativePreConstruct() override;
	virtual void NativeConstruct() override;
	virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime) override;

	void SetResultTitle(FString sText);
	void SetResultText(FString sText);

	UFUNCTION(BlueprintCallable)
		void SetPlayAnimation(FString sAniName, bool bRevers = false);
	
	UFUNCTION(BlueprintCallable)
		void SetActive(bool bActive);

	UFUNCTION(BlueprintCallable)
		void SetAniDone(bool bDone) { m_bAniDone = bDone; }

	UFUNCTION(BlueprintPure)
		FORCEINLINE bool GetAniDone() { return m_bAniDone; }

	UFUNCTION(BlueprintPure)
		FORCEINLINE class UWidgetAni_Mng* GetAnimation() { return m_pWidgetAni; }
};
