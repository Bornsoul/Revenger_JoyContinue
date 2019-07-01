// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ArrowComponent.h"
#include "BossEnemySpawn_Arrow.generated.h"

/**
 * 
 */
UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class REVENGER_API UBossEnemySpawn_Arrow : public UArrowComponent
{
	GENERATED_BODY()
public :
	UBossEnemySpawn_Arrow();
};
