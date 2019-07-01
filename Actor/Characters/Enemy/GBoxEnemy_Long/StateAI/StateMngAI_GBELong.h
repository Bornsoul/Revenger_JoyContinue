// Fill out your copyright notice in the Description page of Project Settings.

#pragma once
#include "AIController.h"

#include "States/StateAI_GBEL_Normal.h"
#include "States/StateAI_GBEL_Chase.h"
#include "States/StateAI_GBEL_Combat.h"
#include "States/StateAI_GBEL_Lost.h"

#include "Revenger.h"
#include "Actor/Characters/StateRootAI/StateMng_AI.h"
#include "StateMngAI_GBELong.generated.h"


UENUM()
enum class E_StateAI_GBELong : uint8
{
	E_Normal UMETA(DisplayName = "Normal"),
	E_Chase UMETA(DisplayName = "Chase"),
	E_Combat UMETA(DisplayName = "Combat"),
	E_Lost UMETA(DisplayName = "Lost"),

	E_MAX,
};

UCLASS()
class REVENGER_API UStateMngAI_GBELong : public UStateMng_AI
{
	GENERATED_BODY()

private:
	UPROPERTY()
		class AAIC_GBoxEnemy_Long* m_pRootCharacter_Override;

public:
	UStateMngAI_GBELong();
	virtual ~UStateMngAI_GBELong();

	virtual void Init(class AAIController* pRoot) override;
	virtual void Destroy() override;

	class AAIC_GBoxEnemy_Long* GetRootAI_Override() { return m_pRootCharacter_Override; }
};
