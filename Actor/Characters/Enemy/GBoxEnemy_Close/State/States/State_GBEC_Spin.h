// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Actor/Characters/Enemy/GBoxEnemy_Close/State/StateRoot_GBEClose.h"
#include "State_GBEC_Spin.generated.h"

/**
 * 
 */
UCLASS()
class REVENGER_API UState_GBEC_Spin : public UStateRoot_GBEClose
{
	GENERATED_BODY()

private :
	bool m_bMotion = false;


	UPROPERTY()
		class AWarningSpace_Root* m_pWarning;

public:
	virtual void Init(class UStateMng_GC* pMng) override;
	virtual void Enter() override;
	virtual void Exit() override;
	virtual void Update(float fDeltaTime) override;
	virtual void StateMessage(FString sMessage) override;

	//void SetTarget(AActor* pTarget) { m_pTarget = pTarget; }
};
