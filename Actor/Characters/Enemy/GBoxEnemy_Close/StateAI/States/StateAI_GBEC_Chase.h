// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Revenger.h"
#include "Actor/Characters/Enemy/GBoxEnemy_Close/StateAI/StateRootAI_GBEClose.h"
#include "StateAI_GBEC_Chase.generated.h"

/**
 * 
 */
UCLASS()
class REVENGER_API UStateAI_GBEC_Chase : public UStateRootAI_GBEClose
{
	GENERATED_BODY()

private:
	UPROPERTY()
		class AActor* m_pChaseTarget = nullptr;

	FVector m_vEnemyPos;
	FVector m_vTargetPos;

	float m_fTargetTime_Curr = 0.0f;
	float m_fTargetTime_End = 0.05f;

	float m_fDist_Combat = 350.0f;
	float m_fDist_Lost = 1000.0f;

public:
	virtual void Init(class UStateMng_AI* pMng) override;
	virtual void Enter() override;
	virtual void Exit() override;
	virtual void Update(float fDeltaTime) override;
	virtual void StateMessage(FString sMessage) override;

public:
	void SetChaseTarget(class AActor* pTarget);
};
