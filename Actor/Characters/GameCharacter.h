// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Libraries/Interfaces/Itf_Weapon.h"

#include "Revenger.h"
#include "GameFramework/Character.h"
#include "GameCharacter.generated.h"

UCLASS()
class REVENGER_API AGameCharacter : public ACharacter
{
	GENERATED_BODY()

		
public:
	// Sets default values for this character's properties


protected:
	bool m_bLife = false;
	bool m_bIgnoreCollision_Hit = false;
	bool m_bIgnoreCollision_Pawn = false;
	bool m_bRagdoll = false;


public:
	UFUNCTION(BlueprintPure)
		bool GetLife() { return m_bLife; }

	UFUNCTION(BlueprintCallable)
		void SetLife(bool bLife) { m_bLife = bLife; }

	bool GetIgnoreCollision_Hit() { return m_bIgnoreCollision_Hit; }
	void SetIgnoreCollision_Hit(bool bIgnore);

	bool GetIgnoreCollision_Pawn() { return m_bIgnoreCollision_Pawn; }
	void SetIgnoreCollision_Pawn(bool bIgnore);
	
	virtual void CharacterMessage(FString sMessage);

	UFUNCTION(BlueprintCallable)
		virtual void SetRagdollPhysics(FVector vImpactPoint, float fPushPower);

public:	
	AGameCharacter();
	virtual void BeginPlay() override;
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;
	virtual void Tick(float DeltaTime) override;
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

};
