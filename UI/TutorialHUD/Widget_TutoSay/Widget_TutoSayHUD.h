// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Revenger.h"
#include "Cpt_TutorialSay.h"
#include "UI/NewGameHUD/Widget/Widget_Root.h"
#include "Widget_TutoSayHUD.generated.h"

/**
 * 
 */
UCLASS()
class REVENGER_API UWidget_TutoSayHUD : public UWidget_Root
{
	GENERATED_BODY()
	
private:
	UPROPERTY()
		class UTextBlock* m_pTxt_Tuto;

	UPROPERTY()
		class UTextBlock* m_pTxt_Count;

	UPROPERTY()
		class UImage* m_pTimeGage;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category ="Property", meta = (AllowPrivateAccess = "true"))
		float m_fTutorialSay_Speed = 0.06f;

	UPROPERTY()
		class APlayerController* m_pPlayerController;
	
	int32 m_nListCount = 0;

	int32 m_nTutoSayLen = 0;
	FTutorialSay m_stTutoSayList;
	FTimerHandle m_pTutoSayTimer;

	float m_fGageScale = 0.0f;
	float m_fGageTime = 0.0f;
	bool m_bGageState = false;

	bool m_bSayAllEnd = false;
	bool m_bSkip = false;

public:
	virtual void NativeConstruct() override;
	virtual void NativeDestruct() override;
	virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime) override;
	
	UFUNCTION(BlueprintCallable)
		void SetInit(const FTutorialSay stSayList);

	UFUNCTION(BlueprintCallable)
		void Play_TutorialText();

	UFUNCTION(BlueprintCallable)
		void Stop_TutorialText();


	UFUNCTION(BlueprintCallable)
		void SetGageTime(float fGage);

	UFUNCTION(BlueprintCallable)
		void SetGageState(bool bState) { m_bGageState = bState; }

	UFUNCTION(BlueprintCallable)
		void SetSayAllEnd(bool bEnd) { m_bSayAllEnd = bEnd; }

	UFUNCTION(BlueprintPure)
		bool GetSayAllEnd() { return m_bSayAllEnd; }

	void SetSayCountText(int32 nCount);

	void Tick_TutorialGage(float fDeltaTime);
	void Cor_TutoSay();
};
