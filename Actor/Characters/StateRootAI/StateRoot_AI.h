// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "AIController.h"

#include "Revenger.h"
#include "UObject/NoExportTypes.h"
#include "StateRoot_AI.generated.h"

/**
 * 
 */
UCLASS()
class REVENGER_API UStateRoot_AI : public UObject
{
	GENERATED_BODY()
	
protected:
	UPROPERTY()
		class UStateMng_AI* m_pStateMng;

public:
	UStateRoot_AI();
	virtual ~UStateRoot_AI();

	virtual void Init(class UStateMng_AI* pMng);
	virtual void Enter();
	virtual void Exit();
	virtual void Update(float fDeltaTime);
	virtual void StateMessage(FString sMessage);

	class AAIController* GetRootAI();
	void ChangeState(int eState);
};
