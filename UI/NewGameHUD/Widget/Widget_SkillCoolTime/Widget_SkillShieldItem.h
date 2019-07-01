// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Widget_SkillShieldItem.generated.h"

/**
 * 
 */
UCLASS()
class REVENGER_API UWidget_SkillShieldItem : public UUserWidget
{
	GENERATED_BODY()
	
private:
	UPROPERTY()
		class UWidgetAni_Mng* m_pWidgetAni;

	UPROPERTY()
		class UImage* m_pIcon;

	UPROPERTY()
		class UProgressBar* m_pCoolTime;


	// 기본 상태 이미지
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Skill Widget", meta = (AllowPrivateAccess = "true"))
		class UTexture2D* m_pIcon_Normal;

	// 사용중 상태 이미지
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Skill Widget", meta = (AllowPrivateAccess = "true"))
		class UTexture2D* m_pIcon_Shield;

	bool m_bActive = false;
	bool m_bRevers = false;

	// CoolTIme
	bool m_bCoolTimeActive = false;

	float m_fCoolTime_Cur = 0.0f;
	float m_fCoolTime_End = 0.0f;
	float m_fCoolTime_CurTime = 0.0f;
	float m_fCoolTime_Percent = 0.0f;
	float m_fCoolTime_Lerp = 0.0f;

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

	void Tick_SkillShieldCoolTime(float fDeltaTime);

	UFUNCTION(BlueprintPure)
		FORCEINLINE bool GetActive() { return m_bActive; }

	UFUNCTION(BlueprintPure)
		FORCEINLINE bool GetCoolTimeState() { return m_bCoolTimeActive; }
};
