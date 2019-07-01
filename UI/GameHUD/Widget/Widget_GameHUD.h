// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Revenger.h"
#include "Blueprint/UserWidget.h"
#include "Widget_GameHUD.generated.h"

UENUM()
enum class E_State_SkillType : uint8
{
	E_SKILL_LCLICK,
	E_SKILL_SHIFT,
	E_SKILL_SPACE,

	E_MAX,
};

UCLASS()
class REVENGER_API UWidget_GameHUD : public UUserWidget
{
	GENERATED_BODY()
	
private:
	UPROPERTY()
		TArray<class UWidget_PlayerDash*> m_pGageArr;

	UPROPERTY()
		TArray<class UWidget_PlayerKeyInfo*> m_pSkillArr;

	UPROPERTY()
		class UTextBlock* m_pStageTxt;

	UPROPERTY()
		class UWidgetAni_Mng* m_pWidgetAni;

	bool m_bUseSlow = false;
	bool m_bActive = false;

	float m_fDashTime_Curr = 0.0f;
	float m_fDashTime_End = 1.0f;

public:
	virtual void NativeConstruct() override;
	virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime) override;

	void SetShow(bool bShow);

	//! Dash Count 
	void InitDash();	
	void DashTick_AddDash(float fDeltaTime);
	bool AddDash();	
	bool RemoveDash();
	bool GetDashAllEmpty();
	
	//! Skill Info
	void InitKeyInfo(float fKey1 = 0.0f, float fKey2 = 0.0f, float fKey3 = 0.0f);
	void Active_KeyCoolTime(int32 nSelect);	
	bool GetCoolTimeCheck(int32 nSelect); //! ƒ≈∏¿”¿Œ¡ˆ √º≈©«ÿ¡‹.

	//! StateName Info
	void SetStageName(FString sName);

public:
	//FORCEINLINE class UWidget_PlayerDash* GetDash() { return m_pGage; }
	FORCEINLINE TArray<class UWidget_PlayerDash*> GetDashList() { return m_pGageArr; }
	FORCEINLINE class UTextBlock* GetStageName() { return m_pStageTxt; }
	FORCEINLINE bool GetActive() { return m_bActive; }
};
