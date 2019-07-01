#include "GhostTrail_Root.h"
#include "Components/PoseableMeshComponent.h"
#include "Materials/MaterialInstanceDynamic.h"
#include "Materials/Material.h"
#include "Materials/MaterialInterface.h"
#include "Kismet/KismetMaterialLibrary.h"

AGhostTrail_Root::AGhostTrail_Root()
{
	PrimaryActorTick.bCanEverTick = true;

	m_pGhostMesh = CreateDefaultSubobject<UPoseableMeshComponent>(TEXT("GhostMesh"));
	m_pGhostMesh->bReceivesDecals = false;
	m_pGhostMesh->CastShadow = false;
	m_pGhostMesh->SetCollisionObjectType(ECC_WorldDynamic);
	m_pGhostMesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	m_pGhostMesh->SetCollisionResponseToAllChannels(ECR_Ignore);
	m_pGhostMesh->SetCollisionResponseToChannel(ECC_Visibility, ECR_Block);
	RootComponent = m_pGhostMesh;
}

void AGhostTrail_Root::BeginPlay()
{
	Super::BeginPlay();

}

void AGhostTrail_Root::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	Super::EndPlay(EndPlayReason);
	m_pOwnerMesh = nullptr;

	m_pSpawnMaterial.Empty();

}

void AGhostTrail_Root::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AGhostTrail_Root::Spawn(USkeletalMeshComponent * pMesh)
{
	m_pOwnerMesh = pMesh;
	if (m_pMaterial == nullptr || m_pOwnerMesh == nullptr)
	{
		Destroy();
		return;
	}

	m_pGhostMesh->SetSkeletalMesh(m_pOwnerMesh->SkeletalMesh, true);
	m_pGhostMesh->CopyPoseFromSkeletalComponent(m_pOwnerMesh);
	TArray<UMaterialInterface*> pMaterials = m_pGhostMesh->GetMaterials();
	for (int i = 0; i < pMaterials.Num(); i++)
	{
		UMaterialInstanceDynamic* pSpawnMaterial = UKismetMaterialLibrary::CreateDynamicMaterialInstance(m_pOwnerMesh->GetWorld(), m_pMaterial);
		if (pSpawnMaterial == nullptr)
		{
			ULOG(TEXT("asda"));
		}
		m_pSpawnMaterial.Add(pSpawnMaterial);
		m_pGhostMesh->SetMaterial(i, pSpawnMaterial);
	}
}

