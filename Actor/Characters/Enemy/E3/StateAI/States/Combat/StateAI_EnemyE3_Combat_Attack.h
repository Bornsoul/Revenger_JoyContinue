// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Revenger.h"
#include "Actor/Characters/Enemy/E3/StateAI/StateRoot_AI_EnemyE3.h"
#include "StateAI_EnemyE3_Combat_Attack.generated.h"

/**
 * 
 */
UCLASS()
class REVENGER_API UStateAI_EnemyE3_Combat_Attack : public UStateRoot_AI_EnemyE3
{
	GENERATED_BODY()

private:
	float m_fDist_Attack = 300.0f;
	bool m_bMovement = false;

	FVector m_vEnemyPos;

public:
	virtual void Init(class UStateMng_AI* pMng) override;
	virtual void Enter() override;
	virtual void Exit() override;
	virtual void Update(float fDeltaTime) override;
	virtual void StateMessage(FString sMessage) override;
};
