// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Revenger.h"
#include "Engine/GameInstance.h"
#include "GameInst_JoyContinue.generated.h"

/**
 * 
 */
UCLASS()
class REVENGER_API UGameInst_JoyContinue : public UGameInstance
{
	GENERATED_BODY()

public:

private:
	int32 m_nDifficulty = -1;

public:
	UGameInst_JoyContinue();
	virtual void Init();

	UFUNCTION(BlueprintCallable)
		void SetDifficulty(int32 nDifficulty) { m_nDifficulty = nDifficulty; }

	UFUNCTION(BlueprintPure)
		int32 GetDifficulty() { return m_nDifficulty; }

};
