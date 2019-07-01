// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Revenger.h"
#include "GameFramework/Actor.h"
#include "GhostTrail_Root.generated.h"

UCLASS()
class REVENGER_API AGhostTrail_Root : public AActor
{
	GENERATED_BODY()

public:
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Mesh")
		class UPoseableMeshComponent* m_pGhostMesh;

protected:
	UPROPERTY(EditDefaultsOnly, Category = "Material", Meta = (AllowPrivateAccess = true))
		class UMaterialInterface* m_pMaterial;


	UPROPERTY()
		class USkeletalMeshComponent* m_pOwnerMesh;

	UPROPERTY()
		TArray<class UMaterialInstanceDynamic*> m_pSpawnMaterial;

public:
	AGhostTrail_Root();
	virtual void BeginPlay() override;
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;
	virtual void Tick(float DeltaTime) override;

	virtual void Spawn(class USkeletalMeshComponent* pMesh);
};
