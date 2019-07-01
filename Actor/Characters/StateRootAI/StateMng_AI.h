// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "AIController.h"

#include "Revenger.h"
#include "UObject/NoExportTypes.h"
#include "StateMng_AI.generated.h"

/**
 * 
 */
UCLASS()
class REVENGER_API UStateMng_AI : public UObject
{
	GENERATED_BODY()

protected:
	UPROPERTY()
		class AAIController* m_pRootCharacter;

	UPROPERTY()
		class UStateRoot_AI* m_pCurrentState;

	UPROPERTY()
		TMap<int, class UStateRoot_AI*> m_pStateClass;

	int m_eState = -1;
	bool m_bDestroyed = false;

public:
	UStateMng_AI();
	virtual ~UStateMng_AI();

	virtual void Init(class AAIController* pRoot);
	virtual void Destroy();
	virtual void Update(float fDeltaTime);
	virtual void ChangeState(int eState);

	class UStateRoot_AI* GetStateClassRef(int eFindState);
	void StateMessage(FString sMessage);

	int GetCurrentState() { return m_eState; }
	class AAIController* GetRootAI() { return m_pRootCharacter; }
};
