// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "AIModule/Classes/GenericTeamAgentInterface.h"
#include "Libraries/Interfaces/Itf_AnimMsgNotify.h"
#include "Libraries/Components/KeyStateMng/Cpt_KeyStateMng.h"

#include "Revenger.h"
#include "Actor/Characters/Npc/GC_Npc.h"
#include "Citizen.generated.h"

UCLASS()
class REVENGER_API ACitizen : public AGC_Npc, public IItf_AnimMsgNotify, public IGenericTeamAgentInterface
{
	GENERATED_BODY()

private:
	UPROPERTY()
		class UCpt_AnimationMng* m_pAnimationMng;

	UPROPERTY()
		class UAnimInst_Citizen* m_pAnimInstance;

	UPROPERTY()
		class AAIC_Citizen* m_pAIController;

	UPROPERTY()
		class UCpt_KeyStateMng* m_pKeyStateMng;

	UPROPERTY()
		class AGBox* m_pPlayer;

	bool m_bActive = false;
	bool m_bHappyMotion = false;
	bool m_bFreeMotionEnd = false;
	bool m_bState_Happy = false;

private:
	UPROPERTY(EditAnywhere, Category = CitizenOption)
		float m_fHappyRadius = 500.0f;

	UPROPERTY(EditAnywhere, Category = CitizenOption)
		float m_fInterpSpeed = 15.0f;

public:
	ACitizen();
	virtual void PossessedBy(AController* NewController) override;
	virtual void PostInitializeComponents() override;
	virtual void BeginPlay() override;
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;
	virtual void Tick(float DeltaTime) override;
	virtual float TakeDamage(float DamageAmount, struct FDamageEvent const & DamageEvent, class AController * EventInstigator, AActor * DamageCauser) override;
	
	void AnimInst_Tick();
	void SetUpdateActive(bool bActive) { m_bActive = bActive; }

	void Control_Free();

public:
	FGenericTeamId GetGenericTeamId() const override { return 0; }
	virtual void CharacterMessage(FString sMessage) override;

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "Itf_NotifyMessage")
		void Inter_Notify_Message(FName sMessage);
	virtual void Inter_Notify_Message_Implementation(FName sMessage) override;

	UFUNCTION(BlueprintPure)
		bool GetHappying() { return m_bHappyMotion; }
	
	UFUNCTION(BlueprintPure)
		bool GetHappyMotion() { return m_bState_Happy; }

	UFUNCTION(BlueprintCallable)
		void SetHappyMotion(bool bHappy) { m_bState_Happy = bHappy;  }

public:
	FORCEINLINE class UCpt_AnimationMng* GetAnimationMng() { return m_pAnimationMng; }

};
