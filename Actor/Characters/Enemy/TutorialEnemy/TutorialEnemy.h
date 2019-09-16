// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "AIModule/Classes/GenericTeamAgentInterface.h"
#include "Libraries/Interfaces/Itf_AnimMsgNotify.h"

#include "Revenger.h"
#include "Actor/Characters/Enemy/GC_Enemy.h"
#include "TutorialEnemy.generated.h"

/**
 * 
 */
UCLASS()
class REVENGER_API ATutorialEnemy : public AGC_Enemy, public IItf_AnimMsgNotify, public IGenericTeamAgentInterface
{
	GENERATED_BODY()
	
private:
	UPROPERTY()
		class UCpt_AnimationMng* m_pAnimationMng;

	UPROPERTY()
		class UAnimInst_TutorialEnemy* m_pAnimInstance;

	UPROPERTY()
		class UCpt_ParticleMng* m_pParticleMng;

	UPROPERTY()
		class UCpt_MaterialEffect* m_pMaterialEffect;

	UPROPERTY()
		class UCpt_SoundMng* m_pSoundMng;

	UPROPERTY()
		class UStateMng_TutorialEnemy* m_pStateMng;

private:

	UPROPERTY(EditAnywhere, Category = Option)
		float m_fCurrentHp = 2.0f;
	
public:
	ATutorialEnemy();
	virtual void PossessedBy(AController* NewController);
	virtual void PostInitializeComponents() override;
	virtual void BeginPlay() override;
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;
	virtual void Tick(float DeltaTime) override;
	virtual float TakeDamage(float DamageAmount, struct FDamageEvent const & DamageEvent, class AController * EventInstigator, AActor * DamageCauser) override;


public:
	FGenericTeamId GetGenericTeamId() const override { return 0; }
	virtual void CharacterMessage(FString sMessage) override;

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "Itf_NotifyMessage")
		void Inter_Notify_Message(FName sMessage);

	virtual void Inter_Notify_Message_Implementation(FName sMessage) override;

public:

	UFUNCTION(BlueprintPure)
		FORCEINLINE UCpt_AnimationMng* GetAnimationMng() { return m_pAnimationMng; }

	UFUNCTION(BlueprintPure)
		FORCEINLINE UStateMng_TutorialEnemy* GetStateMng() { return m_pStateMng; }

	FORCEINLINE class UCpt_MaterialEffect* GetMaterialEffect() { return m_pMaterialEffect; }
	FORCEINLINE class UCpt_ParticleMng* GetParticleMng() { return m_pParticleMng; }
	FORCEINLINE class UCpt_SoundMng* GetSoundMng() { return m_pSoundMng; }

};
