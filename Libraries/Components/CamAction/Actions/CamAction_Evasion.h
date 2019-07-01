// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Libraries/Components/CamAction/CamAction_Root.h"
#include "CamAction_Evasion.generated.h"

/**
 * 
 */
UCLASS()
class REVENGER_API UCamAction_Evasion : public UCamAction_Root
{
	GENERATED_BODY()

private:
	FVector	 m_vOriginCamPos;
	FRotator m_rOriginCamRota;


	FVector m_vAimPos;
	FRotator m_rAimRota;

	float m_fOrigin_Length;
	float m_fResult_Length;

	bool m_bAimComp = false;

	float m_fInterpSpeed = 12.0f;

	float m_fAgoTime = 0.03f;
	float m_fCurrTime = 0.0f;

public:
	virtual void ActiveAction() override;
	virtual void DeActiveAction() override;
	virtual void Tick_Action(float fDeltaTime) override;
};
