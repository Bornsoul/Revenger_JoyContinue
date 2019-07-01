// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Widget_SkillItem.h"

#include "Revenger.h"
#include "Blueprint/UserWidget.h"
#include "Widget_SkillHUD.generated.h"

/**
 * 
 */
UCLASS()
class REVENGER_API UWidget_SkillHUD : public UUserWidget
{
	GENERATED_BODY()
	
private:
	UPROPERTY()
		class UWidgetAni_Mng* m_pWidgetAni;

	UPROPERTY()
		 TArray<class UWidget_SkillItem*> m_pSkillItemList;

	UPROPERTY()
		class UWidget_SkillShieldItem* m_pSkillShield;

	UPROPERTY(EditAnywhere)
		int32 m_nWidgetNum = 3;

	bool m_bActive = false;
	bool m_bRevers = false;

public:
	virtual void NativePreConstruct() override;
	virtual void NativeConstruct() override;
	virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime) override;

	void SetSkillEnter();

	UFUNCTION(BlueprintCallable)
		void SetActive(bool bActive);

	UFUNCTION(BlueprintCallable)
		void SetPlayAnimation(FString sAniName, bool bRevers = false);

	UFUNCTION(BlueprintCallable)
		void Active_CoolTime(int32 nIndex, float fCoolTime);

	UFUNCTION(BlueprintCallable)
		void Active_CoolTimeCount(int32 nIndex);

	UFUNCTION(BlueprintCallable)
		void Active_ShieldCoolTime(float fCoolTime);

	void Tick_SkillCoolTime(float fDeltaTime);
	void Tick_SkillCoolTimeCount(float fDeltaTime);
	void Tick_SkillShieldTime(float fDeltaTime);

	UFUNCTION(BlueprintPure)
		FORCEINLINE bool GetActive() { return m_bActive; }

	// 타이머가 돌고있으면 true 됨
	UFUNCTION(BlueprintPure)
		FORCEINLINE bool GetCoolTimeState(int32 nIndex) { return m_pSkillItemList[nIndex]->GetCoolTimeState(); }

	// 3카운트 모두 소진시 true 됨
	UFUNCTION(BlueprintPure)
		FORCEINLINE bool GetCoolTimeCountEmpty(int32 nIndex) { return m_pSkillItemList[nIndex]->GetCoolTimeCountEmpty(); }

	// 1개라도 카운트가 소진되면 true됨
	UFUNCTION(BlueprintPure)
		FORCEINLINE bool GetCoolTimeCountState(int32 nIndex) { return m_pSkillItemList[nIndex]->GetCoolTimeCountState(); }
};
