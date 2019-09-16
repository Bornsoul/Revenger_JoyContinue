// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Revenger.h"
#include "Blueprint/UserWidget.h"
#include "Widget_QuestAlarm_Item.generated.h"

UCLASS()
class REVENGER_API UWidget_QuestAlarm_Item : public UUserWidget
{
	GENERATED_BODY()

protected:
	UPROPERTY()
		class UWidgetAni_Mng* m_pWidgetAni;

	UPROPERTY()
		class UImage* m_pImg_Icon;

	UPROPERTY()
		class UTextBlock* m_pTxt_Text;	

	UPROPERTY()
		TArray<class UVerticalBox*> m_pVertBoxList;
	
	UPROPERTY()
		TArray<UWidget_QuestAlarm_Item*> m_pQuestItem;

	int m_nVertIndex = 0;

	bool m_bActive = false;
	bool m_bRevers = false;

	FTimerHandle m_pDestroyTimer;
	bool m_bDone = false;
	bool m_bDestroyed = false;

public:
	virtual void NativeConstruct() override;
	virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime) override;
	virtual void NativeDestruct() override;

	UFUNCTION(BlueprintCallable)
		void SetActive(bool bActive);

	UFUNCTION(BlueprintCallable)
		void SetPlayAnimation(FString sAniName, bool bRevers = false);

	void SetIcon(class UTexture2D* pTexture);
	void SetText(FText sText);

	UFUNCTION(BlueprintCallable)
		void Quest_Done(class UVerticalBox* pVertBox, int nIndex = -1);

	UFUNCTION(BlueprintCallable)
		void Quest_Destroy(float fDestroyDelay = 1.0f);

	void Cor_Destroy();
	void SetDestroyed(bool bDestroyed) { m_bDestroyed = bDestroyed; }
	void SetQuestItem(TArray<UWidget_QuestAlarm_Item*> &pQuestItem);

	FORCEINLINE bool GetIsDestroyed() { return m_bDestroyed; }
	FORCEINLINE bool GetIsQuestDone() { return m_bDone; }
};
