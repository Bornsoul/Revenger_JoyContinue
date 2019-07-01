// Fill out your copyright notice in the Description page of Project Settings.

#include "Cpt_FootPushGround.h"
#include "Components/StaticMeshComponent.h"

// Sets default values for this component's properties
UCpt_FootPushGround::UCpt_FootPushGround()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	
}


// Called when the game starts
void UCpt_FootPushGround::BeginPlay()
{
	Super::BeginPlay();
	GetOwner()->Tags.Add(FName("PushGround"));

	UActorComponent* pActorCpt =  GetOwner()->GetComponentByClass(UStaticMeshComponent::StaticClass());
	if (pActorCpt != nullptr)
	{
		UStaticMeshComponent* pMesh = Cast<UStaticMeshComponent>(pActorCpt);
		if (pMesh != nullptr)
		{
			pMesh->SetCollisionResponseToChannel(ECC_GameTraceChannel5, ECR_Block);
			//pMesh->SetCollisionResponseToChannel(EC)

			m_vOriginLocation = pMesh->GetRelativeTransform().GetLocation();

			m_pMesh = pMesh;
			//ULOG(TEXT("Mesh On"));
		}
	}

	
	
	
}


// Called every frame
void UCpt_FootPushGround::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if (m_bPushState == true)
	{
		m_fResetTime += DeltaTime;
		if (m_fResetTime > m_fResetTime_Ago)
		{
			Ground_Push_Out();
			m_fResetTime = 0.0f;
		}
	}
}

