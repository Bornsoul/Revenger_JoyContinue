// Fill out your copyright notice in the Description page of Project Settings.

#include "WarningSpace_Root.h"
#include "Components/StaticMeshComponent.h"
#include "Materials/MaterialInstanceDynamic.h"
#include "Materials/MaterialInterface.h"
#include "Kismet/KismetMaterialLibrary.h"

// Sets default values
AWarningSpace_Root::AWarningSpace_Root()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	m_pMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	m_pMesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);

	//
	static ConstructorHelpers::FObjectFinder<UStaticMesh>MeshAsset(TEXT("StaticMesh'/Engine/BasicShapes/Plane.Plane'"));
	UStaticMesh* Asset = MeshAsset.Object;

	m_pMesh->SetStaticMesh(Asset);

	RootComponent = m_pMesh;
}

// Called when the game starts or when spawned
void AWarningSpace_Root::BeginPlay()
{
	Super::BeginPlay();
	UMaterialInterface* pMaterial = m_pMesh->GetMaterial(0);
	m_pMaterial = UKismetMaterialLibrary::CreateDynamicMaterialInstance(GetWorld(), pMaterial);
	m_pMesh->SetMaterial(0, m_pMaterial);

}

// Called every frame
void AWarningSpace_Root::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	Tick_Space(DeltaTime);
}

void AWarningSpace_Root::SpawnSpace(float fWarningTime, FVector vLocation, FRotator vRotation, FVector vScale)
{
	if (m_pMaterial == nullptr) return;
	m_fWarningTime_Curr = 0.0f;
	m_fWarningTime = fWarningTime;
	m_bActive = true;

	SetActorLocation(vLocation);
	SetActorRotation(vRotation);
	SetActorScale3D(vScale);
}

void AWarningSpace_Root::StopSpace()
{
	if (m_pMaterial == nullptr) return;
	m_bActive = false;

	Destroy();
}

void AWarningSpace_Root::Tick_Space(float fDeltaTime)
{
	if (m_bActive == false) return;
	
	m_fWarningTime_Curr += fDeltaTime;
	m_pMaterial->SetScalarParameterValue("ProgressValue", m_fWarningTime_Curr / m_fWarningTime * 1.0f);
	if (m_fWarningTime_Curr >= m_fWarningTime)
	{
		
		StopSpace();
	}
}

