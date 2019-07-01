// Fill out your copyright notice in the Description page of Project Settings.

#include "Cpt_FootPushLine.h"
#include "Cpt_FootPushGround.h"
#include "Actor/Characters/GameCharacter.h"
#include "Kismet/KismetMathLibrary.h"

// Sets default values for this component's properties
UCpt_FootPushLine::UCpt_FootPushLine()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UCpt_FootPushLine::BeginPlay()
{
	Super::BeginPlay();

	
	
}

void UCpt_FootPushLine::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	Super::EndPlay(EndPlayReason);
	m_pMesh = nullptr;
	m_pCapsule = nullptr;
	m_pBoneList.Empty();
}

// Called every frame
void UCpt_FootPushLine::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	Tick_PushLine(DeltaTime);
}

void UCpt_FootPushLine::SetSKMesh(AGameCharacter* pChar)
{
	m_pMesh = pChar->GetMesh();
	m_pCapsule = pChar->GetCapsuleComponent();
	m_fDefaultHeight = m_pCapsule->GetScaledCapsuleHalfHeight();
	m_vDefaultMeshLoc = m_pMesh->GetRelativeTransform().GetLocation();


	//m_vLineStart = FVector(pSocketLocation.X, pSocketLocation.Y, pSocketLocation.Z);
}

void UCpt_FootPushLine::AddBone(FString sBoneName)
{
	if (m_pMesh == nullptr) return;
	m_pBoneList.Add(sBoneName);
	
}

void UCpt_FootPushLine::Tick_PushLine(float fDeltaTime)
{
	if (m_pMesh == nullptr) return;

	float fLongDistance = 0.0f;
	for (int i = 0; i < m_pBoneList.Num(); i++)
	{
		FVector pSocketLocation = m_pMesh->GetSocketLocation(*m_pBoneList[i]);
		FVector pLine_Start = FVector(pSocketLocation.X, pSocketLocation.Y, pSocketLocation.Z);// m_pLineStartList[i].Z);
		FVector pLine_End = pLine_Start - FVector::UpVector * 300.0f;

		//! Process Line Trace
		FHitResult pHitResult;
		TArray<AActor*> pIgnore;
		pIgnore.Add(GetOwner());

		bool bDebug = false;
		EDrawDebugTrace::Type eDebug = EDrawDebugTrace::None;
		if (bDebug == true) eDebug = EDrawDebugTrace::ForOneFrame;

		bool bResult = UKismetSystemLibrary::LineTraceSingle(GetWorld(), pLine_Start, pLine_End,
			UEngineTypes::ConvertToTraceType(ECC_GameTraceChannel5), true, pIgnore, eDebug, pHitResult, true);

		if (bResult == true)
		{
			AActor* pHitActor = pHitResult.GetActor();
			if (pHitActor != nullptr)
			{
				if (pHitActor->ActorHasTag("PushGround") == true || pHitActor->ActorHasTag("PushGround_Piano") == true)
				{
					UActorComponent* pActorCpt = pHitActor->GetComponentByClass(UCpt_FootPushGround::StaticClass());
					if (pActorCpt != nullptr)
					{
						UCpt_FootPushGround* pGround = Cast<UCpt_FootPushGround>(pActorCpt);
						if (pGround != nullptr)
						{
							pGround->Ground_Push_In();
							
							float fDistance = FMath::Abs(pHitResult.ImpactPoint.Z - m_pMesh->GetComponentLocation().Z);
							if (fDistance > fLongDistance)
							{
								fLongDistance = fDistance;
							}
						}
					}
					
				}
			}
		}	
	}

	
/*
	UKismetSystemLibrary::PrintString(GetWorld(), FString::SanitizeFloat(fLongDistance), true, false,
		FLinearColor::Blue, 0.0f);

	FVector vMeshLoc = m_pMesh->GetRelativeTransform().GetLocation();
	float fDestLoc = m_vDefaultMeshLoc.Z - fLongDistance;
	//vMeshLoc.Z = UKismetMathLibrary::FInterpTo(m_pMesh->GetRelativeTransform().GetLocation().Z, fDestLoc, fDeltaTime, 13.0f);
	vMeshLoc.Z = fDestLoc;
	m_pMesh->SetRelativeLocation(vMeshLoc);*/
}
