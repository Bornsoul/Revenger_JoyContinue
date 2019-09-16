// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Actor/Props/SoulFollow/SoulFollow.h"

#include "CoreMinimal.h"
#include "Actor/Characters/GameCharacter.h"
#include "GC_Enemy.generated.h"

UENUM(BlueprintType)
enum class eDifficultArrow : uint8
{
	E_EASY UMETA(DisplayName = "Easy"),
	E_NORMAL UMETA(DisplayName = "Normal"),
	E_HARD UMETA(DisplayName = "Hard"),
	E_HELL UMETA(DisplayName = "Hell"),

	E_MAX,
};

USTRUCT(Atomic, BlueprintType)
struct REVENGER_API FDifficultySetting
{
	GENERATED_USTRUCT_BODY()

public:
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "SpawnAI")
		eDifficultArrow m_eDifficult;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "SpawnAI")
		float m_fHp;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "SpawnAI")
		float m_fMoveSpeed;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "SpawnAI")
		float m_fBarrier;
};

UCLASS()
class REVENGER_API AGC_Enemy : public AGameCharacter
{
	GENERATED_BODY()
	
private:
	FVector m_vStartPos;
	bool m_bFighter = false;

	float m_fFallingTime_Curr = 0.0f;
	float m_fFallingTime_End = 3.0f;
	bool m_bFalling = false;

	/*UPROPERTY()
		class AHUD_GameMain* m_pHud;*/

	UPROPERTY()
		TSubclassOf<class ASoulFollow> m_pInst_SoulFollow;

	UPROPERTY()
		class ASoulFollow* m_pSoulFollow;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Difficulty Setting", meta = (AllowPrivateAccess = "true"))
		TArray<FDifficultySetting> m_stDifficulty;

protected:
	UPROPERTY()
		class AHUD_Game* m_pHud;

	UPROPERTY()
		class UGameInst_JoyContinue* m_pGamInst;

public:
	virtual void BeginPlay() override;
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;
	virtual void Tick(float DeltaTime) override;

	virtual void CreateSoulFollow();

	void SetFighter(bool bFight) { m_bFighter = bFight; }
	float GetEnemyHp();
	float GetEnemyBarrier();
	float GetEnemySpeed();
	int32 GetDifficulty();

	void AddOisEnemy(AGameCharacter* pTarget, int32 nIconState);
	void DestroyOsiEnemy();

	FORCEINLINE FVector GetStartLoc() { return m_vStartPos;  }
	FORCEINLINE void SetStartLoc(FVector vStartPos) { m_vStartPos = vStartPos;  }
	FORCEINLINE bool GetFighter() { return m_bFighter; }
public:
	AGC_Enemy();


};
