// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Libraries/Components/PostProcessEffect/PostProcessEffect_Root.h"
#include "PPE_ChromaticBlur.generated.h"

/**
 * 
 */
UCLASS()
class REVENGER_API UPPE_ChromaticBlur : public UPostProcessEffect_Root
{
	GENERATED_BODY()

private:
	float m_fValue = 0.0f;

	float m_fColorValue = 0.0f;

	float m_fTime;
	float m_fAgoTime;

	bool m_bPingPong = false;


	int m_nState = 0;

public:
	UPPE_ChromaticBlur();
	~UPPE_ChromaticBlur();

	virtual void Enter() override;
	virtual void End() override;
	virtual bool Tick_Effect(float fDeltaTime) override;
};
