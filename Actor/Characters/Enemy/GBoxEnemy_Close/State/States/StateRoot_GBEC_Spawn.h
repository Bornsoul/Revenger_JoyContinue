// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Actor/Characters/Enemy/GBoxEnemy_Close/State/StateRoot_GBEClose.h"
#include "StateRoot_GBEC_Spawn.generated.h"

/**
 * 
 */
UCLASS()
class REVENGER_API UStateRoot_GBEC_Spawn : public UStateRoot_GBEClose
{
	GENERATED_BODY()

private:
	bool m_bMotionEnd = false;
	float m_fWaitTime = 0.0f;
	bool m_bLand = false;
public:
	virtual void Init(class UStateMng_GC* pMng) override;
	virtual void Enter() override;
	virtual void Exit() override;
	virtual void Update(float fDeltaTime) override;
	virtual void StateMessage(FString sMessage) override;

};