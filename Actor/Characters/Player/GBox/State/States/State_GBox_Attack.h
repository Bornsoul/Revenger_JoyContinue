// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Revenger.h"
#include "Actor/Characters/Player/GBox/State/StateRoot_GBox.h"
#include "State_GBox_Attack.generated.h"

/**
 * 
 */
UCLASS()
class REVENGER_API UState_GBox_Attack : public UStateRoot_GBox
{
	GENERATED_BODY()

private:
	bool m_bMotionEnd = false;
	bool m_bRotation = false;

	FVector m_vMouseLoc;

	bool m_bAttackMotionEnd = false;

public:
	virtual void Init(class UStateMng_GC* pMng) override;
	virtual void Enter() override;
	virtual void Exit() override;
	virtual void Update(float fDeltaTime) override;
	virtual void StateMessage(FString sMessage) override;

	void SetDirection(FVector vLoc);
	void SetRotateMotion(float fDeltaTime, FVector vLook, float fSpeed);

public :
	void Attack();
	void Tick_Attack(float fDeltaTime);
	void AttackEnd();

	bool m_bAttack = false;
	float m_fAttackTime;
	TArray<FString> m_sOverlapName;

	bool CheckParring(FVector vAttackLoc);
};
