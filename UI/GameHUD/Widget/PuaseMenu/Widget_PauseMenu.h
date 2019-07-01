// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Widget_PauseMenu.generated.h"

UENUM()
enum class E_Button_Pause : uint8
{
	E_NONE UMETA(DisplayName = "None"),
	E_RESUME UMETA(DisplayName = "Resume"),
	E_RESTART UMETA(DisplayName = "ReStart"),
	E_QUIT UMETA(DisplayName = "Quit"),

	E_MAX,
};

UCLASS()
class REVENGER_API UWidget_PauseMenu : public UUserWidget
{
	GENERATED_BODY()

private:
	UPROPERTY()
		class UWidgetAni_Mng* m_pWidgetAni;

	bool m_bRevers = false;
	bool m_bActive = false;
	bool m_bDestroy = false;

	bool m_bAniPlaying = false;

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
		void Menu_Button(E_Button_Pause eState);

	UFUNCTION(BlueprintCallable)
		void SetAniPlaying(bool bPlaying) { m_bAniPlaying = bPlaying; }
	FORCEINLINE class UWidgetAni_Mng* GetAnimation() { return m_pWidgetAni; }

	UFUNCTION(BlueprintPure)
		FORCEINLINE int32 GetCurrentState() { return m_nState; }

	UFUNCTION(BlueprintPure)
		FORCEINLINE bool GetAniPlaying() { return m_bAniPlaying; }

	FORCEINLINE bool GetDestroy() { return m_bDestroy; }
};