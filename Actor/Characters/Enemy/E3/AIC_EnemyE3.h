// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Revenger.h"
#include "AIController.h"
#include "AIC_EnemyE3.generated.h"

/**
 * 
 */
UCLASS()
class REVENGER_API AAIC_EnemyE3 : public AAIController
{
	GENERATED_BODY()
private:
	UPROPERTY()
		class AEnemyE3* m_pRoot;

	UPROPERTY()
		class UStateMng_AI_EnemyE3* m_pStateMng;

	bool m_bActive = false;

public:
	UPROPERTY()
		class UAIPerceptionComponent* m_pPerception;

	UPROPERTY()
		class UAISenseConfig_Sight* m_pSightConfig;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = AI)
		float m_fAISightRadius = 1500.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = AI)
		float m_fAILoseSightRadius = m_fAISightRadius + 500.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = AI)
		float m_fAIFieldOfView = 200.0f;

public:
	AAIC_EnemyE3();
	virtual void BeginPlay() override;
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;
	virtual void Possess(APawn* Pawn) override;
	virtual void Tick(float DeltaTime) override;

	void InitAI();
	void SetActiveAI(bool bActive);
	void StopAI();

	void State_Fight();

public:
	AActor* DetectInPerception();
	AActor* DetectInPerceptionDie();

public:

	FORCEINLINE class AEnemyE3* GetRootChar() { return m_pRoot; }
	FORCEINLINE class UStateMng_AI_EnemyE3* GetStateMng() { return m_pStateMng; }

};