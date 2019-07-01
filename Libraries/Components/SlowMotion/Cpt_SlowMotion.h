// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Revenger.h"
#include "Components/ActorComponent.h"
#include "Cpt_SlowMotion.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class REVENGER_API UCpt_SlowMotion : public UActorComponent
{
	GENERATED_BODY()

private:
	float m_fSlowActiveTime = 0.0f;
	float m_fSlowPower = 0.1f;
	float m_fChangeSpeed = 13.0f;

	int m_nStateCnt = 0;

	float m_fSlow_CurrentValue = 0.0f;


	float m_fRealTime = 0.0f;

	bool m_bActive = false;
public:
	UCpt_SlowMotion();
	virtual void BeginPlay() override;
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;


	void Active_SlowMotion(float fActiveTime, float fSlowPower = 0.1f, float fChangeSpeed = 26.0f);
	void DeActive_SlowMotion();

	bool GetActive() { return m_bActive; }
private:

	void Tick_SlowMotion(float fDeltatime);

	void Tick_Enter(float fDeltaTime);
	void Tick_Process(float fDeltaTime);
	void Tick_End(float fDeltaTime);
};
