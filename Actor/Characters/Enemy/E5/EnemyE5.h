// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "AIModule/Classes/GenericTeamAgentInterface.h"
#include "Libraries/Interfaces/Itf_AnimMsgNotify.h"

#include "Revenger.h"
#include "Actor/Characters/Enemy/GC_Enemy.h"
#include "EnemyE5.generated.h"

/**
 * 
 */
UCLASS()
class REVENGER_API AEnemyE5 : public AGC_Enemy, public IItf_AnimMsgNotify, public IGenericTeamAgentInterface
{
	GENERATED_BODY()
	
private:
	UPROPERTY()
		class UCpt_AnimationMng* m_pAnimationMng;

	UPROPERTY()
		class UAnimInst_EnemyE5* m_pAnimInstance;

	UPROPERTY()
		class UCpt_ParticleMng* m_pParticleMng;

	UPROPERTY()
		class UCpt_MaterialEffect* m_pMaterialEffect;

	UPROPERTY()
		class UCpt_SoundMng* m_pSoundMng;

	UPROPERTY()
		class UCpt_FootPushLine* m_pFootPushLine;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Property", meta = (AllowPrivateAccess = "true"))
		class UCpt_EnemyHpComponent* m_pHpHud;

	UPROPERTY()
		class AAIC_EnemyE5* m_pAIController;

	UPROPERTY()
		class UStateMng_EnemyE5* m_pStateMng;

	UPROPERTY(VisibleAnywhere)
		class TSubclassOf<class AEnemyE5_Missile> m_pInstance_Bullet;

	bool m_bShoot = false;
	bool m_bCombat = false;

	bool m_bHpDestroy = false;

public:
	FORCEINLINE class UAnimInst_EnemyE5* GetAnimInstance() { return m_pAnimInstance; }
	FORCEINLINE class UCpt_AnimationMng* GetAnimationMng() { return m_pAnimationMng; }	
	FORCEINLINE class UCpt_ParticleMng* GetParticleMng() { return m_pParticleMng; }
	FORCEINLINE class UCpt_MaterialEffect* GetMaterialEffect() { return m_pMaterialEffect; }
	FORCEINLINE class UCpt_SoundMng* GetSoundMng() { return m_pSoundMng; }
	FORCEINLINE class AAIC_EnemyE5* GetAI() { return m_pAIController; }
	FORCEINLINE class UStateMng_EnemyE5* GetStateMng() { return m_pStateMng; }
	
	FORCEINLINE bool GetCombatState() { return m_bCombat;  }
private:
	float m_fMovementDir = 0.0f;

	UPROPERTY(EditAnywhere, Category = Option)
		float m_fCurrentHp = 2.0f;	

public:
	AEnemyE5();
	virtual void PossessedBy(AController* NewController);
	virtual void PostInitializeComponents() override;
	virtual void BeginPlay() override;
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;
	virtual void Tick(float DeltaTime) override;
	virtual float TakeDamage(float DamageAmount, struct FDamageEvent const & DamageEvent, class AController * EventInstigator, AActor * DamageCauser) override;

public:
	void SetMovementDirection(float fDir) { m_fMovementDir = fDir; }
	void SetCombatState(bool bCombat);

	bool Controll_Attack(class AActor* pActor);
	bool Controll_Moving();

	class AEnemyE5_Missile* CreateBullet(FVector vShootLoc, FVector vTargetLoc);
	class AEnemyE5_Missile* CreateBullet(FVector vShootLoc, AActor* pTarget);

	bool GetShoot() { return m_bShoot;  }
	void SetShoot(bool bShoot) { m_bShoot = bShoot; }

public:
	FGenericTeamId GetGenericTeamId() const override { return 0; }
	virtual void CharacterMessage(FString sMessage) override;

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "Itf_NotifyMessage")
		void Inter_Notify_Message(FName sMessage);
	virtual void Inter_Notify_Message_Implementation(FName sMessage) override;
};
