// Fill out your copyright notice in the Description page of Project Settings.

#include "Stick.h"
#include "AnimInst_Stick.h"

#include "Libraries/Components/AnimationMng/Cpt_AnimationMng.h"
#include "Libraries/Components/MouseMng/Cpt_MouseLandMng.h"
#include "Libraries/Components/SoundMng/Cpt_SoundMng.h"
#include "Kismet/KismetMathLibrary.h"


AStick::AStick()
{
	PrimaryActorTick.bCanEverTick = true;
	Tags.Add(FName("Stick"));
	SetGenericTeamId(FGenericTeamId(0));

	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	GetCharacterMovement()->bOrientRotationToMovement = true;
	GetCharacterMovement()->MaxWalkSpeed = 1200.0f;
	GetCharacterMovement()->RotationRate = FRotator(0.f, 800.0f, 0.f);
	GetCharacterMovement()->GravityScale = 5.0f;
	GetCharacterMovement()->MaxAcceleration = 99999.0f;
	
	m_pAnimationMng = CreateDefaultSubobject<UCpt_AnimationMng>(TEXT("AnimMngComponent"));
	m_pAnimationMng->SetAnimList(TEXT("/Game/1_Project_Main/1_Blueprints/Actor/Characters/Player/Stick/BP_AnimList_Stick.BP_AnimList_Stick_C"));

	m_pMouseLandMng = CreateDefaultSubobject<UCpt_MouseLandMng>(TEXT("MouseLandMng"));
	m_pMouseLandMng->SetupAttachment(RootComponent);

	static ConstructorHelpers::FClassFinder<UAnimInstance> Const_AnimInst(TEXT("/Game/1_Project_Main/2_Contents/Actors/Player/Stick/Ani/BP_AnimInst_Stick.BP_AnimInst_Stick_C"));
  	if (Const_AnimInst.Succeeded()) GetMesh()->SetAnimInstanceClass(Const_AnimInst.Class);
}

void AStick::Spawn(AActor* pTarget, FVector vPos)
{
	m_pTarget = pTarget;
	m_vStartLocation = m_pTarget->GetActorLocation();
	m_rStartRotation = m_pTarget->GetActorRotation();
	ULOG(TEXT("Stick is Spawned"));
}

void AStick::PossessedBy(AController * NewController)
{
	Super::PossessedBy(NewController);

}

void AStick::PostInitializeComponents()
{
	Super::PostInitializeComponents();

}

void AStick::BeginPlay()
{
	Super::BeginPlay();

	m_pAnimInstance = Cast<UAnimInst_Stick>(GetMesh()->GetAnimInstance());
	if (m_pAnimInstance == nullptr)	ULOG(TEXT("AnimInstance is NULL"));

}

void AStick::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	Super::EndPlay(EndPlayReason);

}

void AStick::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (m_pTarget == nullptr) return;

	FVector vPos = m_pTarget->GetActorLocation() + m_vPos;	

	m_vStartLocation.X = FMath::Lerp(m_vStartLocation.X, vPos.X, m_fFollowSpeed * DeltaTime);
	m_vStartLocation.Y = FMath::Lerp(m_vStartLocation.Y, vPos.Y, m_fFollowSpeed * DeltaTime);
	m_vStartLocation.Z = FMath::Lerp(m_vStartLocation.Z, vPos.Z, m_fFollowSpeed * DeltaTime);

	if (m_bMouseRot == false)
	{
		FRotator vRot = m_pTarget->GetActorRotation();
		m_rStartRotation = FMath::RInterpTo(m_rStartRotation, vRot, DeltaTime, m_fRotateSpeed);
		m_rStartRotation.Roll = 0.0f;
		m_rStartRotation.Pitch = 0.0f;
		SetActorRotation(m_rStartRotation);

	}
	else
	{
		FVector vMouseLoc = GetMouseMng()->GetMouse_Location();
		vMouseLoc.Z = GetActorLocation().Z;

		FRotator rMouse = UKismetMathLibrary::FindLookAtRotation(GetActorLocation(), vMouseLoc);
		m_rStartRotation = FMath::RInterpTo(m_rStartRotation, rMouse, DeltaTime, m_fRotateSpeed);
		m_rStartRotation.Roll = 0.0f;
		m_rStartRotation.Pitch = 0.0f;
		SetActorRotation(m_rStartRotation);

	}

	SetActorLocation(m_vStartLocation);

	AnimInst_Tick();
}

float AStick::TakeDamage(float DamageAmount, FDamageEvent const & DamageEvent, AController * EventInstigator, AActor * DamageCauser)
{
	float fFinalDamage = Super::TakeDamage(DamageAmount, DamageEvent, EventInstigator, DamageCauser);
	if (m_bLife == false) return 0.0f;

	return fFinalDamage;
}

void AStick::AnimInst_Tick()
{
	if (m_pAnimInstance == nullptr) return;

	m_pAnimInstance->SetStat_Acceleration(GetVelocity().Size());
}

void AStick::CharacterMessage(FString sMessage)
{
}

void AStick::Inter_Notify_Message_Implementation(FName sMessage)
{
	CharacterMessage(sMessage.ToString());
}

void AStick::SetStickHidden(bool bVisibility)
{
	GetMesh()->SetVisibility(bHidden);
}

void AStick::Control_Portal(bool bUsePortal)
{
	if (bUsePortal)
	{
		GetMesh()->SetVisibility(false);
	}
	else
	{
		GetMesh()->SetVisibility(true);
	}
}
