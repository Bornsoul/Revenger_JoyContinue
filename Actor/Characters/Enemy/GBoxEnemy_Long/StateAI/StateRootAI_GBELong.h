// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "../AIC_GBoxEnemy_Long.h"

#include "Revenger.h"
#include "Actor/Characters/StateRootAI/StateRoot_AI.h"
#include "StateRootAI_GBELong.generated.h"

/**
 * 
 */
UCLASS()
class REVENGER_API UStateRootAI_GBELong : public UStateRoot_AI
{
	GENERATED_BODY()

protected:
	UPROPERTY()
		class UStateMngAI_GBELong* m_pStateMng_Override;

public:
	UStateRootAI_GBELong();
	virtual ~UStateRootAI_GBELong();

	virtual void Init(class UStateMng_AI* pMng) override;
	virtual void Enter() override;
	virtual void Exit() override;
	virtual void Update(float fDeltaTime) override;
	virtual void StateMessage(FString sMessage) override;

	class AAIC_GBoxEnemy_Long* GetRootAI();
};
