// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Revenger.h"
#include "Blueprint/UserWidget.h"
#include "Widget_SlowGageHUD.generated.h"

UENUM()
enum class E_State_SlowGageState : uint8
{
	E_SLOW_NONE,
	E_SLOW_ACTIVE,
	E_SLOW_DEACTIVE,

	E_MAX,
};

UCLASS()
class REVENGER_API UWidget_SlowGageHUD : public UUserWidget
{
	GENERATED_BODY()

private:
	UPROPERTY()
		class UWidgetAni_Mng* m_pWidgetAni;

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category = "Widget Option", meta = (AllowPrivateAccess = "true"))
		TArray<class UWidget_SlowArrowUp*> m_pGageList;

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category = "Widget Option", meta = (AllowPrivateAccess = "true"))
		class UWidget_SlowTime* m_pTimer;

	bool m_bActive = false;
	bool m_bRevers = false;

	int32 m_eState;

	float m_fLastValue = 0.0f;
	float m_fCurrentGage = 0.0f;
	float m_fGageValue = 0.0f;
	float m_fDeActiveGageVal = 0.0f;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Widget Option", meta = (AllowPrivateAccess = "true"))
		float m_fGageSpeed = 1.0f;

	bool m_bIsEmpty = false;

	float m_fRealTime = 0.0f;

public:
	virtual void NativePreConstruct() override;
	virtual void NativeConstruct() override;
	virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime) override;

	void SetSlowEnter(float fGageSpeed);
	void Tick_SlowGage(float fDeltaTime);

	UFUNCTION(BlueprintCallable)
		void SetActive(bool bActive);

	UFUNCTION(BlueprintCallable)
		void SetPlayAnimation(FString sAniName, bool bRevers = false);

	UFUNCTION(BlueprintCallable)
		void SetGagePercent(float fPer, bool bFull);

	UFUNCTION(BlueprintCallable)
		void Active_SlowGage();

	UFUNCTION(BlueprintCallable)
		void DeActive_SlowGage();	

	UFUNCTION(BlueprintPure)
		FORCEINLINE bool GetActive() { return m_bActive; }

	UFUNCTION(BlueprintPure)
		FORCEINLINE bool GetIsEmpty() { return m_bIsEmpty; }

	FORCEINLINE float GetDeActiveGageValue() { return m_fDeActiveGageVal; }
};
