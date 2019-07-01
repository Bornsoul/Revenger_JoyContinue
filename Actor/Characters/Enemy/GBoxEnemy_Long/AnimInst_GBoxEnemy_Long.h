// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "AnimInst_GBoxEnemy_Long.generated.h"

/**
 * 
 */
UCLASS()
class REVENGER_API UAnimInst_GBoxEnemy_Long : public UAnimInstance
{
	GENERATED_BODY()

public:
	UAnimInst_GBoxEnemy_Long();
	virtual void NativeUpdateAnimation(float DeltaSeconds) override;

private:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "AnimationStat", Meta = (AllowPrivateAccess = true))
		float m_fCurrentAcceleration = 0.0f;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "AnimationStat", Meta = (AllowPrivateAccess = true))
		float m_fMovementDirection = 0.0f;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "AnimationStat", Meta = (AllowPrivateAccess = true))
		bool m_bCombat = false;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "AnimationStat", Meta = (AllowPrivateAccess = true))
		FRotator m_rHeadRotator;

public:
	void SetStat_Acceleration(float fAcceleration) { m_fCurrentAcceleration = fAcceleration; }
	void SetStat_MovementDirection(float fMovementDirection) { m_fMovementDirection = fMovementDirection; }
	void SetStat_Combat(bool bCombat) { m_bCombat = bCombat; }
	void SetStat_HeadRotator(FRotator rHeadRotator) { m_rHeadRotator = rHeadRotator; }

};

