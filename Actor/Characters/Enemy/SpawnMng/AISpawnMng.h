// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "AISpawn_ArrowPin.h"

#include "Revenger.h"
#include "GameFramework/Actor.h"
#include "AISpawnMng.generated.h"

enum class eDifficultArrow : uint8;


UCLASS()
class REVENGER_API AAISpawnMng : public AActor
{
	GENERATED_BODY()

private:

	UPROPERTY()
		TArray<class UAISpawn_ArrowPin*> m_pSpawnPins;

	//UPROPERTY()
	//	TArray<class UAISpawn_DifficultArrowPin*> m_pSpawnDifficultPins;

	UPROPERTY()
		TArray<class UAISpawn_Wall*> m_pSpawnWalls;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
		class UBoxComponent* m_pCollider;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Portal Mng", meta = (AllowPrivateAccess = "true"))
		class ACitizenCage* m_pCitizenCage;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Portal Mng", meta = (AllowPrivateAccess = "true"))
		class AMovePortal* m_pPortal;

	UPROPERTY()
		class UCpt_GameSave* m_pSaveData;

	//UPROPERTY(EditAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
//		TArray<class ALevelObj_Door*> m_pDoors;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
		bool m_bBossStage = false;

	int m_nMaxPhase = 0;
	int m_nCurrPhase = 0;
	int m_nDifficultLevel = 0;

	bool m_bActive = false;
	bool m_bPortalUsed = false;

	bool m_bStageClear = false;

public:
	AAISpawnMng();
	virtual void BeginPlay() override;
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;
	virtual void Tick(float DeltaTime) override;

	UFUNCTION(BlueprintCallable)
		void SetDifficulty(int32 nDifficulty) { m_nDifficultLevel = nDifficulty; }

	void SpawnAIs();

	void StageClear();

	UFUNCTION(BlueprintPure)
		bool GetStageClear() { return m_bStageClear; }

	UFUNCTION(BlueprintCallable)
		void KillAllMonsters();

	UFUNCTION(BlueprintCallable)
		void BeginedOverlap();

	UFUNCTION()
		void OnOverlapBegin(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

};
