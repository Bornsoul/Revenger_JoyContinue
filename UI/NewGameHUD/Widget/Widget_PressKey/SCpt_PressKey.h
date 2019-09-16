// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Revenger.h"
#include "Components/SceneComponent.h"
#include "SCpt_PressKey.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class REVENGER_API USCpt_PressKey : public USceneComponent
{
	GENERATED_BODY()

private:

	UPROPERTY()
		class UWCpt_PressKey* m_pWidgetComp_PressKey;

	UPROPERTY(EditAnywhere)
		FVector m_vLocation;

public:	
	USCpt_PressKey();

	virtual void BeginPlay() override;	
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

};
