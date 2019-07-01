// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Widget/Widget_Result_Item.h"

#include "Revenger.h"
#include "Blueprint/UserWidget.h"
#include "Widget_ResultHUD.generated.h"

/**
 * 
 */
UCLASS()
class REVENGER_API UWidget_ResultHUD : public UUserWidget
{
	GENERATED_BODY()
	
private:
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category="Option_ResultItem", Meta = (AllowPrivateAccess = true))
		TArray<class UWidget_Result_Item*> m_pItemList;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Option_ResultItem", Meta = (AllowPrivateAccess = true))
		TArray<FString> m_pItemTitleList;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Option_ButtonItem", Meta = (AllowPrivateAccess = true))
		TArray<class UWidget_Result_ButtonItem*> m_pButtonItemList;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Option_ButtonItem", Meta = (AllowPrivateAccess = true))
		TArray<FString> m_pButtonTitleList;

	UPROPERTY()
		class UWidget_Result_GoodItem* m_pGoodItem;

private:
 	FTimerHandle m_pTimer_Item;	
	int32 m_nItemCount = 0;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Option_ResultItem", Meta = (AllowPrivateAccess = true))
		float m_fItemSpawnTime = 0.5f; 

	bool m_bActive = false;
	bool m_bGoodTick = false;

	bool m_bResultDone = false;

public:
	virtual void NativePreConstruct() override;
	virtual void NativeConstruct() override;
	virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime) override;
 	virtual void NativeDestruct() override;

	void SetActive(bool bActive);


	void Active_HUD();
	void DeActive_HUD();
	
	bool SetItemResult_Text(TArray<FString> pItemTextList);
	
	void SetButtonActive();
 	UFUNCTION()
 		void Cor_ItemActive();

	void Button_NextStage();
	void Button_SelectStage();

	FORCEINLINE bool GetResultDone() { return m_bResultDone; }

};
