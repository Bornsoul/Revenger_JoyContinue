// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Libraries/Components/MaterialEffect/MaterialEffect_Root.h"
#include "ME_CharacterHit.generated.h"

/**
 * 
 */
UCLASS()
class REVENGER_API UME_CharacterHit : public UMaterialEffect_Root
{
	GENERATED_BODY()

private:
	float m_fHitValue_Insensity;

	float m_fHitTime;
	float m_fCurrTime;

public:
	UME_CharacterHit();

	virtual void ActiveEffect() override;
	virtual void Tick_Effect(float fDeltaTime) override;
	virtual void EndEffect() override;
};
