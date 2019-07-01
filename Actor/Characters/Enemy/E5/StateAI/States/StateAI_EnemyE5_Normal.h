// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Actor/Characters/Enemy/E5/StateAI/StateRoot_AI_EnemyE5.h"
#include "StateAI_EnemyE5_Normal.generated.h"

/**
 * 
 */
UCLASS()
class REVENGER_API UStateAI_EnemyE5_Normal : public UStateRoot_AI_EnemyE5
{
	GENERATED_BODY()
	
private:


public:
	virtual void Init(class UStateMng_AI* pMng) override;
	virtual void Enter() override;
	virtual void Exit() override;
	virtual void Update(float fDeltaTime) override;
	virtual void StateMessage(FString sMessage) override;
};
