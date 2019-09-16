// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Actor/Characters/Enemy/GC_Enemy.h"

#include "Revenger.h"
#include "Components/ArrowComponent.h"
#include "AISpawn_ArrowPin.generated.h"

enum class eDifficultArrow : uint8;

USTRUCT(Atomic, BlueprintType)
struct REVENGER_API FDifficultArrow
{
	GENERATED_USTRUCT_BODY()

public:
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "SpawnAI")
		eDifficultArrow m_eDifficult;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "SpawnAI")
		TArray<TSubclassOf<class AGameCharacter>> m_pInstance_AI;

};

UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class REVENGER_API UAISpawn_ArrowPin : public UArrowComponent
{
	GENERATED_BODY()

private:
	/*UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = SpawnAI, meta = (AllowPrivateAccess = "true"))
		TArray<class TSubclassOf<class AGameCharacter>> m_pInstance_AI;*/

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "SpawnAI_Difficulty", meta = (AllowPrivateAccess = "true"))
		TArray<FDifficultArrow> m_pInstance_Arrow;

	UPROPERTY()
		class AGameCharacter* m_pCurrentAI;

	int32 m_nDifficulty = -1;


public:
	UAISpawn_ArrowPin();
	int GetMaxPhase();
	void SpawnAI(int nPhaseNum);

	void SetDifficulty(int32 nDifficulty);
	int32 GetDifficulty() { return m_nDifficulty; }

	bool CheckAILife();
	void KillAI();

	UFUNCTION(BlueprintPure)
		class AGameCharacter* GetCurrentAI() { return m_pCurrentAI;  }
};
