// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Revenger.h"
#include "Components/ActorComponent.h"
#include "Cpt_WarningSpace.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class REVENGER_API UCpt_WarningSpace : public UActorComponent
{
	GENERATED_BODY()

public:	
	
private :
	UPROPERTY()
		TMap<FString, TSubclassOf<class AWarningSpace_Root>> m_pList;

public:	
	UCpt_WarningSpace();
	virtual void BeginPlay() override;
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	void Add_WarningSpace(FString sName, FString sPath);

	class AWarningSpace_Root* SpawnSpace_Circle(float fWarningTime, float fAngle, FVector vLocation, FRotator vRotation, FVector vScale);
	class AWarningSpace_Root* SpawnSpace_Dash(float fWarningTime, FVector vLocation, FRotator vRotation, FVector vScale);
};
