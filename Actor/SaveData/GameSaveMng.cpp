// Fill out your copyright notice in the Description page of Project Settings.

#include "GameSaveMng.h"

void UGameSaveMng::SetDataInit()
{
	UALERT(TEXT("SetDataInit"));
	m_nSpawnPoint = -1;
	m_nDifficulty = -1;
	m_nTutorial = 0;

	m_stPlayerData.m_nHitBulletCount = 0;
	m_stPlayerData.m_nNonHitBulletCount = 0;
	m_stPlayerData.m_nDeadCount = 0;	
}
