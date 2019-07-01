// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Combat/StateAI_EnemyE5_Combat_Attack.h"
#include "Combat/StateAI_EnemyE5_Combat_DistMove.h"

#include "CoreMinimal.h"
#include "Actor/Characters/Enemy/E5/StateAI/StateRoot_AI_EnemyE5.h"
#include "StateAI_EnemyE5_Combat.generated.h"

UENUM()
enum class E_StateAI_EnemyE5_Combat : uint8
{
	E_Combat_Attack UMETA(DisplayName = "Combat_Attack"),
	E_Combat_DistMove UMETA(DisplayName = "Combat_DistMove"),

	E_MAX,
};

UCLASS()
class REVENGER_API UStateAI_EnemyE5_Combat : public UStateRoot_AI_EnemyE5
{
	GENERATED_BODY()

private:
	UPROPERTY()
		class UStateRoot_AI_EnemyE5* m_pCurrentState;

	UPROPERTY()
		TMap<int32, class UStateRoot_AI_EnemyE5*> m_pStateClass;

	int32 m_eState = -1;

public:
	virtual void Init(class UStateMng_AI* pMng) override;
	virtual void Enter() override;
	virtual void Exit() override;
	virtual void Update(float fDeltaTime) override;
	virtual void StateMessage(FString sMessage) override;

public:
	void ChangeCombatState(int32 eState);
};
