// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Materials/MaterialInstanceDynamic.h"
#include "Materials/MaterialInterface.h"

#include "Revenger.h"
#include "Components/ActorComponent.h"
#include "Cpt_MaterialEffect.generated.h"

UENUM()
enum class E_MaterialEffect : uint8
{
	E_Hit UMETA(DisplayName = "Hit"),
	E_Hit2 UMETA(DisplayName = "Hit"),
	E_Disint UMETA(DisplayName = "Disint"),

	E_MAX,
};

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class REVENGER_API UCpt_MaterialEffect : public UActorComponent
{
	GENERATED_BODY()

private:
	UPROPERTY()
		class USkeletalMeshComponent* m_pSkeletal_Mesh;

	UPROPERTY()
		class UStaticMeshComponent* m_pStatic_Mesh;

	UPROPERTY()
		TArray<UMaterialInstanceDynamic*> m_pSpawnMaterial;

	UPROPERTY()
		TMap<int, class UMaterialEffect_Root*> m_pEffectList;

	UPROPERTY()
		TMap<int, class UMaterialEffect_Root*> m_pEffectList_Running;

	bool m_bInit = false;
	bool m_bIsSkeletalMesh = false;

public:
	UCpt_MaterialEffect();
	virtual void BeginPlay() override;
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	void Init(class USkeletalMeshComponent* pMesh);
	void Init(class UStaticMeshComponent* pMesh);

	void AddEffect(E_MaterialEffect eEffect);

	void ActiveEffect(E_MaterialEffect eEffect);
	void ActiveEffect_Hit();

	TArray<UMaterialInstanceDynamic*> GetMaterials() { return m_pSpawnMaterial; }
private:
	void TickEffects(float fDeltaTime);

	class UMaterialEffect_Root* GetEffect(E_MaterialEffect eEffect);
	bool CheckEffectRunning(E_MaterialEffect eEffect);
};
