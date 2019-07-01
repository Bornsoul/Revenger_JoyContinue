// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Components/ProgressBar.h"
#include "Components/Image.h"
#include "Components/TextBlock.h"
#include "Runtime/UMG/Public/Animation/WidgetAnimation.h"
#include "Runtime/SlateCore/Public/Styling/SlateBrush.h"

#include "Revenger.h"
#include "Blueprint/UserWidget.h"
#include "Widget_PlayerKeyInfo.generated.h"

UENUM()
enum class E_State_SkillTime : uint8
{
	E_SKILL_NONE,
	E_SKILL_START,
	E_SKILL_END,

	E_MAX,
};

UCLASS()
class REVENGER_API UWidget_PlayerKeyInfo : public UUserWidget
{
	GENERATED_BODY()

private:
	UPROPERTY()
		class UProgressBar* m_pCoolTime;

	UPROPERTY()
		class UImage* m_pIcon;	

	UPROPERTY()
		class UTextBlock* m_pKeyText;
	
	//! Skill Key Name
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = AUser_Option, Meta = (AllowPrivateAccess = true))
		FString m_sKeyName;

	//! Skill Icon Image
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = AUser_Option, Meta = (AllowPrivateAccess = true))
		UTexture2D* m_pImage;

	UPROPERTY()
		class UWidgetAni_Mng* m_pWidgetAni;

	//! CoolTime Speed
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = AUser_Option, Meta = (AllowPrivateAccess = true))
		float m_fCoolTimepeed = 0.5f;

private:
	int32 m_eState;
	float m_fCoolTime_Curr = 0.0f;
	float m_fCoolTime_Max = 1.0f;
	
	float m_fInterep = 0.0f;	
	float m_fInterepValue = 0.0f;

	bool m_bCoolTime = false;

public:
	virtual void NativePreConstruct() override;
	virtual void NativeConstruct() override;
	virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime) override;	

	void SetInit(float fCoolTimeSpeed);

	void ChangeState(int32 eState);
	void SkillTick_None(float fDeltaTime);
	void SkillTick_Start(float fDeltaTime);
	void SkillTick_End(float fDeltaTime);

	void SetValue(float fPercent);
	void CoolTimeEffect();

public:
	FORCEINLINE bool GetCoolTime() { return m_bCoolTime;  }
};
