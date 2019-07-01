// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Actor/Characters/Enemy/GBoxEnemy_Close/State/StateRoot_GBEClose.h"
#include "State_GBEC_DashAttack.generated.h"

/**
 * 
 */
UCLASS()
class REVENGER_API UState_GBEC_DashAttack : public UStateRoot_GBEClose
{
	GENERATED_BODY()
private :
	UPROPERTY()
		class AWarningSpace_Root* m_pWarning;

	UPROPERTY()
		class AActor* m_pTarget;

	bool m_bMotion = false;
	bool m_bRotation = false;

	bool m_bAttackAgo = false;
	bool m_bAttackReady = false;

	float m_fAttackAgoTime = 0.0f;
	float m_fAttackAgoTime_Ago = 3.0f;

	bool m_bAttack = false;

	FRotator m_pAttackRotator;
	FVector m_pStartPOs;
public:
	virtual void Init(class UStateMng_GC* pMng) override;
	virtual void Enter() override;
	virtual void Exit() override;
	virtual void Update(float fDeltaTime) override;
	virtual void StateMessage(FString sMessage) override;

	void SetTarget(AActor* pTarget) { m_pTarget = pTarget; }
};

