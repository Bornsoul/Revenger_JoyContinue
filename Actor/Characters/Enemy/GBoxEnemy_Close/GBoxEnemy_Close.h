// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "AIModule/Classes/GenericTeamAgentInterface.h"
#include "Libraries/Interfaces/Itf_AnimMsgNotify.h"

#include "Revenger.h"
#include "Actor/Characters/Enemy/GC_Enemy.h"
#include "GBoxEnemy_Close.generated.h"

/**
 * 
 */
UCLASS()
class REVENGER_API AGBoxEnemy_Close : public AGC_Enemy, public IItf_AnimMsgNotify, public IGenericTeamAgentInterface
{
	GENERATED_BODY()
	
private:
	UPROPERTY()
		class UCpt_AnimationMng* m_pAnimationMng;

	UPROPERTY()
		class UAnimInst_GBoxEnemy_Close* m_pAnimInstance;

	UPROPERTY()
		class UCpt_ParticleMng* m_pParticleMng;

	UPROPERTY()
		class UCpt_SoundMng* m_pSoundMng;

	UPROPERTY()
		class AAIC_GBoxEnemy_Close* m_pAIController;

	UPROPERTY()
		class UStateMng_GBEClose* m_pStateMng;

	UPROPERTY()
		class UCpt_MaterialEffect* m_pMaterialEffect;

	/*UPROPERTY()
		class UCpt_EnemyHp* m_pHp;*/

	UPROPERTY()
		class UCpt_EnemyBossHp* m_pBossHp;

	UPROPERTY(EditAnywhere, Category = HpBar)
		FVector2D m_vHpPos = FVector2D(10.0f, 10.0f);
	
	UPROPERTY(EditAnywhere, Category = HpBar)
		float m_fHpSize = 20.0f;

	/*UPROPERTY()
		class USC_WidgetEnemyHp* m_pHp;

	UPROPERTY(EditAnywhere, Category = HpBar)
		FVector2D m_vHpPos = FVector2D(0.0f, 0.0f);

	UPROPERTY(EditAnywhere, Category = HpBar)
		FVector2D m_vHpSize = FVector2D(10.0f, -10.0f);*/

	
	UPROPERTY()
		class UCpt_FootPushLine* m_pFootPushLine;

	UPROPERTY()
		class UCpt_CamShake* m_pCamShake;

	UPROPERTY()
		class UCpt_WarningSpace* m_pWarningSpace;

	UPROPERTY()
		class TSubclassOf<class AEnemyBarrier> m_pInst_Barrier;

	UPROPERTY()
		class AEnemyBarrier* m_pBarrier;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = SpawnAI, meta = (AllowPrivateAccess = "true"))
		class ABossEnemySpawnMng* m_pSpawnMng;

private:
	float m_fMovementDir = 0.0f;

	UPROPERTY(EditAnywhere, Category = Option)
		float m_fCurrentHp = 3.0f;

	float m_fEnemyCheckTime = 0.0f;
	bool m_bEnemyCheck = false;

	bool m_bHpDestroy = false;


public:
	FORCEINLINE class UAnimInst_GBoxEnemy_Close* GetAnimInstance() { return m_pAnimInstance; }
	FORCEINLINE class UCpt_AnimationMng* GetAnimationMng() { return m_pAnimationMng; }
	FORCEINLINE class UStateMng_GBEClose* GetStateMng() { return m_pStateMng; }
	FORCEINLINE class AAIC_GBoxEnemy_Close* GetAI() { return m_pAIController; }
	FORCEINLINE class UCpt_MaterialEffect* GetMaterialEffect() { return m_pMaterialEffect; }
	FORCEINLINE class UCpt_ParticleMng* GetParticleMng() { return m_pParticleMng; }
	FORCEINLINE class UCpt_SoundMng* GetSoundMng() { return m_pSoundMng; }
	FORCEINLINE class UCpt_CamShake* GetCamShake() { return m_pCamShake; }
	FORCEINLINE class UCpt_WarningSpace* GetWarningSpace() { return m_pWarningSpace; }
	FORCEINLINE class AEnemyBarrier* GetBarrier() { return m_pBarrier; }
	FORCEINLINE class ABossEnemySpawnMng* GetAISpawnMng() { return m_pSpawnMng; }

public:
	AGBoxEnemy_Close();
	virtual void PossessedBy(AController* NewController);
	virtual void PostInitializeComponents() override;
	virtual void BeginPlay() override;
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;
	virtual void Tick(float DeltaTime) override;
	virtual float TakeDamage(float DamageAmount, struct FDamageEvent const & DamageEvent, class AController * EventInstigator, AActor * DamageCauser) override;

private:
	void AnimInst_Tick();
	void Tick_EnemyCheck(float fDeltaTime);

public:
	void SetMovementDirection(float fDir) { m_fMovementDir = fDir; }
	
	bool Controll_Attack(class AActor* pActor);
	bool Controll_Attack2(class AActor* pActor);
	bool Controll_JumpAttack(class AActor* pActor);
	bool Controll_Spin(class AActor* pActor);
	bool Controll_Dash(class AActor* pActor);


	void Active_Barrier();
	void Hit_Barrier();
	void DeActive_Barrier();

	void SpawnMonsters();

public:
	FGenericTeamId GetGenericTeamId() const override { return 0; }
	virtual void CharacterMessage(FString sMessage) override;

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "Itf_NotifyMessage")
		void Inter_Notify_Message(FName sMessage);
	virtual void Inter_Notify_Message_Implementation(FName sMessage) override;
};
