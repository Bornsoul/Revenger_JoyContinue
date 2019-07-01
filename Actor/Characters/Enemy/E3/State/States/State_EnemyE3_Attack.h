// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Actor/Characters/Enemy/E3/State/StateRoot_EnemyE3.h"
#include "State_EnemyE3_Attack.generated.h"

/**
 * 
 */
UCLASS()
class REVENGER_API UState_EnemyE3_Attack : public UStateRoot_EnemyE3
{
	GENERATED_BODY()
private:
	bool m_bMotion = true;

	float m_fReadyTime = 0.0f;
	bool m_bAttacked = false;

	class AActor* m_pTarget;

	UPROPERTY()
		class AWarningSpace_Root* m_pWarning;

public:
	virtual void Init(class UStateMng_GC* pMng) override;
	virtual void Enter() override;
	virtual void Exit() override;
	virtual void Update(float fDeltaTime) override;
	virtual void StateMessage(FString sMessage) override;

public:
	void Attack();
	void Tick_Attack(float fDeltaTime);
	void AttackEnd();

	bool m_bAttack = false;
	float m_fAttackTime;
	TArray<FString> m_sOverlapName;


	void SetTarget(AActor* pTarget) { m_pTarget = pTarget; }
};
