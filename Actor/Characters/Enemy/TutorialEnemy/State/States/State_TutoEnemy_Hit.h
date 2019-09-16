// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Actor/Characters/Enemy/TutorialEnemy/State/StateRoot_TutorialEnemy.h"
#include "State_TutoEnemy_Hit.generated.h"

/**
 * 
 */
UCLASS()
class REVENGER_API UState_TutoEnemy_Hit : public UStateRoot_TutorialEnemy
{
	GENERATED_BODY()
	
private:
	bool m_bMotionEnd = false;
	FVector m_vHitDirection;

	float	m_fKnockBackTIme = 0.0f;
	bool	 m_bKnockBacked = false;

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
