// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Actor/Characters/Enemy/GBoxEnemy_Close/State/StateRoot_GBEClose.h"
#include "State_GBEC_Panic.generated.h"

/**
 * 
 */
UCLASS()
class REVENGER_API UState_GBEC_Panic : public UStateRoot_GBEClose
{
	GENERATED_BODY()
private :
	bool m_bBreak = false;
	FString m_sAni;

	bool m_bMotion = false;

	//bool m_bFirst = false;
	bool m_bOpen = false;
	float m_fTime = 0.0f;
	float m_fWaitTime = 1.5f;
public:
	virtual void Init(class UStateMng_GC* pMng) override;
	virtual void Enter() override;
	virtual void Exit() override;
	virtual void Update(float fDeltaTime) override;
	virtual void StateMessage(FString sMessage) override;

	void Set_Break(bool bBreak = false) { m_bBreak = bBreak; }

	void PanicHit(bool bStiffen =false);
};
