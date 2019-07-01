// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Revenger.h"
#include "AIController.h"
#include "AIC_GBoxEnemy_Long.generated.h"

/**
 * 
 */
UCLASS()
class REVENGER_API AAIC_GBoxEnemy_Long : public AAIController
{
	GENERATED_BODY()

private:
	UPROPERTY()
		class AGBoxEnemy_Long* m_pRoot;

	UPROPERTY()
		class UStateMngAI_GBELong* m_pStateMng;

	bool m_bActive = false;

public:
	UPROPERTY()
		class UAIPerceptionComponent* m_pPerception;

	UPROPERTY()
		class UAISenseConfig_Sight* m_pSightConfig;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = AI)
		float m_fAISightRadius = 2000.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = AI)
		float m_fAILoseSightRadius = m_fAISightRadius + 500.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = AI)
		float m_fAIFieldOfView = 360.0f;

public:
	AAIC_GBoxEnemy_Long();
	virtual void BeginPlay() override;
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;
	virtual void Possess(APawn* Pawn) override;
	virtual void Tick(float DeltaTime) override;

	void InitAI();
	void SetActiveAI(bool bActive);
	void StopAI();

public:
	AActor* DetectInPerception();

public:
	
	FORCEINLINE class AGBoxEnemy_Long* GetRootChar() { return m_pRoot; }
	FORCEINLINE class UStateMngAI_GBELong* GetStateMng() { return m_pStateMng; }

};
