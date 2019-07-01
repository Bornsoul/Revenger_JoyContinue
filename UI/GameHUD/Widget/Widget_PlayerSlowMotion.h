// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Components/ProgressBar.h"
#include "Components/TextBlock.h"

#include "Revenger.h"
#include "Blueprint/UserWidget.h"
#include "Widget_PlayerSlowMotion.generated.h"

UENUM()
enum class E_State_SlowTime : uint8
{
	E_SLOW_NONE,
	E_SLOW_START,
	E_SLOW_END,

	E_MAX,
};

UCLASS()
class REVENGER_API UWidget_PlayerSlowMotion : public UUserWidget
{
	GENERATED_BODY()
	
private:
	UPROPERTY()
		class UImage* m_pGage;

	UPROPERTY()
		class UTextBlock* m_pGageValueText;

	UPROPERTY()
		class UWidgetAni_Mng* m_pWidgetAni;

	UPROPERTY()
		class UMaterialInterface* m_pMaterialInstance;

	UPROPERTY()
		class UMaterialInstanceDynamic* m_pMaterialDynamic;

	//! Slow InProcess Speed
	//! 슬로우가 진행될때 닳는 속도
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = AUser_Option, Meta = (AllowPrivateAccess = true))
		float m_fUseSpeed = 0.0f;
	
	//! Slow EndProcess Speed
	//! 슬로우를 끝냈을때 차오르는 속도
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = AUser_Option, Meta = (AllowPrivateAccess = true))
		float m_fFullSpeed = 0.0f;


	float m_fCurrValue_Front = 0.0f;
	float m_fPerValue = 0.0f;

	float m_fValue = 0.0f;

	bool m_bUseSlow = false;	
	bool m_bEmptySlow = false;

	int32 m_eSlowState;

public:
	virtual void NativeConstruct() override;
	virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime) override;

	void SetInit(float fGage);
	void SetShow(bool bShow);	
	void SetPercent(float fValue);	

	void ChangeSlowState(int32 eState);
	void SlowTick_None(float fDeltaTime);
	void SlowTick_Start(float fDeltaTime);
	void SlowTick_End(float fDeltaTime);

public:
	FORCEINLINE class UWidgetAni_Mng* GetAnimation() { return m_pWidgetAni; }	
	FORCEINLINE bool GetSlowEmpty() { return m_bEmptySlow; }
};
