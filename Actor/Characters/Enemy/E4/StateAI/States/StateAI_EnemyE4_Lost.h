// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Actor/Characters/Enemy/E4/StateAI/StateRoot_AI_EnemyE4.h"
#include "StateAI_EnemyE4_Lost.generated.h"

/**
 * 
 */
UCLASS()
class REVENGER_API UStateAI_EnemyE4_Lost : public UStateRoot_AI_EnemyE4
{
	GENERATED_BODY()
private:
	FVector m_vStartPos;

	bool m_bReSearch = false;
	float m_fReSearchTime_Curr = 0.0f;
	float m_fReSearchTime_End = 2.0f;

public:
	virtual void Init(class UStateMng_AI* pMng) override;
	virtual void Enter() override;
	virtual void Exit() override;
	virtual void Update(float fDeltaTime) override;
	virtual void StateMessage(FString sMessage) override;
};
