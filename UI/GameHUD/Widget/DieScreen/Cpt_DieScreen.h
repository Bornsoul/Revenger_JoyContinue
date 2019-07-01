// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Revenger.h"
#include "Components/ActorComponent.h"
#include "Cpt_DieScreen.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class REVENGER_API UCpt_DieScreen : public UActorComponent
{
	GENERATED_BODY()

private:
	UPROPERTY()
		TSubclassOf<class UWidget_Die> m_pInst_Widget;

	UPROPERTY()
		class UWidget_Die* m_pWidget;

	UPROPERTY()
		class UCpt_KeyStateMng* m_pKeyStateMng;

	bool m_bActive = false;
	
	bool m_bDieStart = false;
	float m_fDieStartTime_Cur = 0.0f;
	float m_fDieStartTime_End = 0.0f;	

	bool m_bKeyTime = false;
	float m_fKeyTime_Cur = 0.0f;
	float m_fKeyTime_End = 2.0f;

public:	
	UCpt_DieScreen();

	virtual void BeginPlay() override;
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	void Active_Die(float fDieStartTime = 1.0f);
	void DeActive_Die();

	bool GetActive() { return m_bActive; }
	bool GetAniPlaying();
	int32 Menu_GetButton();
};
