// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Revenger.h"
#include "Actor/Characters/Enemy/E4/StateAI/StateRoot_AI_EnemyE4.h"
#include "State_AI_EnemyE4_Normal.generated.h"

/**
 * 
 */
UCLASS()
class REVENGER_API UState_AI_EnemyE4_Normal : public UStateRoot_AI_EnemyE4
{
	GENERATED_BODY()
private:


public:
	virtual void Init(class UStateMng_AI* pMng) override;
	virtual void Enter() override;
	virtual void Exit() override;
	virtual void Update(float fDeltaTime) override;
	virtual void StateMessage(FString sMessage) override;
};
