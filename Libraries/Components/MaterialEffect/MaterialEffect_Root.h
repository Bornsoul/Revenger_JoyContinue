// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Revenger.h"
#include "UObject/NoExportTypes.h"
#include "MaterialEffect_Root.generated.h"

/**
 * 
 */
UCLASS()
class REVENGER_API UMaterialEffect_Root : public UObject
{
	GENERATED_BODY()

protected:
	bool m_bActive = false;
	UPROPERTY()
		class UCpt_MaterialEffect* m_pRootComp;

public:
	UMaterialEffect_Root();

	virtual void Init(class UCpt_MaterialEffect* pRootComp);
	virtual void Destroy();

	virtual void ActiveEffect();
	virtual void Tick_Effect(float fDeltaTime);
	virtual void EndEffect();

	bool GetActive() { return m_bActive; }
};
