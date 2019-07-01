// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Widget_SlowTimeGage.generated.h"


UCLASS()
class REVENGER_API UWidget_SlowTimeGage : public UUserWidget
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

	UPROPERTY()
		class AActor* m_pRootChar;

	FVector2D vWidgetPos;
	float m_fGageValue = 0.0f;
	float m_fGageSpeed = 2.0f;
	bool m_bActive = true;
	bool m_bShow = false;



	FVector vColor;
public:
	virtual void NativeConstruct() override;
	virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime) override;
	
	void SetShow(bool bShow);
	void SetValue(float fVal);
	
	void SetInit(class AActor* pActor, FVector2D vPos);
	void SetActive(bool bActive);

	void Tick_Target(AActor* pActor);

private:
	void Tick_Position();

public:
	FORCEINLINE class UWidgetAni_Mng* GetAnimation() { return m_pWidgetAni; }
	FORCEINLINE class AActor* GetRoot() { return m_pRootChar; }
	FORCEINLINE bool GetActive() { return m_bActive;  }
	FORCEINLINE bool GetShow() { return m_bShow; }
};
