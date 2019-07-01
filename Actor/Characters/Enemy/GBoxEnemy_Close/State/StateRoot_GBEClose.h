// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "../GBoxEnemy_Close.h"

#include "Revenger.h"
#include "Actor/Characters/StateRoot/StateRoot_GC.h"
#include "StateRoot_GBEClose.generated.h"

/**
 * 
 */
UCLASS()
class REVENGER_API UStateRoot_GBEClose : public UStateRoot_GC
{
	GENERATED_BODY()

protected:
	UPROPERTY()
		class UStateMng_GBEClose* m_pStateMng_Override;

public:
	UStateRoot_GBEClose();
	virtual ~UStateRoot_GBEClose();

	virtual void Init(class UStateMng_GC* pMng) override;
	virtual void Enter() override;
	virtual void Exit() override;
	virtual void Update(float fDeltaTime) override;
	virtual void StateMessage(FString sMessage) override;

	class AGBoxEnemy_Close* GetRootChar();
};
