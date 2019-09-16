// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Actor/Characters/Enemy/TutorialEnemy/State/StateRoot_TutorialEnemy.h"
#include "State_TutoEnemy_Die.generated.h"

/**
 * 
 */
UCLASS()
class REVENGER_API UState_TutoEnemy_Die : public UStateRoot_TutorialEnemy
{
	GENERATED_BODY()
	
private:
	bool m_bMotionEnd = false;
	FVector m_vHitDirection;

	bool m_bRagdoll = false;
	float m_fStiffenTime = 0.0f;

	bool m_bDestroy = false;

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
