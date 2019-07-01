// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Revenger.h"
#include "Components/ActorComponent.h"
#include "Cpt_ResultWidget.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class REVENGER_API UCpt_ResultWidget : public UActorComponent
{
	GENERATED_BODY()

private:
	UPROPERTY()
		TSubclassOf<class UWidget_ResultHUD> m_pInst_Widget;

	UPROPERTY()
		class UWidget_ResultHUD* m_pWidget;

	bool m_bActive = false;
	bool m_bEndTime = false;
	float m_fEndTime_Cur = 0.0f;
	float m_fEndTime_End = 10.0f;

public:
	UCpt_ResultWidget();
	virtual void BeginPlay() override;
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	void Active_HUD();
	void SetDataInit(TArray<FString> pItemTextList);
	void DeActive_HUD();
	
	FORCEINLINE bool Get_Active() { return m_bActive; }
	FORCEINLINE void Set_Active(bool bActive) { m_bActive = bActive; }
};
