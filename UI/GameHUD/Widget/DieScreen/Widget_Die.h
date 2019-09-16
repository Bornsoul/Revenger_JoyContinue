// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Revenger.h"
#include "Blueprint/UserWidget.h"
#include "Widget_Die.generated.h"

UENUM()
enum class E_Button_Die : uint8
{
	E_NONE UMETA(DisplayName = "None"),
	E_RESTART UMETA(DisplayName = "Restart"),	
	E_QUIT UMETA(DisplayName = "Quit"),

	E_MAX,
};


UCLASS()
class REVENGER_API UWidget_Die : public UUserWidget
{
	GENERATED_BODY()
	
private:
	UPROPERTY()
		class UWidgetAni_Mng* m_pWidgetAni;

	UPROPERTY()
		class UTextBlock* m_pDieTimeLabel;
	
	bool m_bActive = false;
	bool m_bRevers = false;
	bool m_bDestroy = false;

	bool m_bAniPlaying = false;

	int32 m_nState;

	float m_fDieTime_Val = 0.0f;
	bool m_bDieTime = false;

public:
	virtual void NativeConstruct() override;
	virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime) override;
	virtual void NativeDestruct() override;

	UFUNCTION(BlueprintCallable)
		void SetPlayAnimation(FString sAniName, bool bRevers = false);

	UFUNCTION(BlueprintCallable)
		void SetActive(bool bActive);

	UFUNCTION(BlueprintCallable)
		void SetButtonState(int32 nState);

	UFUNCTION(BlueprintCallable)
		void Menu_Destory();

	UFUNCTION(BlueprintCallable)
		void Menu_Button(E_Button_Die eState);

	UFUNCTION(BlueprintCallable)
		void SetAniPlaying(bool bPlaying) { m_bAniPlaying = bPlaying; }

	UFUNCTION(BlueprintCallable)
		void SetDieText(FString sStr);
	
	UFUNCTION(BlueprintCallable)
		void Active_DieTime(float fDieTime);

	void DeActive_DieTime();

	UFUNCTION(BlueprintPure)
		FORCEINLINE int32 GetCurrentState() { return m_nState; }

	UFUNCTION(BlueprintPure)
		FORCEINLINE bool GetAniPlaying() { return m_bAniPlaying; }

	FORCEINLINE bool GetDestroy() { return m_bDestroy; }
	FORCEINLINE class UWidgetAni_Mng* GetAnimation() { return m_pWidgetAni; }
};
