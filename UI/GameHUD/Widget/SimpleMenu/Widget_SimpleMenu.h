// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "UI/Core/WidgetAni_Mng.h"

#include "Revenger.h"
#include "Blueprint/UserWidget.h"
#include "Widget_SimpleMenu.generated.h"

UENUM()
enum class E_Button_State : uint8
{
	E_NONE UMETA(DisplayName = "None"),
	E_START UMETA(DisplayName = "Start"),
	E_QUIT UMETA(DisplayName = "Quit"),

	E_MAX,
};

UCLASS()
class REVENGER_API UWidget_SimpleMenu : public UUserWidget
{
	GENERATED_BODY()
	
private:
	UPROPERTY()
		class UWidgetAni_Mng* m_pWidgetAni;

	bool m_bRevers = false;
	bool m_bActive = false;
	bool m_bDestroy = false;

	int32 m_nState;
		
public:
	virtual void NativeConstruct() override;
	virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime) override;
	
	UFUNCTION(BlueprintCallable)
		void SetPlayAnimation(FString sAniName, bool bRevers = false);

	UFUNCTION(BlueprintCallable)
		void SetActive(bool bActive);

	UFUNCTION(BlueprintCallable)
		void Menu_Destory();

	UFUNCTION(BlueprintCallable)
		void SetButtonState(int32 nState);

	UFUNCTION(BlueprintCallable)
		void Menu_Start();

	UFUNCTION(BlueprintCallable)
		void Menu_Quit();

	FORCEINLINE class UWidgetAni_Mng* GetAnimation() { return m_pWidgetAni; }

	UFUNCTION(BlueprintPure)
		FORCEINLINE int32 GetCurrentState() { return m_nState; }

	FORCEINLINE bool GetDestroy() { return m_bDestroy; }
};