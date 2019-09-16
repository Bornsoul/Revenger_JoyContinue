// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Revenger.h"
#include "Components/ActorComponent.h"
#include "Cpt_PressKey.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class REVENGER_API UCpt_PressKey : public UActorComponent
{
	GENERATED_BODY()

private:

	UPROPERTY()
		TSubclassOf<class UWidget_PressKeyItem> m_pInst_PressKey;

	UPROPERTY()
		class UWidget_PressKeyItem* m_pPressKeyItem;

public:	
	UCpt_PressKey();
	virtual void BeginPlay() override;
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	UFUNCTION(BlueprintCallable)
		void Tick_IconLocation(FVector vLoc, float fWidth, float fHeight);

};
