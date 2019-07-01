// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Revenger.h"
#include "UObject/NoExportTypes.h"
#include "Mdl_GhostTrail_TickSpawn.generated.h"

/**
 * 
 */
UCLASS()
class REVENGER_API UMdl_GhostTrail_TickSpawn : public UObject
{
	GENERATED_BODY()

private:
	FString m_sSpawnEffectName;

	float m_fTickTime_Max = 999.0f;
	float m_fTickTime_Curr = 0.0f;

	float m_fIntervalTime_Max = 0.1f;
	float m_fIntervalTime_Curr = 0.0f;

	bool m_bActive = false;
	FString m_sName;

	class UCpt_GhostTrail* m_pRoot;

public:
	UMdl_GhostTrail_TickSpawn();
	~UMdl_GhostTrail_TickSpawn();

	void Spawn(class UCpt_GhostTrail* pRoot, FString sName, float fIntervalTime, float fTickTime);
	void Tick_Effect(float fDeltaTime);

	void Call_Spawn();

	bool GetActive() { return m_bActive; }
	void SetActive(bool bActive) { m_bActive = bActive; }
	FString GetEffectName() { return m_sName; }

};
