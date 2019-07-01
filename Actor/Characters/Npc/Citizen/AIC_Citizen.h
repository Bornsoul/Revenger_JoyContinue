// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "AIC_Citizen.generated.h"

/**
 * 
 */
UCLASS()
class REVENGER_API AAIC_Citizen : public AAIController
{
	GENERATED_BODY()

private:
	UPROPERTY()
		class ACitizen* m_pRoot;

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
	AAIC_Citizen();
	virtual void BeginPlay() override;
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;
	virtual void Possess(APawn* Pawn) override;
	virtual void Tick(float DeltaTime) override;

	void InitAI();
	void SetActiveAI(bool bActive);
	void StopAI();

public:
	AActor* DetectInPerception();

};