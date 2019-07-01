// Fill out your copyright notice in the Description page of Project Settings.

#pragma once
#include "AIController.h"

#include "States/StateAI_EnemyE5_Normal.h"
#include "States/StateAI_EnemyE5_Chase.h"
#include "States/StateAI_EnemyE5_Combat.h"
#include "States/StateAI_EnemyE5_Lost.h"

#include "Revenger.h"
#include "Actor/Characters/StateRootAI/StateMng_AI.h"
#include "StateMng_AI_EnemyE5.generated.h"


UENUM()
enum class E_StateAI_EnemyE5 : uint8
{
	E_Normal UMETA(DisplayName = "Normal"),
	E_Chase UMETA(DisplayName = "Chase"),
	E_Combat UMETA(DisplayName = "Combat"),
	E_Lost UMETA(DisplayName = "Lost"),

	E_MAX,
};

UCLASS()
class REVENGER_API UStateMng_AI_EnemyE5 : public UStateMng_AI
{
	GENERATED_BODY()
	
private:
	UPROPERTY()
		class AAIC_EnemyE5* m_pRootCharacter_Override;

public:
	UStateMng_AI_EnemyE5();
	virtual ~UStateMng_AI_EnemyE5();

	virtual void Init(class AAIController* pRoot) override;
	virtual void Destroy() override;

	class AAIC_EnemyE5* GetRootAI_Override() { return m_pRootCharacter_Override; }
};
