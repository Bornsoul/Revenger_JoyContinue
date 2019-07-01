#include "Mdl_GhostTrail_TickSpawn.h"
#include "Cpt_GhostTrail.h"

UMdl_GhostTrail_TickSpawn::UMdl_GhostTrail_TickSpawn()
{

}

UMdl_GhostTrail_TickSpawn::~UMdl_GhostTrail_TickSpawn()
{
	m_pRoot = nullptr;
}

void UMdl_GhostTrail_TickSpawn::Spawn(UCpt_GhostTrail* pRoot, FString sName, float fIntervalTime = 0.1f, float fTickTime = 999.0f)
{
	m_pRoot = pRoot;
	m_sName = sName;
	m_bActive = true;

	m_fIntervalTime_Max = fIntervalTime;
	m_fTickTime_Max = fTickTime;
}

void UMdl_GhostTrail_TickSpawn::Tick_Effect(float fDeltaTime)
{
	if (m_bActive == false) return;

	m_fIntervalTime_Curr += fDeltaTime;
	if (m_fIntervalTime_Curr > m_fIntervalTime_Max)
	{
		Call_Spawn();
		m_fIntervalTime_Curr = 0.0f;
	}

	m_fTickTime_Curr += fDeltaTime;
	if (m_fTickTime_Curr > m_fTickTime_Max)
	{
		m_bActive = false;
	}
}


void UMdl_GhostTrail_TickSpawn::Call_Spawn()
{
	m_pRoot->Spawn_GhostTrailEffect(m_sName);
}