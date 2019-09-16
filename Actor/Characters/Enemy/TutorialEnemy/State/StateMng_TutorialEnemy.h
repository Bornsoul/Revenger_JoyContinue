// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "States/State_TutoEnemy_Idle.h"
#include "States/State_TutoEnemy_Die.h"
#include "States/State_TutoEnemy_Hit.h"
#include "States/State_TutoEnemy_Spawn.h"

#include "Revenger.h"
#include "Actor/Characters/StateRoot/StateMng_GC.h"
#include "StateMng_TutorialEnemy.generated.h"

UENUM()
enum class E_State_TutoEnemy : uint8
{
	E_Idle UMETA(DisplayName = "Idle"),
	E_Attack UMETA(DisplayName = "Attack"),
	E_Hit UMETA(DisplayName = "Hit"),
	E_Die UMETA(DisplayName = "Die"),
	E_Spawn UMETA(DisplayName = "Spawn"),

	E_MAX,
};

UCLASS()
class REVENGER_API UStateMng_TutorialEnemy : public UStateMng_GC
{
	GENERATED_BODY()
	

private:
	UPROPERTY()
		class ATutorialEnemy* m_pRootCharacter_Override;

public:
	UStateMng_TutorialEnemy();
	virtual ~UStateMng_TutorialEnemy();

	virtual void Init(class AGameCharacter* pRoot) override;
	virtual void Destroy() override;

	class ATutorialEnemy* GetRootCharacter_Override() { return m_pRootCharacter_Override; }
};
