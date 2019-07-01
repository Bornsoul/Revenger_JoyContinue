// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Revenger.h"
#include "Components/ActorComponent.h"
#include "Cpt_GhostTrail.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class REVENGER_API UCpt_GhostTrail : public UActorComponent
{
	GENERATED_BODY()

private:
	UPROPERTY(EditDefaultsOnly, Category = "GhostTrail", Meta = (AllowPrivateAccess = true))
		TMap<FString, TSubclassOf<class AGhostTrail_Root>> m_pEffect_List;

	UPROPERTY()
		class ACharacter* m_pOwnerChar;


	UPROPERTY()
		TMap<FString, class UMdl_GhostTrail_TickSpawn*> m_pEffectTickSpawnModule_List;

public:
	UCpt_GhostTrail();
	virtual void BeginPlay() override;
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	void Add_GhostTrailEffectActor(FString sName, FString sPath);

	class TSubclassOf<class AGhostTrail_Root> GetGhostTrailEffectActor(FString sName);

	UFUNCTION(BlueprintCallable, Category = "Event")
		void Spawn_GhostTrailEffect(FString sName, FTransform tSpawnTransform);

	void Spawn_GhostTrailEffect(FString sName);


	void Active_TickGhostTrailEffect(FString sName, float fIntervalTime = 0.1f, float fTickTime = 999.0f);
	void DeActive_TickGhostTrailEffect(FString sName);
	void Tick_GhostTrailEffect(float fDeltaTime);

	bool CheckOverlapTickEffect(FString sName);

};