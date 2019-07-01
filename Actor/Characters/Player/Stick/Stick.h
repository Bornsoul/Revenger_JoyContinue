// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "AIModule/Classes/GenericTeamAgentInterface.h"
#include "Libraries/Interfaces/Itf_AnimMsgNotify.h"
#include "Libraries/Components/KeyStateMng/Cpt_KeyStateMng.h"
#include "Libraries/Components/MouseMng/Cpt_MouseMng.h"

#include "Revenger.h"
#include "Actor/Characters/Player/GC_Player.h"
#include "Stick.generated.h"

UCLASS()
class REVENGER_API AStick : public AGC_Player, public IItf_AnimMsgNotify, public IGenericTeamAgentInterface
{
	GENERATED_BODY()

private:
	UPROPERTY()
		class UCpt_AnimationMng* m_pAnimationMng;

	UPROPERTY()
		class UAnimInst_Stick* m_pAnimInstance;

	UPROPERTY()
		class AActor* m_pTarget;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = MouseLand, meta = (AllowPrivateAccess = "true"))
		class UCpt_MouseLandMng* m_pMouseLandMng;

private:

	UPROPERTY(EditAnywhere, Category = StickOption)
		float m_fFollowSpeed = 2.0f;

	UPROPERTY(EditAnywhere, Category = StickOption)
		float m_fRotateSpeed = 1.0f;

	UPROPERTY(EditAnywhere, Category = StickOption)
		FVector m_vPos;

	FVector m_vStartLocation;
	FRotator m_rStartRotation;

	bool m_bMouseRot = false;

public:
	FORCEINLINE bool GetMouseRotation() { return m_bMouseRot; }
	FORCEINLINE class UCpt_MouseLandMng* GetMouseMng() { return m_pMouseLandMng; }

public:
	AStick();
	virtual void PossessedBy(AController* NewController) override;
	virtual void PostInitializeComponents() override;
	virtual void BeginPlay() override;
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;
	virtual void Tick(float DeltaTime) override;
	virtual float TakeDamage(float DamageAmount, struct FDamageEvent const & DamageEvent, class AController * EventInstigator, AActor * DamageCauser) override;

public:
	void AnimInst_Tick();
	void Spawn(AActor* pTarget, FVector vPos);
	void SetMouseRotation(bool bRot) { m_bMouseRot = bRot; }

	void Control_Portal(bool bUsePortal);

	void SetStickHidden(bool bVisibility);

public:
	FGenericTeamId GetGenericTeamId() const override { return 0; }
	virtual void CharacterMessage(FString sMessage) override;

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "Itf_NotifyMessage")
		void Inter_Notify_Message(FName sMessage);
	virtual void Inter_Notify_Message_Implementation(FName sMessage) override;
};
