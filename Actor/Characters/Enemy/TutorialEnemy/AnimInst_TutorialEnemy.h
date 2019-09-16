// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Revenger.h"
#include "Animation/AnimInstance.h"
#include "AnimInst_TutorialEnemy.generated.h"

/**
 * 
 */
UCLASS()
class REVENGER_API UAnimInst_TutorialEnemy : public UAnimInstance
{
	GENERATED_BODY()
	
private:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "AnimationStat", Meta = (AllowPrivateAccess = true))
		float m_fCurrentAcceleration = 0.0f;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "AnimationStat", Meta = (AllowPrivateAccess = true))
		float m_fMovementDirection = 0.0f;

public:
	void SetStat_Acceleration(float fAcceleration) { m_fCurrentAcceleration = fAcceleration; }
	void SetStat_MovementDirection(float fMovementDirection) { m_fMovementDirection = fMovementDirection; }
		
public:
	UAnimInst_TutorialEnemy();
	virtual void NativeUpdateAnimation(float DeltaSeconds) override;


};
