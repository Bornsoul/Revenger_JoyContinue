// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Combat/StateAI_GBEC_Combat_Attack.h"
#include "Combat/StateAI_GBEC_Combat_DistMove.h"
#include "Combat/UStateAI_GBEC_Combat_JumpAttack.h"

#include "Revenger.h"
#include "Actor/Characters/Enemy/GBoxEnemy_Close/StateAI/StateRootAI_GBEClose.h"
#include "StateAI_GBEC_Combat.generated.h"

UENUM()
enum class E_StateAI_GBEC_Combat : uint8
{
	E_Combat_Attack UMETA(DisplayName = "Combat_Attack"),
	E_Combat_DistMove UMETA(DisplayName = "Combat_DistMove"),
	E_Combat_JumpAttack UMETA(DisplayName = "Combat_JumpAttack"),

	E_MAX,
};

UCLASS()
class REVENGER_API UStateAI_GBEC_Combat : public UStateRootAI_GBEClose
{
	GENERATED_BODY()

private:
	UPROPERTY()
		class UStateRootAI_GBEClose* m_pCurrentState;

	UPROPERTY()
		TMap<int32, class UStateRootAI_GBEClose*> m_pStateClass;

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
