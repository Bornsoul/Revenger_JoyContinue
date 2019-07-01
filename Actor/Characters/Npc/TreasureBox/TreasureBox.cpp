// Fill out your copyright notice in the Description page of Project Settings.

#include "TreasureBox.h"

#include "Libraries/Components/AnimationMng/Cpt_AnimationMng.h"
#include "Libraries/Components/SoundMng/Cpt_SoundMng.h"
#include "Kismet/KismetMathLibrary.h"

ATreasureBox::ATreasureBox()
{
	PrimaryActorTick.bCanEverTick = true;
	Tags.Add(FName("Enemy"));
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
	//m_pAnimationMng->SetAnimList(TEXT("/Game/1_Project_Main/1_Blueprints/Actor/Characters/Player/Stick/BP_AnimList_Stick.BP_AnimList_Stick_C"));

}

void ATreasureBox::PossessedBy(AController * NewController)
{
	Super::PossessedBy(NewController);

}

void ATreasureBox::PostInitializeComponents()
{
	Super::PostInitializeComponents();

}

void ATreasureBox::BeginPlay()
{
	Super::BeginPlay();

	SetLife(true);

}

void ATreasureBox::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	Super::EndPlay(EndPlayReason);

}

void ATreasureBox::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

float ATreasureBox::TakeDamage(float DamageAmount, FDamageEvent const & DamageEvent, AController * EventInstigator, AActor * DamageCauser)
{
	float fFinalDamage = Super::TakeDamage(DamageAmount, DamageEvent, EventInstigator, DamageCauser);
	if (m_bLife == false) return 0.0f;

	E_DamageEventClass eDamageEventClass = ULib_DamageEvent::GetDamageEventClass(DamageEvent.GetTypeID());
	if (fFinalDamage > 0.0f)
	{
		if (eDamageEventClass == E_DamageEventClass::E_Hit)
		{
			FDamageEvent_Hit* pBloodDamageEvent = (FDamageEvent_Hit*)&DamageEvent;

			m_fCurrentHp -= fFinalDamage;

			bool bIsDead = m_fCurrentHp <= 0 ? true : false;
			if (bIsDead == true)
			{
				SetLife(false);
				SetRagdollPhysics(pBloodDamageEvent->m_vAttackerLocaction, 8000.0f);
				return fFinalDamage;
			}
		}
	}

	return fFinalDamage;
}

void ATreasureBox::CharacterMessage(FString sMessage)
{
}

void ATreasureBox::Inter_Notify_Message_Implementation(FName sMessage)
{
	CharacterMessage(sMessage.ToString());
}

