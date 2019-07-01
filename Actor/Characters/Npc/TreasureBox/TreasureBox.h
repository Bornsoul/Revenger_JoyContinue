// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "AIModule/Classes/GenericTeamAgentInterface.h"
#include "Libraries/Interfaces/Itf_AnimMsgNotify.h"

#include "Revenger.h"
#include "Actor/Characters/Npc/GC_Npc.h"
#include "TreasureBox.generated.h"

UCLASS()
class REVENGER_API ATreasureBox : public AGC_Npc, public IItf_AnimMsgNotify, public IGenericTeamAgentInterface
{
	GENERATED_BODY()
	
private:
	UPROPERTY()
		class UCpt_AnimationMng* m_pAnimationMng;

public:
	float m_fCurrentHp = 2.0f;

public:
	ATreasureBox();
	virtual void PossessedBy(AController* NewController) override;
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
};
