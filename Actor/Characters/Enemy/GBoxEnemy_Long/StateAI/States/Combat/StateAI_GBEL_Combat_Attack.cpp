// Fill out your copyright notice in the Description page of Project Settings.

#include "StateAI_GBEL_Combat_Attack.h"


#include "Actor/Characters/Enemy/GBoxEnemy_Long/GBoxEnemy_Long.h"
#include "Kismet/KismetMathLibrary.h"

void UStateAI_GBEL_Combat_Attack::Init(class UStateMng_AI* pMng)
{
	Super::Init(pMng);

}

void UStateAI_GBEL_Combat_Attack::Enter()
{
	Super::Enter();

	m_fShootTime_Curr = 0.0f;
	m_fMoveTime_Curr = 0.0f;
	m_fMoveTime_End = FMath::RandRange(1.0f, 3.0f);

}

void UStateAI_GBEL_Combat_Attack::Exit()
{
	Super::Exit();
}

void UStateAI_GBEL_Combat_Attack::Update(float fDeltaTime)
{
	Super::Update(fDeltaTime);
	
	AActor* pTarget = GetRootAI()->DetectInPerception();

	if (pTarget != nullptr)
	{
		FVector vEnemyPos = GetRootAI()->GetRootChar()->GetActorLocation();
		FVector vTargetPos = pTarget->GetActorLocation();

		float fDistance = FVector::Distance(vEnemyPos, vTargetPos);
		if (fDistance <= GetRootAI()->m_fAISightRadius)
		{
			if (GetRootAI()->GetRootChar()->Controll_Attack(pTarget))
			{
				ChangeState(static_cast<int32>(E_StateAI_GBELong::E_Chase));
				return;
			}
		}
	}
	

}

void UStateAI_GBEL_Combat_Attack::StateMessage(FString StateMessage)
{
	Super::StateMessage(StateMessage);
}


