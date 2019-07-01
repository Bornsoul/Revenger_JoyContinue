// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Actor/Characters/GameCharacter.h"

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "StateMng_GC.generated.h"




UCLASS()
class REVENGER_API UStateMng_GC : public UObject
{
	GENERATED_BODY()
protected:
	UPROPERTY()
		class AGameCharacter* m_pRootCharacter;

	UPROPERTY()
		class UStateRoot_GC* m_pCurrentState;

	UPROPERTY()
		TMap<int, class UStateRoot_GC*> m_pStateClass;

	int m_eState = -1;
	bool m_bDestroyed = false;
public:
	UStateMng_GC();
	virtual ~UStateMng_GC();

	virtual void Init(class AGameCharacter* pRoot);
	virtual void Destroy();

	virtual void Update(float fDeltaTime);

	virtual void ChangeState(int eState);

	class UStateRoot_GC* GetStateClassRef(int eFindState);
	void StateMessage(FString sMessage);

	UFUNCTION(BlueprintPure)
		int GetCurrentState() { return m_eState; }
	
	UFUNCTION(BlueprintPure)
		class AGameCharacter* GetRootCharacter() { return m_pRootCharacter; }
};
