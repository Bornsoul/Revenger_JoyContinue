// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "AIModule/Classes/GenericTeamAgentInterface.h"
#include "Libraries/Interfaces/Itf_AnimMsgNotify.h"

#include "Revenger.h"
#include "Actor/Characters/Enemy/GC_Enemy.h"
#include "EnemyE3.generated.h"

/**
 * 
 */
UCLASS()
class REVENGER_API AEnemyE3 : public AGC_Enemy, public IItf_AnimMsgNotify, public IGenericTeamAgentInterface
{
	GENERATED_BODY()
private:
	UPROPERTY()
		class UCpt_AnimationMng* m_pAnimationMng;

	UPROPERTY()
		class UAnimInst_EnemyE3* m_pAnimInstance;

	UPROPERTY()
		class UCpt_ParticleMng* m_pParticleMng;

	UPROPERTY()
		class UCpt_SoundMng* m_pSoundMng;

	UPROPERTY()
		class UStateMng_EnemyE3* m_pStateMng;

	UPROPERTY()
		class UCpt_MaterialEffect* m_pMaterialEffect;

	UPROPERTY()
		class UCpt_FootPushLine* m_pFootPushLine;
	
	UPROPERTY()
		class AAIC_EnemyE3* m_pAIController;

	UPROPERTY()
		class UCpt_WarningSpace* m_pWarningSpace;

	UPROPERTY()
		class UCpt_EnemyHp* m_pHp;

public:
	FORCEINLINE class UAnimInst_EnemyE3* GetAnimInstance() { return m_pAnimInstance; }
	FORCEINLINE class UCpt_AnimationMng* GetAnimationMng() { return m_pAnimationMng; }
	FORCEINLINE class UStateMng_EnemyE3* GetStateMng() { return m_pStateMng; }
	FORCEINLINE class UCpt_MaterialEffect* GetMaterialEffect() { return m_pMaterialEffect; }
	FORCEINLINE class UCpt_ParticleMng* GetParticleMng() { return m_pParticleMng; }
	FORCEINLINE class UCpt_SoundMng* GetSoundMng() { return m_pSoundMng; }
	FORCEINLINE class AAIC_EnemyE3* GetAI() { return m_pAIController; }
	FORCEINLINE class UCpt_WarningSpace* GetWarningSpace() { return m_pWarningSpace; }

private:
	float m_fMovementDir = 0.0f;

	UPROPERTY(EditAnywhere, Category = Option)
		float m_fCurrentHp = 2.0f;

	UPROPERTY(EditAnywhere, Category = HpBar)
		FVector m_vHpPos = FVector(40.0f, 40.0f, 40.0f);

	UPROPERTY(EditAnywhere, Category = HpBar)
		FVector2D m_vHpSize = FVector2D(40.0f, 40.0f);

	bool m_bHpDestroy = false;

public:
	AEnemyE3();
	virtual void PossessedBy(AController* NewController);
	virtual void PostInitializeComponents() override;
	virtual void BeginPlay() override;
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;
	virtual void Tick(float DeltaTime) override;
	virtual float TakeDamage(float DamageAmount, struct FDamageEvent const & DamageEvent, class AController * EventInstigator, AActor * DamageCauser) override;

public:
	void SetMovementDirection(float fDir) { m_fMovementDir = fDir; }
	bool Controll_Attack(class AActor* pActor);
public:
	FGenericTeamId GetGenericTeamId() const override { return 0; }
	virtual void CharacterMessage(FString sMessage) override;

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "Itf_NotifyMessage")
		void Inter_Notify_Message(FName sMessage);
	virtual void Inter_Notify_Message_Implementation(FName sMessage) override;
};
