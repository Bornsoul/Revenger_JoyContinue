// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Actor/Characters/Enemy/E5/State/StateRoot_EnemyE5.h"
#include "State_EnemyE5_Attack.generated.h"

/**
 * 
 */
UCLASS()
class REVENGER_API UState_EnemyE5_Attack : public UStateRoot_EnemyE5
{
	GENERATED_BODY()

private:
	UPROPERTY()
		class AActor* m_pTargetActor;

	UPROPERTY()
		class UParticleSystemComponent* m_pLaserParticle;

	UPROPERTY()
		class UParticleSystemComponent* m_pLaserParticleL;

	bool m_bLaserTime = false;
	float m_fLaserTime = 0.0f;
	float m_fLaserTime_Ago = 0.5f;

	bool m_bAttackTime = false;
	float m_fAttackTime_Cur = 0.0f;
	float m_fAttackTime_End = 1.0f;

	bool m_bLeft = false;

	int32 m_nFireCount = 0;

public:
	virtual void Init(class UStateMng_GC* pMng) override;
	virtual void Enter() override;
	virtual void Exit() override;
	virtual void Update(float fDeltaTime) override;
	virtual void StateMessage(FString sMessage) override;

	void SetTarget(class AActor* pTarget) { m_pTargetActor = pTarget; }
};
