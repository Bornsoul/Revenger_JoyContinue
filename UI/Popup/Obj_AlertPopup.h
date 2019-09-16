// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Revenger.h"
#include "UObject/NoExportTypes.h"
#include "Obj_AlertPopup.generated.h"

/**
 * 
 */
UCLASS()
class REVENGER_API UObj_AlertPopup : public UObject
{
	GENERATED_BODY()

private:

	UPROPERTY()
		TSubclassOf<class UWidget_AlertPopup> m_pInst_Alert;


	/*UPROPERTY()
		class UWidget_AlertPopup* m_pAlertPop;*/

public:
	UObj_AlertPopup();
	
	UFUNCTION(BlueprintCallable)
		class UWidget_AlertPopup* CreateAlert(const FString sText, const float fDestroyTime = 5.0f);
};
