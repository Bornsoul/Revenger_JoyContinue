// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/WidgetComponent.h"
#include "WCpt_PressKey.generated.h"

/**
 * 
 */
UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class REVENGER_API UWCpt_PressKey : public UWidgetComponent
{
	GENERATED_BODY()
	
private:
	UPROPERTY()
		TSubclassOf<class UWidget_PressKeyItem> m_pInst_PressKey;

	UPROPERTY()
		class UWidget_PressKeyItem* m_pPressKeyItem;

public:
	UWCpt_PressKey();
	virtual void BeginPlay() override;
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;


};
