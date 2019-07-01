// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Libraries/Components/PostProcessEffect/PostProcessEffect_Root.h"
#include "PPE_SlowMotion.generated.h"

/**
 * 
 */
UCLASS()
class REVENGER_API UPPE_SlowMotion : public UPostProcessEffect_Root
{
	GENERATED_BODY()
private:
	float m_fValue = 0.0f;

public:
	UPPE_SlowMotion();
	~UPPE_SlowMotion();

	virtual void Enter() override;
	virtual void End() override;
	virtual bool Tick_Effect(float fDeltaTime) override;
};
