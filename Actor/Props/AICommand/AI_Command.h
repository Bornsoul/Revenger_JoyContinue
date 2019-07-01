// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Revenger.h"
#include "GameFramework/Actor.h"
#include "AI_Command.generated.h"

UENUM()
enum class E_Command : uint8
{
	E_None UMETA(DisplayName = "None"),
	E_NonFight UMETA(DisplayName = "NonFight"),
	E_Fight UMETA(DisplayName = "Fight"),	

	E_MAX,
};


UCLASS()
class REVENGER_API AAI_Command : public AActor
{
	GENERATED_BODY()

private:

	UPROPERTY()
		TArray<class AEnemyE3*> m_pEnemyList;
	
	UPROPERTY()
		TArray<class AGC_Player*> m_pPlayerList;
	
	int32 m_nState = 0;
	int32 m_nCount = 0;

	float m_fLoopTime_Curr = 0.0f;
	float m_fLoopTime_End = 0.02f;

public:	
	AAI_Command();

	virtual void BeginPlay() override;
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;
	virtual void Tick(float DeltaTime) override;

};
