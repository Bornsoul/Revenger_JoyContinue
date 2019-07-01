// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "../EnemyE5.h"

#include "Revenger.h"
#include "Actor/Characters/StateRoot/StateRoot_GC.h"
#include "StateRoot_EnemyE5.generated.h"

/**
 * 
 */
UCLASS()
class REVENGER_API UStateRoot_EnemyE5 : public UStateRoot_GC
{
	GENERATED_BODY()

protected:
	UPROPERTY()
		class UStateMng_EnemyE5* m_pStateMng_Override;

public:
	UStateRoot_EnemyE5();
	virtual ~UStateRoot_EnemyE5();

	virtual void Init(class UStateMng_GC* pMng) override;
	virtual void Enter() override;
	virtual void Exit() override;
	virtual void Update(float fDeltaTime) override;
	virtual void StateMessage(FString sMessage) override;

	class AEnemyE5* GetRootChar();
};
