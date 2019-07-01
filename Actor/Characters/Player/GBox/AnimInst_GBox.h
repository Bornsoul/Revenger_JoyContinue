// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "AnimInst_GBox.generated.h"

/**
 * 
 */
UCLASS()
class REVENGER_API UAnimInst_GBox : public UAnimInstance
{
	GENERATED_BODY()
public:
	UAnimInst_GBox();
	virtual void NativeUpdateAnimation(float DeltaSeconds) override;

private:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "AnimationStat", Meta = (AllowPrivateAccess = true))
		float m_fCurrentAcceleration = 0.0f;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "AnimationStat", Meta = (AllowPrivateAccess = true))
		float m_fMovementDirection = 0.0f;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "AnimationStat", Meta = (AllowPrivateAccess = true))
		FRotator m_rHeadRotator;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "AnimationStat", Meta = (AllowPrivateAccess = true))
		FRotator m_rSpineRotator;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "AnimationStat", Meta = (AllowPrivateAccess = true))
		bool m_bMoveDir = false;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "AnimationStat", Meta = (AllowPrivateAccess = true))
		bool m_bFalling = false;

private:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Stat_VariableProperty", Meta = (AllowPrivateAccess = true))
		FVector2D m_vRotRange_Head = FVector2D(-50.0f, 80.0f);

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Stat_VariableProperty", Meta = (AllowPrivateAccess = true))
		FVector2D m_vRotRange_Spine = FVector2D(-50.0f, 80.0f);

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Stat_VariableProperty", Meta = (AllowPrivateAccess = true))
		float m_fRotSpeed_Head = 5.0f;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Stat_VariableProperty", Meta = (AllowPrivateAccess = true))
		float m_fRotSpeed_Spine = 4.0f;

public:
	void SetStat_Acceleration(float fAcceleration) { m_fCurrentAcceleration = fAcceleration; }
	void SetStat_MovementDirection(float fMovementDirection) { m_fMovementDirection = fMovementDirection; }
	void SetStat_HeadRotator(FRotator rRotator) { m_rHeadRotator = rRotator; }
	void SetStat_SpineRotator(FRotator rRotator) { m_rSpineRotator = rRotator; }
	
	void SetStat_Falling(bool bFalling) { m_bFalling = bFalling; }

	void SetStat_MoveDir(bool bMoveDir) { m_bMoveDir = bMoveDir; }
	bool GetStat_MoveDir() { return m_bMoveDir; }

	FVector2D GetRotRange_Head() { return m_vRotRange_Head; }
	FVector2D GetRotRange_Spine() { return m_vRotRange_Spine; }
	float GetRotSpeed_Head() { return m_fRotSpeed_Head; }
	float GetRotSpeed_Spine() { return m_fRotSpeed_Spine; }
};

