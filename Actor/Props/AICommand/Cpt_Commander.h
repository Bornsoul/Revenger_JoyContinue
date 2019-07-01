// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Revenger.h"
#include "Components/ActorComponent.h"
#include "Cpt_Commander.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class REVENGER_API UCpt_Commander : public UActorComponent
{
	GENERATED_BODY()

private:


public:	
	UCpt_Commander();

	virtual void BeginPlay() override;
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

		
};
