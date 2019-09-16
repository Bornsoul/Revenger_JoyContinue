// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Revenger.h"
#include "GameFramework/SaveGame.h"
#include "GameSaveMng.generated.h"

//@ 플레이어 저장 정보
USTRUCT(BlueprintType)
struct FSaveData_Player
{
	GENERATED_BODY()

public:
	//! 튕겨내기 횟수
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "SaveData_Player")
		int32 m_nHitBulletCount;
	
	//! 빗나간 횟수
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "SaveData_Player")
		int32 m_nNonHitBulletCount;

	//! 죽은 횟수
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "SaveData_Player")
		int32 m_nDeadCount;
};

UCLASS()
class REVENGER_API UGameSaveMng : public USaveGame
{
	GENERATED_BODY()
	
public:
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "SaveData")
		FString m_sSaveData_Name;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "SaveData")
		int32 m_nSaveData_Index;

	//! ▼▼▼ 아래부터 사용자 데이터 추가 ▼▼▼
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "SaveData")
		int32 m_nSpawnPoint;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "SaveData")
		FSaveData_Player m_stPlayerData;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "SaveData")
		int32 m_nDifficulty;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "SaveData")
		int32 m_nTutorial;

public:

	UFUNCTION(BlueprintCallable)
		void SetDataInit();
};
