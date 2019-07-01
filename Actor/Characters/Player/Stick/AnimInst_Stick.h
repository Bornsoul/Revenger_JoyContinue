// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Revenger.h"
#include "Animation/AnimInstance.h"
#include "AnimInst_Stick.generated.h"

/**
 * 
 */
UCLASS()
class REVENGER_API UAnimInst_Stick : public UAnimInstance
{
	GENERATED_BODY()

public:
	UAnimInst_Stick();
	virtual void NativeUpdateAnimation(float DeltaSeconds) override;

private:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "AnimationStat", Meta = (AllowPrivateAccess = true))
		float m_fCurrentAcceleration = 0.0f;

public:
	void SetStat_Acceleration(float fAcceleration) { m_fCurrentAcceleration = fAcceleration; }

};