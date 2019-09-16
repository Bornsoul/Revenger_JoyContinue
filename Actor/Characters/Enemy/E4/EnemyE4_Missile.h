// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Revenger.h"
#include "GameFramework/Actor.h"
#include "EnemyE4_Missile.generated.h"

UCLASS()
class REVENGER_API AEnemyE4_Missile : public AActor
{
	GENERATED_BODY()
public:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
		class USphereComponent* m_pCollider;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
		class UStaticMeshComponent* m_pMesh;

	UPROPERTY()
		class UCpt_ParticleMng* m_pParticleMng;

	//UPROPERTY()
	//	class UCpt_GameSave* m_pSaveData;

protected:
	float m_fMoveSpeed = 2500.0f;
	bool m_bShooted = false;

	bool m_bReflected = false;

	bool m_bReflectWaitTime = false;
	float m_fReflectWiatTime_Curr = 0.0f;
	float m_fReflectWiatTime_Ago = 0.3f;

	float m_fReflectDamage = 0.0f;

	AActor* m_pShooter;

	float m_fLifeTime = 0.0f;

	UPROPERTY()
		AActor * m_pDamageCauser;

	UPROPERTY()
		AActor* m_pTarget;

	bool m_bChase = false;

	bool m_bSuccessHit = false;

public:
	AEnemyE4_Missile();
	virtual void BeginPlay() override;
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;
	virtual void Tick(float DeltaTime) override;
	virtual float TakeDamage(float DamageAmount, struct FDamageEvent const & DamageEvent, class AController * EventInstigator, AActor * DamageCauser) override;

public:
	void Shoot(AActor* pShooter, FVector vLocation, FVector vDestLoc);
	void ShootToTarget(AActor* pShooter, FVector vLocation, AActor* pTarget);
	void Reflect(FVector vDestLoc);
	void Explosion();

	UFUNCTION(BlueprintCallable)
		void SetSuccessHit(bool bSuccessHit) { m_bSuccessHit = bSuccessHit; }
	
	UFUNCTION(BlueprintPure)
		bool GetSuccessHit() { return m_bSuccessHit; }

	UFUNCTION()
		void OnOverlapBegin(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
};
