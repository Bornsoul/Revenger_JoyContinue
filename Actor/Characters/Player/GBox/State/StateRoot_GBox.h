// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "../GBox.h"

#include "Revenger.h"
#include "Actor/Characters/StateRoot/StateRoot_GC.h"
#include "StateRoot_GBox.generated.h"

/**
 * 
 */
UCLASS()
class REVENGER_API UStateRoot_GBox : public UStateRoot_GC
{
	GENERATED_BODY()
	
protected:
	UPROPERTY()
		class UStateMng_GBox* m_pStateMng_Override;

public:
	UStateRoot_GBox();
	virtual ~UStateRoot_GBox();

	virtual void Init(class UStateMng_GC* pMng) override;
	virtual void Enter() override;
	virtual void Exit() override;
	virtual void Update(float fDeltaTime) override;
	virtual void StateMessage(FString sMessage) override;

	class AGBox* GetRootChar();
};
