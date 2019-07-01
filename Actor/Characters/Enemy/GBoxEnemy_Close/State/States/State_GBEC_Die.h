// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Actor/Characters/Enemy/GBoxEnemy_Close/State/StateRoot_GBEClose.h"
#include "State_GBEC_Die.generated.h"

/**
 * 
 */
UCLASS()
class REVENGER_API UState_GBEC_Die : public UStateRoot_GBEClose
{
	GENERATED_BODY()

private:
	bool m_bMotionEnd = false;
	FVector m_vHitDirection;

	float m_fKillingDamage;
	FDamageEvent_Hit m_pDamageEvent;

	UPROPERTY()
	APawn * m_pPawnInstigator;

	UPROPERTY()
	AActor * m_pDamageCauser;

	bool m_bRagdoll = false;
	float m_fStiffenTime = 0.0f;

public:
	virtual void Init(class UStateMng_GC* pMng) override;
	virtual void Enter() override;
	virtual void Exit() override;
	virtual void Update(float fDeltaTime) override;
	virtual void StateMessage(FString sMessage) override;

public:	
	FString GetHitDirection();
	void SetHitDirection(FVector vHitDirection) { m_vHitDirection = vHitDirection; }
};
