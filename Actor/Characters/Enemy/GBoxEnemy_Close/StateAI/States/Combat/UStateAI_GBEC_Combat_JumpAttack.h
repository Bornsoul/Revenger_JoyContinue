// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Revenger.h"
#include "Actor/Characters/Enemy/GBoxEnemy_Close/StateAI/StateRootAI_GBEClose.h"
#include "UStateAI_GBEC_Combat_JumpAttack.generated.h"

/**
 * 
 */
UCLASS()
class REVENGER_API UUStateAI_GBEC_Combat_JumpAttack : public UStateRootAI_GBEClose
{
	GENERATED_BODY()
private:
	float m_fDist_Attack = 300.0f;
	bool m_bMovement = false;

	FVector m_vEnemyPos;

public:
	virtual void Init(class UStateMng_AI* pMng) override;
	virtual void Enter() override;
	virtual void Exit() override;
	virtual void Update(float fDeltaTime) override;
	virtual void StateMessage(FString sMessage) override;
};

