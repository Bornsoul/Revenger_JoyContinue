// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Revenger.h"
#include "Blueprint/UserWidget.h"
#include "Widget_SkillItem.generated.h"

/**
 * 
 */
UCLASS()
class REVENGER_API UWidget_SkillItem : public UUserWidget
{
	GENERATED_BODY()
	
private:
	UPROPERTY()
		class UWidgetAni_Mng* m_pWidgetAni;


	UPROPERTY()
		class UImage* m_pIcon;

	UPROPERTY()
		class UImage* m_pLabel;

	UPROPERTY()
		TArray<class UProgressBar*> m_pCountList;

	UPROPERTY()
		class UProgressBar* m_pCoolTime;

	UPROPERTY()
		class UTextBlock* m_pCoolTime_Text;



	// 기본 상태 이미지
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Skill Widget", meta = (AllowPrivateAccess = "true"))
		class UTexture2D* m_pIcon_Normal;

	// 사용중 상태 이미지
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Skill Widget", meta = (AllowPrivateAccess = "true"))
		class UTexture2D* m_pIcon_Outline;

	// 아이콘 이름 이미지
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category="Skill Widget", meta = (AllowPrivateAccess = "true"))
		class UTexture2D* m_pIcon_Label;

	// true 이면 상단에 카운트가 생김 
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Skill Widget", meta = (AllowPrivateAccess = "true"))
		bool m_bUseCount = false;


	bool m_bActive = false;
	bool m_bRevers = false;

	// CoolTIme
	bool m_bCoolTimeActive = false;

	float m_fCoolTime_Cur = 0.0f;
	float m_fCoolTime_End = 0.0f;
	float m_fCoolTime_CurTime = 0.0f;
	float m_fCoolTime_Percent = 0.0f;
	float m_fCoolTime_Lerp = 0.0f;

	int32 m_nCoolTimeCount_Val = 3;
	float m_fCoolTimeCount_Cur = 0.0f;
	float m_fCoolTimeCount_End = 0.0f;
	bool m_bCoolTimeCountActive = false;
	bool m_bCoolTimeCount_WaitActive = false;

public:
	virtual void NativePreConstruct() override;
	virtual void NativeConstruct() override;
	virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime) override;

	void SetEnter();
	
	UFUNCTION(BlueprintCallable)
		void SetActive(bool bActive);

	UFUNCTION(BlueprintCallable)
		void SetPlayAnimation(FString sAniName, bool bRevers = false);

	UFUNCTION(BlueprintCallable)
		void Active_CoolTime(float fCoolTime);

	UFUNCTION(BlueprintCallable)
		void DeActive_CoolTime();


	UFUNCTION(BlueprintCallable)
		void Active_CoolTimeCount();

	UFUNCTION(BlueprintCallable)
		void DeActive_CoolTimeCount();

	UFUNCTION(BlueprintCallable)
		void SetCountHidden(bool bHidden);
	
	// 0~3까지(4개) 존재 0은 모두 꺼짐, 1은 하나켜짐, 3은 모두 켜짐
	UFUNCTION(BlueprintCallable)
		void SetCountUseActive(int32 nMaxIndex);

	void Tick_SkillCoolTime(float fDeltaTime);
	void Tick_SkillCoolTimeCount(float fDeltaTime);


	UFUNCTION(BlueprintPure)
		FORCEINLINE bool GetActive() { return m_bActive; }

	UFUNCTION(BlueprintPure)
		FORCEINLINE bool GetCoolTimeState() { return m_bCoolTimeActive; }

	UFUNCTION(BlueprintPure)
		FORCEINLINE bool GetCoolTimeCountEmpty() { return m_bCoolTimeCount_WaitActive; }

	UFUNCTION(BlueprintPure)
		FORCEINLINE bool GetCoolTimeCountState() { return m_bCoolTimeCountActive; }
	
	UFUNCTION(BlueprintPure)
		FORCEINLINE class UProgressBar* GetGageProgress() {	return m_pCoolTime;	}
};
