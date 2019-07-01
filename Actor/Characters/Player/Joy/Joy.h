// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "AIModule/Classes/GenericTeamAgentInterface.h"
#include "Libraries/Interfaces/Itf_AnimMsgNotify.h"
#include "Libraries/Components/KeyStateMng/Cpt_KeyStateMng.h"
#include "Libraries/Components/MouseMng/Cpt_MouseMng.h"

#include "Revenger.h"
#include "Actor/Characters/Player/GC_Player.h"
#include "Joy.generated.h"

/**
 * 
 */
UCLASS()
class REVENGER_API AJoy : public AGC_Player, public IItf_AnimMsgNotify, public IGenericTeamAgentInterface
{
	GENERATED_BODY()

private:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
		class UCameraComponent* m_pCamera;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
		class USpringArmComponent* m_pSpringArm;

	UPROPERTY()
		class UCpt_AnimationMng* m_pAnimationMng;

	UPROPERTY()
		class UCpt_KeyStateMng* m_pKeyStateMng;

	UPROPERTY()
		class UCpt_MouseMng* m_pMouseMng;

	UPROPERTY()
		class UAnimInst_Joy* m_pAnimInstance;

public:
	FORCEINLINE class UCpt_AnimationMng* GetAnimationMng() { return m_pAnimationMng; }
	FORCEINLINE class UCameraComponent* GetCamera() { return m_pCamera; }
	FORCEINLINE class USpringArmComponent* GetSpringArm() { return m_pSpringArm; }
	FORCEINLINE class UCpt_KeyStateMng* GetKeyStateMng() { return m_pKeyStateMng; }
	FORCEINLINE class UCpt_MouseMng* GetMouseMng() { return m_pMouseMng; }
	FORCEINLINE class UAnimInst_Joy* GetAnimInstance() { return m_pAnimInstance; }

public:
	AJoy();
	virtual void PossessedBy(AController* NewController) override;
	virtual void PostInitializeComponents() override;
	virtual void BeginPlay() override;
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;
	virtual void Tick(float DeltaTime) override;
	virtual float TakeDamage(float DamageAmount, struct FDamageEvent const & DamageEvent, class AController * EventInstigator, AActor * DamageCauser) override;
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

public:
	void AnimInst_Tick();
	void ControlMovement(FVector2D vKeyInput);

public:
	FGenericTeamId GetGenericTeamId() const override { return 0; }
	virtual void CharacterMessage(FString sMessage) override;

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "Itf_NotifyMessage")
		void Inter_Notify_Message(FName sMessage);
	virtual void Inter_Notify_Message_Implementation(FName sMessage) override;
};
