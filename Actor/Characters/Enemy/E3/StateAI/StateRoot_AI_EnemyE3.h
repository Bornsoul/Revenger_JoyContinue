// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "../AIC_EnemyE3.h"

#include "Revenger.h"
#include "Actor/Characters/StateRootAI/StateRoot_AI.h"
#include "StateRoot_AI_EnemyE3.generated.h"

/**
 * 
 */
UCLASS()
class REVENGER_API UStateRoot_AI_EnemyE3 : public UStateRoot_AI
{
	GENERATED_BODY()
protected:
	UPROPERTY()
		class UStateMng_AI_EnemyE3* m_pStateMng_Override;

public:
	UStateRoot_AI_EnemyE3();
	virtual ~UStateRoot_AI_EnemyE3();

	virtual void Init(class UStateMng_AI* pMng) override;
	virtual void Enter() override;
	virtual void Exit() override;
	virtual void Update(float fDeltaTime) override;
	virtual void StateMessage(FString sMessage) override;

	class AAIC_EnemyE3* GetRootAI();
};
