// Fill out your copyright notice in the Description page of Project Settings.

#include "AISpawn_Wall.h"
#include "Kismet/KismetMathLibrary.h"

UAISpawn_Wall::UAISpawn_Wall()
{
	
	static ConstructorHelpers::FObjectFinder<UStaticMesh> Const_Mesh(TEXT("/Game/2_Project_Level/3_Levels/Testmap/box.box"));
	
	if (Const_Mesh.Succeeded())
	{
		SetStaticMesh(Const_Mesh.Object);
		SetRelativeLocation(FVector(0.0f, 0.0f, 150.0f));
		SetRelativeScale3D(FVector(0.3f, 8.0f, 2.0f));
	}

}

void UAISpawn_Wall::Wall_Spawn()
{
	SetVisibility(true, true);
	SetCollisionProfileName("BlockAll");

}

void UAISpawn_Wall::Wall_Destroy()
{
	SetVisibility(false, false);
	SetCollisionProfileName("NoCollision");
}