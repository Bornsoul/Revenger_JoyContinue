// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "AIController.h"

#include "States/StateAI_GBEC_Normal.h"
#include "States/StateAI_GBEC_Chase.h"
#include "States/StateAI_GBEC_Combat.h"
#include "States/StateAI_GBEC_Lost.h"

#include "Revenger.h"
#include "Actor/Characters/StateRootAI/StateMng_AI.h"
#include "StateMngAI_GBEClose.generated.h"

UENUM()
enum class E_StateAI_GBEClose : uint8
{
	E_Normal UMETA(DisplayName = "Normal"),
	E_Chase UMETA(DisplayName = "Chase"),
	E_Combat UMETA(DisplayName = "Combat"),
	E_Lost UMETA(DisplayName = "Lost"),

	E_MAX,
};

UCLASS()
class REVENGER_API UStateMngAI_GBEClose : public UStateMng_AI
{
	GENERATED_BODY()

private:
	UPROPERTY()
		class AAIC_GBoxEnemy_Close* m_pRootCharacter_Override;

public:
	UStateMngAI_GBEClose();
	virtual ~UStateMngAI_GBEClose();

	virtual void Init(class AAIController* pRoot) override;
	virtual void Destroy() override;

	class AAIC_GBoxEnemy_Close* GetRootAI_Override() { return m_pRootCharacter_Override; }
};
