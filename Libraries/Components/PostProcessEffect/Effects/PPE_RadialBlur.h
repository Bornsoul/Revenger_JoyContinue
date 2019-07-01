// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Libraries/Components/PostProcessEffect/PostProcessEffect_Root.h"
#include "PPE_RadialBlur.generated.h"

/**
 * 
 */
UCLASS()
class REVENGER_API UPPE_RadialBlur : public UPostProcessEffect_Root
{
	GENERATED_BODY()

private:
	float m_fValue = 0.0f;

	float m_fColorValue = 0.0f;

	float m_fTime;
	float m_fAgoTime;

	bool m_bPingPong = false;

public:
	UPPE_RadialBlur();
	~UPPE_RadialBlur();

	virtual void Enter() override;
	virtual void End() override;
	virtual bool Tick_Effect(float fDeltaTime) override;
};
