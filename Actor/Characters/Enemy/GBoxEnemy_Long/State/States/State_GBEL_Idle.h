// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Revenger.h"
#include "Actor/Characters/Enemy/GBoxEnemy_Long/State/StateRoot_GBELong.h"
#include "State_GBEL_Idle.generated.h"

/**
 * 
 */
UCLASS()
class REVENGER_API UState_GBEL_Idle : public UStateRoot_GBELong
{
	GENERATED_BODY()

private:

public:
	virtual void Init(class UStateMng_GC* pMng) override;
	virtual void Enter() override;
	virtual void Exit() override;
	virtual void Update(float fDeltaTime) override;
	virtual void StateMessage(FString sMessage) override;
};
