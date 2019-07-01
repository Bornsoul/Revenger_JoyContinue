// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Actor/Characters/Enemy/GBoxEnemy_Long/State/StateRoot_GBELong.h"
#include "State_GBEL_Attack.generated.h"

/**
 * 
 */
UCLASS()
class REVENGER_API UState_GBEL_Attack : public UStateRoot_GBELong
{
	GENERATED_BODY()

private:
	UPROPERTY()
		class AActor* m_pTargetActor;

	UPROPERTY()
		class UParticleSystemComponent* m_pLaserParticle;

	bool m_bLaserTime = false;
	float m_fLaserTime = 0.0f;
	float m_fLaserTime_Ago = 0.5f;

	bool m_bLeft = false;

public:
	virtual void Init(class UStateMng_GC* pMng) override;
	virtual void Enter() override;
	virtual void Exit() override;
	virtual void Update(float fDeltaTime) override;
	virtual void StateMessage(FString sMessage) override;

	void SetTarget(class AActor* pTarget);
};
