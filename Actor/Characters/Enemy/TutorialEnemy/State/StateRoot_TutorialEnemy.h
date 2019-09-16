// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Actor/Characters/Enemy/TutorialEnemy/TutorialEnemy.h"

#include "Revenger.h"
#include "Actor/Characters/StateRoot/StateRoot_GC.h"
#include "StateRoot_TutorialEnemy.generated.h"

/**
 * 
 */
UCLASS()
class REVENGER_API UStateRoot_TutorialEnemy : public UStateRoot_GC
{
	GENERATED_BODY()

protected:
	UPROPERTY()
		class UStateMng_TutorialEnemy* m_pStateMng_Override;

public:
	UStateRoot_TutorialEnemy();
	virtual ~UStateRoot_TutorialEnemy();

	virtual void Init(class UStateMng_GC* pMng) override;
	virtual void Enter() override;
	virtual void Exit() override;
	virtual void Update(float fDeltaTime) override;
	virtual void StateMessage(FString sMessage) override;

	class ATutorialEnemy* GetRootChar();
};
