// Fill out your copyright notice in the Description page of Project Settings.

#include "CitizenCage.h"
#include "AnimInst_CitizenCage.h"
#include "Actor/Characters/Npc/Citizen/Citizen.h"
#include "Actor/Props/MovePortal/MovePortal.h"
#include "Actor/Characters/Player/GBox/GBox.h"

#include "Libraries/Components/AnimationMng/Cpt_AnimationMng.h"
#include "Libraries/Components/SoundMng/Cpt_SoundMng.h"
#include "Kismet/KismetMathLibrary.h"

ACitizenCage::ACitizenCage()
{
	PrimaryActorTick.bCanEverTick = true;
	Tags.Add(FName("Enemy"));
	SetGenericTeamId(FGenericTeamId(1));

	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	GetCharacterMovement()->bOrientRotationToMovement = true;
	GetCharacterMovement()->MaxWalkSpeed = 1200.0f;
	GetCharacterMovement()->RotationRate = FRotator(0.f, 800.0f, 0.f);
	GetCharacterMovement()->GravityScale = 5.0f;
	GetCharacterMovement()->MaxAcceleration = 99999.0f;

	m_pAnimationMng = CreateDefaultSubobject<UCpt_AnimationMng>(TEXT("AnimMngComponent"));
	m_pAnimationMng->SetAnimList(TEXT("/Game/1_Project_Main/1_Blueprints/Actor/Characters/NPC/CitizenCage/Bp_AnimList_CitizenCage.Bp_AnimList_CitizenCage_C"));

	static ConstructorHelpers::FClassFinder<UAnimInstance> Const_AnimInst(TEXT("/Game/1_Project_Main/2_Contents/Actors/NPC/CitizenCage/Animation/BP_AnimInst_Cage.BP_AnimInst_Cage_C"));
	if (Const_AnimInst.Succeeded()) GetMesh()->SetAnimInstanceClass(Const_AnimInst.Class);

}

void ACitizenCage::PossessedBy(AController * NewController)
{
	Super::PossessedBy(NewController);

}

void ACitizenCage::PostInitializeComponents()
{
	Super::PostInitializeComponents();

}

void ACitizenCage::BeginPlay()
{
	Super::BeginPlay();

	m_pAnimInstance = Cast<UAnimInst_CitizenCage>(GetMesh()->GetAnimInstance());
	if (m_pAnimInstance == nullptr)
	{
		ULOG(TEXT("AnimInstance is Nullptr"));
		return;
	}
	m_bMotionEnd = false;


	m_pPlayer = Cast<AGBox>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));
	if (m_pPlayer == nullptr)
	{
		ULOG(TEXT("Cage Player is Nullptr"));
		return;
	}

	
	SetLife(true);
}

void ACitizenCage::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	Super::EndPlay(EndPlayReason);

}

void ACitizenCage::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (m_bActive == false) return;

	if (m_bUpdate)
	{
		m_fMotionTime_Cur += DeltaTime;
		if (m_fMotionTime_Cur >= m_fMotionTime_End)
		{
			m_fMotionTime_Cur = 0.0f;
			if (m_pCitizen != nullptr)
			{
				m_pAnimationMng->PlayAnimationMontage(("MT_Free"), 1.0f, TEXT("Start"));

				m_bUpdate = false;
				return;
			}
		}		
	}
}

float ACitizenCage::TakeDamage(float DamageAmount, FDamageEvent const & DamageEvent, AController * EventInstigator, AActor * DamageCauser)
{
	float fFinalDamage = Super::TakeDamage(DamageAmount, DamageEvent, EventInstigator, DamageCauser);
	if (m_bLife == false) return 0.0f;
	if (m_bActive == false) return 0.0f;

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
				m_bUpdate = true;
				return fFinalDamage;
			}
		}
	}

	return fFinalDamage;
}

void ACitizenCage::SetMovePortal(AMovePortal* pTarget)
{
	m_pPortal = pTarget;
}

void ACitizenCage::CharacterMessage(FString sMessage)
{
	if (sMessage == "MotionEnd")
	{
		m_bMotionEnd = true;
		if (m_pCitizen != nullptr)
		{
			m_pCitizen->Control_Free();
		}
		//m_pAnimationMng->StopAnimation_Montage("MT_Free");
		ULOG(TEXT("CitizenCage MotionEnd"));
	}
	else if (sMessage == "CitizenActive")
	{
		if (m_pPortal != nullptr)
		{
			m_pPortal->SetActorHiddenInGame(false);
			m_pPortal->SpawnPortal();
		}
		if (m_pCitizen != nullptr)
		{
			m_pCitizen->SetUpdateActive(true);
		}
	}	
}

void ACitizenCage::Inter_Notify_Message_Implementation(FName sMessage)
{
	CharacterMessage(sMessage.ToString());
}

void ACitizenCage::SetPlayerVisible(bool bVisible)
{
	if (m_pPlayer == nullptr) return;

	m_pPlayer->SetMovement(bHidden);
	m_pPlayer->GetMesh()->SetVisibility(bHidden);
}