// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Libraries/Components/PostProcessEffect/PostProcessEffect_Root.h"
#include "PPE_PlayerHit.generated.h"

/**
 * 
 */
UCLASS()
class REVENGER_API UPPE_PlayerHit : public UPostProcessEffect_Root
{
	GENERATED_BODY()

private:
	float m_fValue = 0.0f;
	bool m_bPingPong = false;

	float m_fCurrTime = 0.0f;

public:
	UPPE_PlayerHit();
	~UPPE_PlayerHit();

	virtual void Enter() override;
	virtual void End() override;
	virtual bool Tick_Effect(float fDeltaTime) override;
};
