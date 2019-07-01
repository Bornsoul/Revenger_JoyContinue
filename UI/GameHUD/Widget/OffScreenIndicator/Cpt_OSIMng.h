// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Cpt_OSIMng.generated.h"

/**
 * 
 */
UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class REVENGER_API UCpt_OSIMng : public UActorComponent
{
	GENERATED_BODY()
private :
	UPROPERTY()
		TSubclassOf<class UWidget_OSIPin> m_pInst_Widget;

	UPROPERTY()
		TArray<class UWidget_OSIPin*> m_pPinList;

public:
	UCpt_OSIMng();
	virtual void BeginPlay() override;
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	void FindScreenEdgeLocationForWorldLocation(FVector InLocation,  float EdgePercent,
		FVector2D& OutScreenPosition, float& OutRotationAngleDegrees, bool &bIsOnScreen, float& fRot);

	// nIconState : 0 = Àâ¸÷ , 1 = º¸½º
	void AddPin(class AGameCharacter* pActor, int32 nIconState);

	void DestroyPin();
};
