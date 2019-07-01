// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/StaticMeshComponent.h"
#include "AISpawn_Wall.generated.h"

/**
 * 
 */
UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class REVENGER_API UAISpawn_Wall : public UStaticMeshComponent
{
	GENERATED_BODY()
	
public:
	UAISpawn_Wall();
	
	UFUNCTION(BlueprintCallable)
		void Wall_Spawn();
	UFUNCTION(BlueprintCallable)
		void Wall_Destroy();
};