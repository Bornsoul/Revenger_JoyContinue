// Fill out your copyright notice in the Description page of Project Settings.

#include "StateAI_EnemyE4_Combat_DistMove.h"
#include "Actor/Characters/Enemy/E4/EnemyE4.h"
#include "Kismet/KismetMathLibrary.h"

void UStateAI_EnemyE4_Combat_DistMove::Init(class UStateMng_AI* pMng)
{
	Super::Init(pMng);

}

void UStateAI_EnemyE4_Combat_DistMove::Enter()
{
	Super::Enter();

	m_fCombatTime_Curr = 0.0f;
	m_fCombatTime_End = FMath::RandRange(1.0f, 2.0f);
	//GetRootAI()->StopMovement();

	AActor* pDetectTarget = GetRootAI()->DetectInPerception();
	//GetRootAI()->GetRootChar()->Controll_Moving();

	if (pDetectTarget != nullptr)
	{
		GetRootAI()->GetRootChar()->Controll_Attack(pDetectTarget);
	}

	//ULOG(TEXT("E4 Combat_DistMove"));
}

void UStateAI_EnemyE4_Combat_DistMove::Exit()
{
	Super::Exit();

}

void UStateAI_EnemyE4_Combat_DistMove::Update(float fDeltaTime)
{
	Super::Update(fDeltaTime);

	m_fCombatTime_Curr += fDeltaTime;
	if (m_fCombatTime_Curr >= m_fCombatTime_End)
	{
		m_fCombatTime_Curr = 0.0f;


		ChangeState(static_cast<int32>(E_StateAI_EnemyE4::E_Combat));
		return;

	}

	AActor* pDetectTarget = GetRootAI()->DetectInPerception();
	if (pDetectTarget != nullptr)
	{
		AEnemyE4* pRootCharacter = GetRootAI()->GetRootChar();

		FRotator pLookRotation = UKismetMathLibrary::FindLookAtRotation(pRootCharacter->GetActorLocation(), pDetectTarget->GetActorLocation());
		pLookRotation.Pitch = 0.0f;
		pLookRotation.Roll = 0.0f;
		FRotator pInterp = UKismetMathLibrary::RInterpTo(pRootCharacter->GetActorRotation(), pLookRotation, fDeltaTime, 18.0f);
		pRootCharacter->SetActorRotation(pInterp);

		float fDistanceChar = FVector::Dist(pRootCharacter->GetActorLocation(), pDetectTarget->GetActorLocation());

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
		}
	}

	//

	///*AActor* pTarget = GetRootAI()->DetectInPerception();

	//if (pTarget != nullptr)
	//{
	//	FVector vEnemyPos = GetRootAI()->GetRootChar()->GetActorLocation();
	//	FVector vTargetPos = pTarget->GetActorLocation();
	//	float fDistance = FVector::Distance(vEnemyPos, vTargetPos);

	//	if (fDistance >= 700.0f)
	//	{
	//		EPathFollowingRequestResult::Type pResult = GetRootAI()->MoveToLocation(vTargetPos);
	//	}
	//}*/

	//AActor* pDetectTarget = GetRootAI()->DetectInPerception();
	//if (pDetectTarget != nullptr)
	//{
	//	AEnemyE4* pRootCharacter = GetRootAI()->GetRootChar();

	//	FRotator pLookRotation = UKismetMathLibrary::FindLookAtRotation(pRootCharacter->GetActorLocation(), pDetectTarget->GetActorLocation());
	//	pLookRotation.Pitch = 0.0f;
	//	pLookRotation.Roll = 0.0f;
	//	FRotator pInterp = UKismetMathLibrary::RInterpTo(pRootCharacter->GetActorRotation(), pLookRotation, fDeltaTime, 18.0f);
	//	pRootCharacter->SetActorRotation(pInterp);

	//	float fDistanceChar = FVector::Dist(pRootCharacter->GetActorLocation(), pDetectTarget->GetActorLocation());

	//	m_fCombatTime_Curr += fDeltaTime;
	//	if (m_fCombatTime_Curr >= m_fCombatTime_End)
	//	{
	//		m_fCombatTime_Curr = 0.0f;
	//		//GetRootAI()->StopMovement();

	//		if (GetRootAI()->GetRootChar()->Controll_Attack(pDetectTarget))
	//		{
	//			ChangeState(static_cast<int32>(E_StateAI_EnemyE4::E_Combat));
	//			return;
	//		}
	//	}

	//	/*if (fDistanceChar <= 200.0f)
	//	{
	//		if (GetRootAI()->GetRootChar()->Controll_Attack(pDetectTarget))
	//		{
	//			ChangeState(static_cast<int32>(E_StateAI_EnemyE4::E_Combat));
	//			return;
	//		}
	//	}*/

	//	if (FMath::Abs(fDistanceChar - m_fStayDistance) > 15.0f)
	//	{
	//		FVector vForwardVector = pRootCharacter->GetActorLocation() - pDetectTarget->GetActorLocation();
	//		vForwardVector.Normalize();
	//		FVector vDestLoc = pDetectTarget->GetActorLocation() + vForwardVector * m_fStayDistance;
	//		if (FVector::Dist(vDestLoc, pRootCharacter->GetActorLocation()) > 5.0f)
	//		{
	//			EPathFollowingRequestResult::Type pResult = GetRootAI()->MoveToLocation(vDestLoc);

	//			FRotator rCapsuleRota = pRootCharacter->GetCapsuleComponent()->GetComponentRotation();
	//			FRotator pMoveRota = UKismetMathLibrary::FindLookAtRotation(pRootCharacter->GetActorLocation(), vDestLoc);
	//			FRotator pRota_Normal = UKismetMathLibrary::NormalizedDeltaRotator(rCapsuleRota, pMoveRota);
	//			pRootCharacter->SetMovementDirection(pRota_Normal.Yaw);
	//		}
	//	}
	//}
}

void UStateAI_EnemyE4_Combat_DistMove::StateMessage(FString StateMessage)
{
	Super::StateMessage(StateMessage);
}




