#pragma once

#include "Actor/Characters/GameCharacter.h"

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "StateRoot_GC.generated.h"

UCLASS()
class REVENGER_API UStateRoot_GC : public UObject
{
	GENERATED_BODY()
protected :
	UPROPERTY()
		class UStateMng_GC* m_pStateMng;

public :
	UStateRoot_GC();
	virtual ~UStateRoot_GC();

	virtual void Init(class UStateMng_GC* pMng);
	virtual void Enter();
	virtual void Exit();
	virtual void Update(float fDeltaTime);
	virtual void StateMessage(FString sMessage);

	class AGameCharacter* GetRootCharacter();
	void ChangeState(int eState);


};
