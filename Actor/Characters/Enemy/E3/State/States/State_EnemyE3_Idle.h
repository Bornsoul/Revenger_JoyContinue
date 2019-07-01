// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Revenger.h"
#include "Actor/Characters/Enemy/E3/State/StateRoot_EnemyE3.h"
#include "State_EnemyE3_Idle.generated.h"

/**
 * 
 */
UCLASS()
class REVENGER_API UState_EnemyE3_Idle : public UStateRoot_EnemyE3
{
	GENERATED_BODY()
private:


public:
	virtual void Init(class UStateMng_GC* pMng) override;
	virtual void Enter() override;
	virtual void Exit() override;
	virtual void Update(float fDeltaTime) override;
	virtual void StateMessage(FString sMessage) override;
};
