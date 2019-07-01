// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ArrowComponent.h"
#include "AISpawn_ArrowPin.generated.h"

/**
 * 
 */
UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class REVENGER_API UAISpawn_ArrowPin : public UArrowComponent
{
	GENERATED_BODY()
private:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = SpawnAI, meta = (AllowPrivateAccess = "true"))
		TArray<class TSubclassOf<class AGameCharacter>> m_pInstance_AI;

	class AGameCharacter* m_pCurrentAI;
public:
	UAISpawn_ArrowPin();
	int GetMaxPhase();
	void SpawnAI(int nPhaseNum);

	bool CheckAILife();
	void KillAI();
};
