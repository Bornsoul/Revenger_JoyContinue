// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Libraries/Components/GhostTrail/GhostTrail_Root.h"
#include "GT_AlphaDown.generated.h"

/**
 * 
 */
UCLASS()
class REVENGER_API AGT_AlphaDown : public AGhostTrail_Root
{
	GENERATED_BODY()

private:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stat Value", Meta = (AllowPrivateAccess = true))
		float m_fStart_Opcaity = 2.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stat Value", Meta = (AllowPrivateAccess = true))
		float m_fInterp_Opcaity = 5.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stat Value", Meta = (AllowPrivateAccess = true))
		FString m_sMaterialValueStr_Opacity = "Opacity";

private:
	float m_fOpacity = 1.0f;

public:
	AGT_AlphaDown();

	virtual void Tick(float DeltaTime) override;
	virtual void Spawn(class USkeletalMeshComponent* pMesh) override;
};
