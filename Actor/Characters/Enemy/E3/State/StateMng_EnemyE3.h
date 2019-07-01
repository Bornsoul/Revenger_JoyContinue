// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "States/State_EnemyE3_Idle.h"
#include "States/State_EnemyE3_Hit.h"
#include "States/State_EnemyE3_Attack.h"
#include "States/State_EnemyE3_Die.h"
#include "States/State_EnemyE3_Spawn.h"

#include "../EnemyE3.h"

#include "Revenger.h"
#include "Actor/Characters/StateRoot/StateMng_GC.h"
#include "StateMng_EnemyE3.generated.h"


UENUM()
enum class E_State_EnemyE3 : uint8
{
	E_Idle UMETA(DisplayName = "Idle"),
	E_Hit UMETA(DisplayName = "Hit"),
	E_Attack UMETA(DisplayName = "Attack"),
	E_Die UMETA(DisplayName = "Die"),
	E_Spawn UMETA(DisplayName = "Spawn"),

	E_MAX,
};

UCLASS()
class REVENGER_API UStateMng_EnemyE3 : public UStateMng_GC
{
	GENERATED_BODY()
private:
	UPROPERTY()
		class AEnemyE3* m_pRootCharacter_Override;

public:
	UStateMng_EnemyE3();
	virtual ~UStateMng_EnemyE3();

	virtual void Init(class AGameCharacter* pRoot) override;
	virtual void Destroy() override;

	class AEnemyE3* GetRootCharacter_Override() { return m_pRootCharacter_Override; }
};
