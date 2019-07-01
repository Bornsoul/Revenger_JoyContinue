// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Revenger.h"
#include "GameFramework/Actor.h"
#include "AutoSetPushGround.generated.h"

UCLASS()
class REVENGER_API AAutoSetPushGround : public AActor
{
	GENERATED_BODY()
private :
	UPROPERTY()
		TSubclassOf<class UCpt_FootPushGround> m_pBP;

public:	
	// Sets default values for this actor's properties
	AAutoSetPushGround();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	//virtual PostEditChangeChainProperty(struct FPropertyChangedEvent& e) override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
