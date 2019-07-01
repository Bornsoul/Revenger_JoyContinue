// Fill out your copyright notice in the Description page of Project Settings.

#include "StateAI_EnemyE3_Combat_Crazy.h"
#include "Actor/Characters/Enemy/E3/EnemyE3.h"
#include "Kismet/KismetMathLibrary.h"


void UStateAI_EnemyE3_Combat_Crazy::Init(class UStateMng_AI* pMng)
{
	Super::Init(pMng);

}

void UStateAI_EnemyE3_Combat_Crazy::Enter()
{
	Super::Enter();

	m_fCombatTime_Curr = 0.0f;
	m_fCombatTime_End = 1.0f;// FMath::RandRange(0.5f, 1.5f);
}

void UStateAI_EnemyE3_Combat_Crazy::Exit()
{
	Super::Exit();

}

void UStateAI_EnemyE3_Combat_Crazy::Update(float fDeltaTime)
{
	Super::Update(fDeltaTime);

	

	AActor* pDetectTarget = GetRootAI()->DetectInPerception();
	if (pDetectTarget != nullptr)
	{
		AEnemyE3* pRootCharacter = GetRootAI()->GetRootChar();

		FRotator pLookRotation = UKismetMathLibrary::FindLookAtRotation(pRootCharacter->GetActorLocation(), pDetectTarget->GetActorLocation());
		pLookRotation.Pitch = 0.0f;
		pLookRotation.Roll = 0.0f;
		FRotator pInterp = UKismetMathLibrary::RInterpTo(pRootCharacter->GetActorRotation(), pLookRotation, fDeltaTime, 18.0f);
		pRootCharacter->SetActorRotation(pInterp);

		float fDistanceChar = FVector::Dist(pRootCharacter->GetActorLocation(), pDetectTarget->GetActorLocation());

		if (fDistanceChar <= 500.0f)
		{
			if (GetRootAI()->GetRootChar()->Controll_Attack(pDetectTarget))
			{
				ChangeState(static_cast<int32>(E_StateAI_EnemyE3::E_Combat));
				return;
			}
		}

		if (m_bCrazy == false)
		{
			if (FMath::Abs(fDistanceChar - m_fStayDistance) > 15.0f)
			{
				FVector vForwardVector = pRootCharacter->GetActorLocation() - pDetectTarget->GetActorLocation();
				vForwardVector.Normalize();
				FVector vDestLoc = pDetectTarget->GetActorLocation() + vForwardVector * m_fStayDistance;
				if (FVector::Dist(vDestLoc, pRootCharacter->GetActorLocation()) > 5.0f)
				{
					EPathFollowingRequestResult::Type pResult = GetRootAI()->MoveToLocation(vDestLoc);

					FRotator rCapsuleRota = pRootCharacter->GetCapsuleComponent()->GetComponentRotation();
					FRotator pMoveRota = UKismetMathLibrary::FindLookAtRotation(pRootCharacter->GetActorLocation(), vDestLoc);
					FRotator pRota_Normal = UKismetMathLibrary::NormalizedDeltaRotator(rCapsuleRota, pMoveRota);
					pRootCharacter->SetMovementDirection(pRota_Normal.Yaw);
					
					
				}

				m_fCombatTime_Curr += fDeltaTime;
				if (m_fCombatTime_Curr >= m_fCombatTime_End)
				{
					m_fCombatTime_Curr = 0.0f;
					m_bCrazy = true;
				}
			}
		}
		else
		{
			FVector vMove = pRootCharacter->GetActorLocation();
			vMove.X += FMath::RandRange(-200.0f, 200.0f);
			vMove.Y += FMath::RandRange(-200.0f, 200.0f);
			EPathFollowingRequestResult::Type pResult = GetRootAI()->MoveToLocation(vMove);

			m_fCombatTime_Curr += fDeltaTime;
			if (m_fCombatTime_Curr >= m_fCombatTime_End)
			{
				m_fCombatTime_Curr = 0.0f;
				m_bCrazy = false;
				//ChangeState(static_cast<int32>(E_StateAI_EnemyE3::E_Combat));
				return;
			}
		}
	}
}

void UStateAI_EnemyE3_Combat_Crazy::StateMessage(FString StateMessage)
{
	Super::StateMessage(StateMessage);
}
