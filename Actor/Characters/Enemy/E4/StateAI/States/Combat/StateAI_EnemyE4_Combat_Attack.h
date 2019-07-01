// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Revenger.h"
#include "Actor/Characters/Enemy/E4/StateAI/StateRoot_AI_EnemyE4.h"
#include "StateAI_EnemyE4_Combat_Attack.generated.h"

/**
 * 
 */
UCLASS()
class REVENGER_API UStateAI_EnemyE4_Combat_Attack : public UStateRoot_AI_EnemyE4
{
	GENERATED_BODY()
private:
	float m_fDist_Attack = 1000.0f;
	bool m_bMovement = false;

	FVector m_vEnemyPos;

	float m_fShootTime_Curr = 0.0f;
	float m_fShootTime_End = 1.0f;

	float m_fMoveTime_Curr = 0.0f;
	float m_fMoveTime_End = 0.0f;

	float m_fStayDistance = 600.0f;


public:
	virtual void Init(class UStateMng_AI* pMng) override;
	virtual void Enter() override;
	virtual void Exit() override;
	virtual void Update(float fDeltaTime) override;
	virtual void StateMessage(FString sMessage) override;

};
