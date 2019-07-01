// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Actor/Characters/Enemy/E5/State/StateRoot_EnemyE5.h"
#include "State_EnemyE5_Idle.generated.h"

/**
 * 
 */
UCLASS()
class REVENGER_API UState_EnemyE5_Idle : public UStateRoot_EnemyE5
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
