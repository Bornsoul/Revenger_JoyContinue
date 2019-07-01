// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Actor/Characters/Enemy/E4/State/StateRoot_EnemyE4.h"
#include "State_EnemyE4_Attack.generated.h"

/**
 * 
 */
UCLASS()
class REVENGER_API UState_EnemyE4_Attack : public UStateRoot_EnemyE4
{
	GENERATED_BODY()
private:
	UPROPERTY()
		class AActor* m_pTargetActor;

	UPROPERTY()
		class UParticleSystemComponent* m_pLaserParticle;

	bool m_bLaserTime = false;
	float m_fLaserTime = 0.0f;
	float m_fLaserTime_Ago = 0.8f;

	bool m_bLeft = false;

public:
	virtual void Init(class UStateMng_GC* pMng) override;
	virtual void Enter() override;
	virtual void Exit() override;
	virtual void Update(float fDeltaTime) override;
	virtual void StateMessage(FString sMessage) override;

	void SetTarget(class AActor* pTarget) { m_pTargetActor = pTarget; }
};
