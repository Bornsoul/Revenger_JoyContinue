// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "States/State_GBEC_Idle.h"
#include "States/State_GBEC_Attack.h"
#include "States/State_GBEC_Hit.h"
#include "States/State_GBEC_Die.h"
#include "States/StateRoot_GBEC_Spawn.h"
#include "States/State_GBEC_Attack2.h"
#include "States/State_GBEC_JumpAttack.h"
#include "States/State_GBEC_Spin.h"
#include "States/State_GBEC_DashAttack.h"
#include "States/State_GBEC_Panic.h"

#include "../GBoxEnemy_Close.h"

#include "Revenger.h"
#include "Actor/Characters/StateRoot/StateMng_GC.h"
#include "StateMng_GBEClose.generated.h"

UENUM()
enum class E_State_GBEClose : uint8
{
	E_Idle UMETA(DisplayName = "Idle"),
	E_Attack UMETA(DisplayName = "Attack"),
	E_Hit UMETA(DisplayName = "Hit"),
	E_Die UMETA(DisplayName = "Die"),
	E_Spawn UMETA(DisplayName = "Spawn"),
	E_Attack2 UMETA(DisplayName = "Attack2"),
	E_JumpAttack UMETA(DisplayName = "JumpAttack"),
	E_Spin UMETA(DisplayName = "Spin"),
	E_DashAttack UMETA(DisplayName = "DashAttack"),
	E_Panic UMETA(DisplayName = "Panic"),

	E_MAX,
};

UCLASS()
class REVENGER_API UStateMng_GBEClose : public UStateMng_GC
{
	GENERATED_BODY()

private:
	UPROPERTY()
		class AGBoxEnemy_Close* m_pRootCharacter_Override;

public:
	UStateMng_GBEClose();
	virtual ~UStateMng_GBEClose();

	virtual void Init(class AGameCharacter* pRoot) override;
	virtual void Destroy() override;

	class AGBoxEnemy_Close* GetRootCharacter_Override() { return m_pRootCharacter_Override; }
};
