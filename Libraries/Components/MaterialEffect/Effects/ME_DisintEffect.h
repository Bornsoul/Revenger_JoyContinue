// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Libraries/Components/MaterialEffect/MaterialEffect_Root.h"
#include "ME_DisintEffect.generated.h"

/**
 * 
 */
UCLASS()
class REVENGER_API UME_DisintEffect : public UMaterialEffect_Root
{
	GENERATED_BODY()
private:
	float m_fInterF = 0.0f;

public:
	UME_DisintEffect();

	virtual void ActiveEffect() override;
	virtual void Tick_Effect(float fDeltaTime) override;
	virtual void EndEffect() override;
};
