// Fill out your copyright notice in the Description page of Project Settings.

#include "GameCharacter.h"

// Sets default values
AGameCharacter::AGameCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AGameCharacter::BeginPlay()
{
	Super::BeginPlay();
	
}

void AGameCharacter::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	Super::EndPlay(EndPlayReason);

}

// Called every frame
void AGameCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AGameCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void AGameCharacter::SetIgnoreCollision_Hit(bool bIgnore)
{
	m_bIgnoreCollision_Hit = bIgnore;
	if (m_bIgnoreCollision_Hit == true)
	{
		GetCapsuleComponent()->SetCollisionResponseToChannel(ECC_GameTraceChannel1, ECollisionResponse::ECR_Ignore);
	}
	else
	{
		GetCapsuleComponent()->SetCollisionResponseToChannel(ECC_GameTraceChannel1, ECollisionResponse::ECR_Overlap);
	}
}

void AGameCharacter::SetIgnoreCollision_Pawn(bool bIgnore)
{
	m_bIgnoreCollision_Pawn = bIgnore;
	if (m_bIgnoreCollision_Pawn == true)
	{
		GetCapsuleComponent()->SetCollisionResponseToChannel(ECC_Pawn, ECollisionResponse::ECR_Ignore);
	}
	else
	{
		GetCapsuleComponent()->SetCollisionResponseToChannel(ECC_Pawn, ECollisionResponse::ECR_Block);
	}
}

void AGameCharacter::CharacterMessage(FString sMessage)
{

}

void AGameCharacter::SetRagdollPhysics(FVector vImpactPoint, float fPushPower)
{
	bool bInRagdoll = false;
	USkeletalMeshComponent* Mesh3P = GetMesh();

	if (IsPendingKill())
	{
		bInRagdoll = false;
	}
	else if (!Mesh3P || !Mesh3P->GetPhysicsAsset())
	{
		bInRagdoll = false;
	}
	else
	{
		Mesh3P->SetAllBodiesSimulatePhysics(true);
		Mesh3P->SetSimulatePhysics(true);
		Mesh3P->WakeAllRigidBodies();
		Mesh3P->bBlendPhysics = true;

		bInRagdoll = true;
	}

	UCharacterMovementComponent* CharacterComp = Cast<UCharacterMovementComponent>(GetMovementComponent());
	if (CharacterComp)
	{
		CharacterComp->StopMovementImmediately();
		CharacterComp->DisableMovement();
		CharacterComp->SetComponentTickEnabled(false);
	}

	UCapsuleComponent* CapsuleComp = GetCapsuleComponent();
	CapsuleComp->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	CapsuleComp->SetCollisionResponseToAllChannels(ECR_Ignore);
	
	if (Mesh3P)
	{
		Mesh3P->SetCollisionProfileName(TEXT("Ragdoll"));
	}
	SetActorEnableCollision(true);

	FVector vDirection = GetActorLocation() - vImpactPoint;
	vDirection.Normalize();
	Mesh3P->AddImpulseAtLocation(vDirection * fPushPower, vImpactPoint);
}