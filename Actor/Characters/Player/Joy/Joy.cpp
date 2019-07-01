// Fill out your copyright notice in the Description page of Project Settings.

#include "Joy.h"
#include "AnimInst_Joy.h"

//#include "State/StateMng_GBox.h"
#include "Libraries/Components/AnimationMng/Cpt_AnimationMng.h"
#include "Libraries/Components/CamShake/Cpt_CamShake.h"
#include "Libraries/Components/SlowMotion/Cpt_SlowMotion.h"
#include "Libraries/Components/MaterialEffect/Cpt_MaterialEffect.h"
#include "Libraries/Components/PostProcessEffect/Cpt_PostProcessEffect.h"
#include "Libraries/Components/ParticleMng/Cpt_ParticleMng.h"
#include "Libraries/Components/SlowMotion/Cpt_SlowMotion.h"
#include "Libraries/Components/SoundMng/Cpt_SoundMng.h"
#include "Kismet/KismetMathLibrary.h"
#include "Components/PostProcessComponent.h"


AJoy::AJoy()
{
	PrimaryActorTick.bCanEverTick = true;
	Tags.Add(FName("Player"));
	SetGenericTeamId(FGenericTeamId(0));

	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	GetCharacterMovement()->bOrientRotationToMovement = true;
	GetCharacterMovement()->MaxWalkSpeed = 800.0f;
	GetCharacterMovement()->RotationRate = FRotator(0.f, 800.0f, 0.f);
	GetCharacterMovement()->GravityScale = 5.0f;
	GetCharacterMovement()->MaxAcceleration = 99999.0f;

	m_pSpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("SprintArm"));
	m_pSpringArm->SetupAttachment(GetMesh(), TEXT("Bone_Body")); // TEXT("Bip001-Spine"));
	m_pSpringArm->bAbsoluteRotation = true;
	m_pSpringArm->TargetArmLength = 1000.f;
	m_pSpringArm->RelativeRotation = FRotator(-45.f, 45.0f, 0.0f);
	m_pSpringArm->bDoCollisionTest = false;
	m_pSpringArm->bEnableCameraLag = true;
	m_pSpringArm->CameraLagSpeed = 10.0f;

	m_pCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	m_pCamera->SetupAttachment(m_pSpringArm, USpringArmComponent::SocketName);
	m_pCamera->bUsePawnControlRotation = false;

	m_pAnimationMng = CreateDefaultSubobject<UCpt_AnimationMng>(TEXT("AnimMngComponent"));
	//m_pAnimationMng->SetAnimList(TEXT("/Game/1_Project_Main/1_Blueprints/Actor/Characters/Player/BP_AnimList_GBox.BP_AnimList_GBox_C"));

	m_pKeyStateMng = CreateDefaultSubobject<UCpt_KeyStateMng>(TEXT("KeyStateMng"));
	m_pMouseMng = CreateDefaultSubobject<UCpt_MouseMng>(TEXT("MouseMng"));

//  	static ConstructorHelpers::FClassFinder<UAnimInstance> Const_AnimInst(TEXT("/Game/1_Project_Main/2_Contents/Actors/TEST/Rabbit/Ani/BP_Anim_Rabbit.BP_Anim_Rabbit_C"));
//  	if (Const_AnimInst.Succeeded()) GetMesh()->SetAnimInstanceClass(Const_AnimInst.Class);
}

void AJoy::PossessedBy(AController* NewController)
{
	Super::PossessedBy(NewController);

}

void AJoy::PostInitializeComponents()
{
	Super::PostInitializeComponents();

}

void AJoy::BeginPlay()
{
	Super::BeginPlay();
	GetController()->SetControlRotation(FRotator::ZeroRotator);

	GetMesh()->SetAllBodiesBelowSimulatePhysics(TEXT("Bone_L_Ear01"), true);
	GetMesh()->SetAllBodiesBelowSimulatePhysics(TEXT("Bone_L_Ear01(mirrored)"), true);
	GetMesh()->SetAllBodiesBelowSimulatePhysics(TEXT("Bone_Head"), true);
	

//  	m_pAnimInstance = Cast<UAnimInst_Joy>(GetMesh()->GetAnimInstance());
//  	if (m_pAnimInstance == nullptr)	ULOG(TEXT("AnimInstance is NULL"));
	
}

void AJoy::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	Super::EndPlay(EndPlayReason);

}

void AJoy::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);


	AnimInst_Tick();
}

void AJoy::AnimInst_Tick()
{
	if (m_pAnimInstance == nullptr) return;
	m_pAnimInstance->SetStat_Acceleration(GetVelocity().Size());
}


float AJoy::TakeDamage(float DamageAmount, struct FDamageEvent const & DamageEvent, class AController * EventInstigator, AActor * DamageCauser)
{
	float fFinalDamage = Super::TakeDamage(DamageAmount, DamageEvent, EventInstigator, DamageCauser);


	return fFinalDamage;
}

void AJoy::SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAxis("MoveForward", m_pKeyStateMng, &UCpt_KeyStateMng::KB_Forward);
	PlayerInputComponent->BindAxis("MoveRight", m_pKeyStateMng, &UCpt_KeyStateMng::KB_Right);

}

void AJoy::CharacterMessage(FString sMessage)
{
	Super::CharacterMessage(sMessage);
	//if (m_pStateMng != nullptr) m_pStateMng->StateMessage(sMessage);
}

void AJoy::Inter_Notify_Message_Implementation(FName sMessage)
{
	CharacterMessage(sMessage.ToString());
}

void AJoy::ControlMovement(FVector2D vKeyInput)
{
	FVector vKey3D = FVector(vKeyInput.X, vKeyInput.Y, 0.0f);
	FRotator rRota_Control = GetControlRotation();
	FRotator rRota_Control_Direction = FRotator(0.0f, rRota_Control.Yaw + 45.0f, 0.0f);
	FVector vContorl_ForwardVector = UKismetMathLibrary::GetForwardVector(rRota_Control_Direction);
	FVector vControl_RightVector = UKismetMathLibrary::GetRightVector(rRota_Control_Direction);

	AddMovementInput(vContorl_ForwardVector, vKeyInput.X);
	AddMovementInput(vControl_RightVector, vKeyInput.Y);
}
