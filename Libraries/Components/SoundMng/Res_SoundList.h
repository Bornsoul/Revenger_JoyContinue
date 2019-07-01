// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Res_SoundList.generated.h"

/**
 * 
 */
UCLASS(Blueprintable)
class REVENGER_API URes_SoundList : public UObject
{
	GENERATED_BODY()

private:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Sound, Meta = (AllowPrivateAccess = true))
		TMap<FString, class USoundCue*> m_pSoundList;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Sound, Meta = (AllowPrivateAccess = true))
		TMap<FString, class USoundAttenuation*> m_pAttenuationList;

public:
	TMap<FString, class USoundCue*> GetSoundList() { return m_pSoundList; }
	TMap<FString, class USoundAttenuation*> GetAttenuationList() { return m_pAttenuationList; }
};
