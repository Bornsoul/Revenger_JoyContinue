// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Actor/Characters/Enemy/GBoxEnemy_Close/State/StateRoot_GBEClose.h"
#include "State_GBEC_JumpAttack.generated.h"

/**
 * 
 */
UCLASS()
class REVENGER_API UState_GBEC_JumpAttack : public UStateRoot_GBEClose
{
	GENERATED_BODY()
private:
	bool m_bMotion = true;

	float m_fReadyTime = 0.0f;
	bool m_bAttacked = false;

	UPROPERTY()
		class AActor* m_pTarget;

	bool m_bJump = false;

	FVector m_vDestLoc;

	bool m_bRotation = false;

	UPROPERTY()
	class AWarningSpace_Root* m_pWarning;

public:
	virtual void Init(class UStateMng_GC* pMng) override;
	virtual void Enter() override;
	virtual void Exit() override;
	virtual void Update(float fDeltaTime) override;
	virtual void StateMessage(FString sMessage) override;

	void SetTarget(AActor* pTarget) { m_pTarget = pTarget; }
};
