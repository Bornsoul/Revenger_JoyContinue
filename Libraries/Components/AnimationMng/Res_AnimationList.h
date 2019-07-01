// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Revenger.h"
#include "UObject/NoExportTypes.h"
#include "Res_AnimationList.generated.h"

/**
 * 
 */
UCLASS(Blueprintable)
class REVENGER_API URes_AnimationList : public UObject
{
	GENERATED_BODY()

private:
	UPROPERTY(EditDefaultsOnly, Category = Animation, Meta = (AllowPrivateAccess = true))
		TMap<FString, class UAnimSequenceBase*> m_pAnimList_Sequence;

	UPROPERTY(EditDefaultsOnly, Category = Animation, Meta = (AllowPrivateAccess = true))
		TMap<FString, class UAnimMontage*> m_pAnimList_Montage;

public:
	TMap<FString, class UAnimSequenceBase*> GetAnimList_Sequence() { return m_pAnimList_Sequence; }
	TMap<FString, class UAnimMontage*> GetAnimList_Montage() { return m_pAnimList_Montage; }
};
