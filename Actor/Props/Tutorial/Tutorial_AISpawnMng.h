// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Revenger.h"
#include "GameFramework/Actor.h"
#include "Tutorial_AISpawnMng.generated.h"

UCLASS()
class REVENGER_API ATutorial_AISpawnMng : public AActor
{
	GENERATED_BODY()
	
private:
	UPROPERTY()
		TArray<class UAISpawn_ArrowPin*> m_pSpawnPins;

	int m_nMaxPhase = 0;
	int m_nCurrPhase = 0;
	bool m_bActive = false;

	bool m_bClearState = false;
	bool m_bClearSuccess = false;

public:	
	ATutorial_AISpawnMng();
	virtual void BeginPlay() override;
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;
	virtual void Tick(float DeltaTime) override;

	UFUNCTION(BlueprintCallable)
		void SpawnAI();

	UFUNCTION(BlueprintCallable)
		void ClearAI();

	UFUNCTION(BlueprintCallable)
		void SetStateClear(bool bClear) { m_bClearState = bClear; }

	UFUNCTION(BlueprintPure)
		bool GetStateClear() { return m_bClearState; }

	UFUNCTION(BlueprintCallable)
		void SetStageSuccess(bool bClear) { m_bClearSuccess = bClear; }

	UFUNCTION(BlueprintPure)
		bool GetStageSuccess() { return m_bClearSuccess; }

	UFUNCTION(BlueprintPure)
		class AGameCharacter* GetCharacter(const int32 nIndex);
};
