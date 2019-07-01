// Fill out your copyright notice in the Description page of Project Settings.

#include "Cpt_Commander.h"
#include "Actor/Characters/Player/GBox/GBox.h"
#include "Actor/Characters/Enemy/GC_Enemy.h"

UCpt_Commander::UCpt_Commander()
{
	PrimaryComponentTick.bCanEverTick = true;

}

void UCpt_Commander::BeginPlay()
{
	Super::BeginPlay();

}

void UCpt_Commander::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	Super::EndPlay(EndPlayReason);

}


void UCpt_Commander::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

}

