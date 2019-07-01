// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "AIModule/Classes/GenericTeamAgentInterface.h"
#include "Libraries/Interfaces/Itf_AnimMsgNotify.h"

#include "Revenger.h"
#include "Actor/Characters/Enemy/GC_Enemy.h"
#include "GBoxEnemy_Long.generated.h"

/**
 * 
 */
UCLASS()
class REVENGER_API AGBoxEnemy_Long : public AGC_Enemy, public IItf_AnimMsgNotify, public IGenericTeamAgentInterface
{
	GENERATED_BODY()

private:
	UPROPERTY()
		class UCpt_AnimationMng* m_pAnimationMng;

	UPROPERTY()
		class UAnimInst_GBoxEnemy_Long* m_pAnimInstance;

	UPROPERTY()
		class UCpt_ParticleMng* m_pParticleMng;

	UPROPERTY()
		class UCpt_SoundMng* m_pSoundMng;

	UPROPERTY()
		class AAIC_GBoxEnemy_Long* m_pAIController;

	UPROPERTY()
		class UStateMng_GBELong* m_pStateMng;

	UPROPERTY()
		class AGBoxEnemyLong_Bullet* m_pBullet;

	UPROPERTY(EditAnywhere, Category = Instance, Meta=(AllowPrivateAccess=true))
		class TSubclassOf<class AGBoxEnemyLong_Bullet> m_pInstance_Bullet;

	UPROPERTY()
		class UCpt_MaterialEffect* m_pMaterialEffect;


	UPROPERTY()
		class UCpt_FootPushLine* m_pFootPushLine;

private:
	float m_fMovementDir = 0.0f;

	UPROPERTY(EditAnywhere, Category = Option)
		float m_fCurrentHp = 2.0f;


	float m_fHeadRotatorNoneTime = 0.0f;
	float m_fHeadRotatorNoneTime_Ago = 0.5f;
	bool m_bUseHeadRotator = false;
	FRotator m_rHeadRotator;

public:
	FORCEINLINE class UAnimInst_GBoxEnemy_Long* GetAnimInstance() { return m_pAnimInstance; }
	FORCEINLINE class UCpt_AnimationMng* GetAnimationMng() { return m_pAnimationMng; }
	FORCEINLINE class UStateMng_GBELong* GetStateMng() { return m_pStateMng; }
	FORCEINLINE class AAIC_GBoxEnemy_Long* GetAI() { return m_pAIController; }
	FORCEINLINE class UCpt_ParticleMng* GetParticleMng() { return m_pParticleMng; }
	FORCEINLINE class UCpt_MaterialEffect* GetMaterialEffect() { return m_pMaterialEffect; }
public:
	AGBoxEnemy_Long();
	virtual void PossessedBy(AController* NewController);
	virtual void PostInitializeComponents() override;
	virtual void BeginPlay() override;
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;
	virtual void Tick(float DeltaTime) override;
	virtual float TakeDamage(float DamageAmount, struct FDamageEvent const & DamageEvent, class AController * EventInstigator, AActor * DamageCauser) override;

private:
	void AnimInst_Tick();

public:
	void SetMovementDirection(float fDir) { m_fMovementDir = fDir; }
	AGBoxEnemyLong_Bullet* CreateBullet(FVector vShootLoc, FVector vTargetLoc);

	bool Controll_Attack(class AActor* pActor);

	void HeadRotator_Tick(float fDeltaTime);
	void HeadRotator_Use(FRotator rLookRotator, float fDeltaTime);

public:
	FGenericTeamId GetGenericTeamId() const override { return 0; }
	virtual void CharacterMessage(FString sMessage) override;

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "Itf_NotifyMessage")
		void Inter_Notify_Message(FName sMessage);
	virtual void Inter_Notify_Message_Implementation(FName sMessage) override;
};
