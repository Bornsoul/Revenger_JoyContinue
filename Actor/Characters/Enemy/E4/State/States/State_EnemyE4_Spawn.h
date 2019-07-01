// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Actor/Characters/Enemy/E4/State/StateRoot_EnemyE4.h"
#include "State_EnemyE4_Spawn.generated.h"

/**
 * 
 */
UCLASS()
class REVENGER_API UState_EnemyE4_Spawn : public UStateRoot_EnemyE4
{
	GENERATED_BODY()
private:
	bool m_bMotionEnd = false;

public:
	virtual void Init(class UStateMng_GC* pMng) override;
	virtual void Enter() override;
	virtual void Exit() override;
	virtual void Update(float fDeltaTime) override;
	virtual void StateMessage(FString sMessage) override;

};