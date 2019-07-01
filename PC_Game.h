// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "PC_Game.generated.h"

/**
 * 
 */
UCLASS()
class REVENGER_API APC_Game : public APlayerController
{
	GENERATED_BODY()
	
public :
	APC_Game();

	float fTest = 0.0f;
};
