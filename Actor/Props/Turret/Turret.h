// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Revenger.h"
#include "GameFramework/Actor.h"
#include "Turret.generated.h"

UCLASS()
class REVENGER_API ATurret : public AActor
{
	GENERATED_BODY()
	
public:	

	UPROPERTY()
		class USceneComponent* m_pSceneComp;

	UPROPERTY(BlueprintReadWrite, VisibleAnywhere, Category = "Option", meta = (AllowPrivateAccess = "true"))
		class UArrowComponent* m_pBulletArrowComp;

	UPROPERTY(BlueprintReadWrite, VisibleAnywhere, Category ="Option", meta = (AllowPrivateAccess = "true"))
		class UArrowComponent* m_pArrowComp;

	UPROPERTY(EditAnywhere, Category = Instance, Meta = (AllowPrivateAccess = true))
		class TSubclassOf<class AEnemyE4_Missile> m_pInstance_Bullet;

	UPROPERTY()
		class UCpt_ParticleMng* m_pParticleMng;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = Instance, Meta = (AllowPrivateAccess = true))
		class UParticleSystemComponent* m_pLaserParticle;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = Instance, Meta = (AllowPrivateAccess = true))
		float m_fLaserTime = 1.5f;

	//UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = Instance, Meta = (AllowPrivateAccess = true))
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = Instance, Meta = (AllowPrivateAccess = true))
		class AEnemyE4_Missile* m_pBullet;

	bool m_bActive = false;
	float m_fTime = 0.0f;

	int32 nState = 0;
	bool m_bLaser = false;
	bool m_bShoot = false;
	//bool m_bDestroyLaser = false;

	bool m_bSuccessHit = false;

public:	
	ATurret();
	virtual void BeginPlay() override;
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;
	virtual void Tick(float DeltaTime) override;
	AEnemyE4_Missile* CreateBullet(FVector vShootLoc, FVector vTargetLoc);

	UFUNCTION(BlueprintCallable)
		void SetSuccessHit(bool bHit) { m_bSuccessHit = bHit; }

	UFUNCTION(BlueprintPure)
		bool GetSuccessHit() { return m_bSuccessHit; }

	UFUNCTION(BlueprintCallable)
		void SetTurretActive(bool bActive);

	UFUNCTION(BlueprintPure)
		bool GetActiveState() { return m_bActive; }

	UFUNCTION(BlueprintPure)
		int32 GetState() { return nState; }
};
