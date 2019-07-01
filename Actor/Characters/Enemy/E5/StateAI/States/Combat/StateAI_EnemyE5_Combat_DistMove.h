// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Actor/Characters/Enemy/E5/StateAI/StateRoot_AI_EnemyE5.h"
#include "StateAI_EnemyE5_Combat_DistMove.generated.h"

/**
 * 
 */
UCLASS()
class REVENGER_API UStateAI_EnemyE5_Combat_DistMove : public UStateRoot_AI_EnemyE5
{
	GENERATED_BODY()

private:
	float m_fCombatTime_Curr = 0.0f;
	float m_fCombatTime_End = 0.0f;

	float m_fStayDistance = 700.0f;

public:
	virtual void Init(class UStateMng_AI* pMng) override;
	virtual void Enter() override;
	virtual void Exit() override;
	virtual void Update(float fDeltaTime) override;
	virtual void StateMessage(FString sMessage) override;
};
