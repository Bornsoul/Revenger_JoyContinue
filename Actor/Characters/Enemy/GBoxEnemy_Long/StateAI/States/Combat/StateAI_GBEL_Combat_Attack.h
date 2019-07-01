// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Revenger.h"
#include "Actor/Characters/Enemy/GBoxEnemy_Long/StateAI/StateRootAI_GBELong.h"
#include "StateAI_GBEL_Combat_Attack.generated.h"

/**
 * 
 */
UCLASS()
class REVENGER_API UStateAI_GBEL_Combat_Attack : public UStateRootAI_GBELong
{
	GENERATED_BODY()

private:
	float m_fDist_Attack = 2000.0f;
	bool m_bMovement = false;

	FVector m_vEnemyPos;

	float m_fShootTime_Curr = 0.0f;
	float m_fShootTime_End = 1.0f;

	float m_fMoveTime_Curr = 0.0f;
	float m_fMoveTime_End = 0.0f;	

	float m_fStayDistance = 600.0f;


public:
	virtual void Init(class UStateMng_AI* pMng) override;
	virtual void Enter() override;
	virtual void Exit() override;
	virtual void Update(float fDeltaTime) override;
	virtual void StateMessage(FString sMessage) override;
};
