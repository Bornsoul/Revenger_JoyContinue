// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Revenger.h"
#include "Actor/Characters/Enemy/GBoxEnemy_Long/StateAI/StateRootAI_GBELong.h"
#include "StateAI_GBEL_Combat_DistMove.generated.h"

/**
 * 
 */
UCLASS()
class REVENGER_API UStateAI_GBEL_Combat_DistMove : public UStateRootAI_GBELong
{
	GENERATED_BODY()

private:
	float m_fCombatTime_Curr = 0.0f;
	float m_fCombatTime_End = 0.0f;

	float m_fStayDistance = 450.0f;

public:
	virtual void Init(class UStateMng_AI* pMng) override;
	virtual void Enter() override;
	virtual void Exit() override;
	virtual void Update(float fDeltaTime) override;
	virtual void StateMessage(FString sMessage) override;
};
