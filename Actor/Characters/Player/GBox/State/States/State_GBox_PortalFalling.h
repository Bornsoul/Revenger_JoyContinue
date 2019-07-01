// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Revenger.h"
#include "Actor/Characters/Player/GBox/State/StateRoot_GBox.h"
#include "State_GBox_PortalFalling.generated.h"

/**
 * 
 */
UCLASS()
class REVENGER_API UState_GBox_PortalFalling : public UStateRoot_GBox
{
	GENERATED_BODY()

private:

	UPROPERTY()
		UArrowComponent* m_pStartPortal;

	bool m_bMotionEnd = false;

	FVector m_vStartLoc;

public:
	virtual void Init(class UStateMng_GC* pMng) override;
	virtual void Enter() override;
	virtual void Exit() override;
	virtual void Update(float fDeltaTime) override;
	virtual void StateMessage(FString sMessage) override;

	void SetPortal(UArrowComponent* pPortal);
};
