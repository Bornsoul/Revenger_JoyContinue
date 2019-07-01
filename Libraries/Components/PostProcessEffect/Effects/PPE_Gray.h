// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Libraries/Components/PostProcessEffect/PostProcessEffect_Root.h"
#include "PPE_Gray.generated.h"

/**
 * 
 */
UCLASS()
class REVENGER_API UPPE_Gray : public UPostProcessEffect_Root
{
	GENERATED_BODY()

private:

	float m_fValue = 0.0f;
	float m_fValueCur = 0.0f;

	float m_fCurrTime = 0.0f;
	float m_fValueTime = 0.0f;

public:
	UPPE_Gray();
	~UPPE_Gray();

	virtual void Enter() override;
	virtual void End() override;
	virtual bool Tick_Effect(float fDeltaTime) override;
};
