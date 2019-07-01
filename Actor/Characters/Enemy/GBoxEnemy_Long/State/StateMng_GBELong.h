// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "States/State_GBEL_Idle.h"
#include "States/State_GBEL_Attack.h"
#include "States/State_GBEL_Hit.h"
#include "States/State_GBEL_Die.h"
#include "States/State_GBEL_Parring.h"

#include "../GBoxEnemy_Long.h"

#include "Revenger.h"
#include "Actor/Characters/StateRoot/StateMng_GC.h"
#include "StateMng_GBELong.generated.h"

UENUM()
enum class E_State_GBELong : uint8
{
	E_Idle UMETA(DisplayName = "Idle"),
	E_Attack UMETA(DisplayName = "Attack"),
	E_Hit UMETA(DisplayName = "Hit"),
	E_Die UMETA(DisplayName = "Die"),

	E_MAX,
};

/**
 * 
 */
UCLASS()
class REVENGER_API UStateMng_GBELong : public UStateMng_GC
{
	GENERATED_BODY()

private:
	UPROPERTY()
		class AGBoxEnemy_Long* m_pRootCharacter_Override;

public:
	UStateMng_GBELong();
	virtual ~UStateMng_GBELong();

	virtual void Init(class AGameCharacter* pRoot) override;
	virtual void Destroy() override;

	class AGBoxEnemy_Long* GetRootCharacter_Override() { return m_pRootCharacter_Override; }
};
