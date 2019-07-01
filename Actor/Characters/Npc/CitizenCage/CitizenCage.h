// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "AIModule/Classes/GenericTeamAgentInterface.h"
#include "Libraries/Interfaces/Itf_AnimMsgNotify.h"

#include "Revenger.h"
#include "Actor/Characters/Npc/GC_Npc.h"
#include "CitizenCage.generated.h"

/**
 * 
 */
UCLASS()
class REVENGER_API ACitizenCage : public AGC_Npc, public IItf_AnimMsgNotify, public IGenericTeamAgentInterface
{
	GENERATED_BODY()

private:
	UPROPERTY()
		class UCpt_AnimationMng* m_pAnimationMng;

	UPROPERTY()
		class UAnimInst_CitizenCage* m_pAnimInstance;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Actor Option", meta = (AllowPrivateAccess = "true"))
		class ACitizen* m_pCitizen;

	UPROPERTY()
		class AMovePortal* m_pPortal;

	UPROPERTY()
		class AGBox* m_pPlayer;

public:
	bool m_bActive = false;


	UPROPERTY(EditAnywhere, Category = Option)
		float m_fCurrentHp = 2.0f;

	bool m_bUpdate = false;
	bool m_bMotionEnd = false;
	float m_fMotionTime_Cur = 0.0f;
	UPROPERTY(EditAnywhere, Category = Option)
		float m_fMotionTime_End = 1.0f;

public:
	ACitizenCage();
	virtual void PossessedBy(AController* NewController) override;
	virtual void PostInitializeComponents() override;
	virtual void BeginPlay() override;
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;
	virtual void Tick(float DeltaTime) override;
	virtual float TakeDamage(float DamageAmount, struct FDamageEvent const & DamageEvent, class AController * EventInstigator, AActor * DamageCauser) override;

	void SetCitizenActive(bool bActive) { m_bActive = bActive;  }
	void SetMovePortal(AMovePortal* pTarget);

	UFUNCTION(BlueprintPure)
		bool GetCageOpen() { return m_bUpdate; }

	UFUNCTION(BlueprintCallable)
		void SetPlayerVisible(bool bVisible);

public:
	FGenericTeamId GetGenericTeamId() const override { return 0; }
	virtual void CharacterMessage(FString sMessage) override;

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "Itf_NotifyMessage")
		void Inter_Notify_Message(FName sMessage);
	virtual void Inter_Notify_Message_Implementation(FName sMessage) override;
};
