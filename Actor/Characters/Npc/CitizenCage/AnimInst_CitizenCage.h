// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "AnimInst_CitizenCage.generated.h"

/**
 * 
 */
UCLASS()
class REVENGER_API UAnimInst_CitizenCage : public UAnimInstance
{
	GENERATED_BODY()
	
public:
	UAnimInst_CitizenCage();
	virtual void NativeUpdateAnimation(float DeltaSeconds) override;

};