// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Revenger.h"
#include "Actor/Characters/Enemy/GBoxEnemy_Close/StateAI/StateRootAI_GBEClose.h"
#include "StateAI_GBEC_Combat_DistMove.generated.h"

/**
 * 
 */
UCLASS()
class REVENGER_API UStateAI_GBEC_Combat_DistMove : public UStateRootAI_GBEClose
{
	GENERATED_BODY()

private:
	float m_fCombatTime_Curr = 0.0f;
	float m_fCombatTime_End = 0.0f;

	float m_fStayDistance = 650.0f;

public:
	virtual void Init(class UStateMng_AI* pMng) override;
	virtual void Enter() override;
	virtual void Exit() override;
	virtual void Update(float fDeltaTime) override;
	virtual void StateMessage(FString sMessage) override;
};
