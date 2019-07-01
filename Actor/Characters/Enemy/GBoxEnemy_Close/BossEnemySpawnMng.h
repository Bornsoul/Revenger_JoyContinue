// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "BossEnemySpawnMng.generated.h"

UCLASS()
class REVENGER_API ABossEnemySpawnMng : public AActor
{
	GENERATED_BODY()
	
public:	
	UPROPERTY()
		TArray<class UBossEnemySpawn_Arrow*> m_pSpawnPins;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = SpawnAI, meta = (AllowPrivateAccess = "true"))
		TArray<class TSubclassOf<class AGameCharacter>> m_pInstance_AI;

	UPROPERTY()
		TArray<class AGameCharacter*> m_pMonsters;

public:	
	ABossEnemySpawnMng();
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;


	UFUNCTION(BlueprintCallable)
		void SpawnMonsters(int nSpawnNum);

	UFUNCTION(BlueprintPure)
		bool GetIsMonstarLive();

	UFUNCTION(BlueprintCallable)
		void KillAllMonsters();
};
