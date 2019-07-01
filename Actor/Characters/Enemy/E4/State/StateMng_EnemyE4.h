// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "States/State_EnemyE4_Idle.h"
#include "States/State_EnemyE4_Hit.h"
#include "States/State_EnemyE4_Attack.h"
#include "States/State_EnemyE4_Die.h"
#include "States/State_EnemyE4_Spawn.h"

#include "../EnemyE4.h"

#include "Revenger.h"
#include "Actor/Characters/StateRoot/StateMng_GC.h"
#include "StateMng_EnemyE4.generated.h"

UENUM()
enum class E_State_EnemyE4 : uint8
{
	E_Idle UMETA(DisplayName = "Idle"),
	E_Hit UMETA(DisplayName = "Hit"),
	E_Attack UMETA(DisplayName = "Attack"),
	E_Die UMETA(DisplayName = "Die"),
	E_Spawn UMETA(DisplayName = "Spawn"),

	E_MAX,
};
UCLASS()
class REVENGER_API UStateMng_EnemyE4 : public UStateMng_GC
{
	GENERATED_BODY()
private:
	UPROPERTY()
		class AEnemyE4* m_pRootCharacter_Override;

public:
	UStateMng_EnemyE4();
	virtual ~UStateMng_EnemyE4();

	virtual void Init(class AGameCharacter* pRoot) override;
	virtual void Destroy() override;

	class AEnemyE4* GetRootCharacter_Override() { return m_pRootCharacter_Override; }
};
