// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ArrowComponent.h"
#include "Cpt_PortalArrow.generated.h"

/**
 * 
 */

UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class REVENGER_API UCpt_PortalArrow : public UArrowComponent
{
	GENERATED_BODY()
	
private:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = PortalOption, meta = (AllowPrivateAccess = "true"))
		int32 m_nCurrentPortalNum = 0;

public:
	UCpt_PortalArrow();
	void SetPortalNum(int32 nIndex) { m_nCurrentPortalNum = nIndex; }
	int GetPortalNum() { return m_nCurrentPortalNum; }

};
