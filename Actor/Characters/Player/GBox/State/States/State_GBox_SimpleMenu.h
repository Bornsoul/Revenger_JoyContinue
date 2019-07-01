// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Actor/Characters/Player/GBox/State/StateRoot_GBox.h"
#include "State_GBox_SimpleMenu.generated.h"

/**
 * 
 */
UCLASS()
class REVENGER_API UState_GBox_SimpleMenu : public UStateRoot_GBox
{
	GENERATED_BODY()

private:
	bool m_bMotionEnd = false;

public:
	virtual void Init(class UStateMng_GC* pMng) override;
	virtual void Enter() override;
	virtual void Exit() override;
	virtual void Update(float fDeltaTime) override;
	virtual void StateMessage(FString sMessage) override;
};
