// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "States/State_EnemyE5_Idle.h"
#include "States/State_EnemyE5_Attack.h"
#include "States/State_EnemyE5_Spawn.h"
#include "States/State_EnemyE5_Hit.h"
#include "States/State_EnemyE5_Die.h"

#include "../EnemyE5.h"

#include "Revenger.h"
#include "Actor/Characters/StateRoot/StateMng_GC.h"
#include "StateMng_EnemyE5.generated.h"


UENUM()
enum class E_State_EnemyE5 : uint8
{
	E_Idle UMETA(DisplayName = "Idle"),
	E_Hit UMETA(DisplayName = "Hit"),
	E_Attack UMETA(DisplayName = "Attack"),
	E_Die UMETA(DisplayName = "Die"),
	E_Spawn UMETA(DisplayName = "Spawn"),

	E_MAX,
};

UCLASS()
class REVENGER_API UStateMng_EnemyE5 : public UStateMng_GC
{
	GENERATED_BODY()

private:
	UPROPERTY()
		class AEnemyE5* m_pRootCharacter_Override;

public:
	UStateMng_EnemyE5();
	virtual ~UStateMng_EnemyE5();

	virtual void Init(class AGameCharacter* pRoot) override;
	virtual void Destroy() override;

	class AEnemyE5* GetRootCharacter_Override() { return m_pRootCharacter_Override; }
};
