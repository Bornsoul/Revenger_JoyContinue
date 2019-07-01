// Fill out your copyright notice in the Description page of Project Settings.

#include "Citizen.h"
#include "AnimInst_Citizen.h"
#include "AIC_Citizen.h"
#include "Actor/Characters/Player/GBox/GBox.h"

#include "Components/BoxComponent.h"
#include "Libraries/Components/AnimationMng/Cpt_AnimationMng.h"
#include "Libraries/Components/SoundMng/Cpt_SoundMng.h"
#include "Kismet/KismetMathLibrary.h"

ACitizen::ACitizen()
{
	PrimaryActorTick.bCanEverTick = true;
	Tags.Add(FName("NPC"));
	SetGenericTeamId(FGenericTeamId(0));

	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	GetCharacterMovement()->bOrientRotationToMovement = true;
	GetCharacterMovement()->MaxWalkSpeed = 800.0f;
	GetCharacterMovement()->RotationRate = FRotator(0.f, 800.0f, 0.f);
	GetCharacterMovement()->GravityScale = 5.0f;
	GetCharacterMovement()->MaxAcceleration = 99999.0f;
	
	m_pAnimationMng = CreateDefaultSubobject<UCpt_AnimationMng>(TEXT("AnimMngComponent"));
	m_pAnimationMng->SetAnimList(TEXT("/Game/1_Project_Main/1_Blueprints/Actor/Characters/NPC/Citizen/Bp_AnimList_Citizen.Bp_AnimList_Citizen_C"));

	m_pKeyStateMng = CreateDefaultSubobject<UCpt_KeyStateMng>(TEXT("KeyStateMng"));

	static ConstructorHelpers::FClassFinder<UAnimInstance> Const_AnimInst(TEXT("/Game/1_Project_Main/2_Contents/Actors/NPC/Citizens/Animation/BP_AnimInst_Citizen.BP_AnimInst_Citizen_C"));
	if (Const_AnimInst.Succeeded()) GetMesh()->SetAnimInstanceClass(Const_AnimInst.Class);

	static ConstructorHelpers::FClassFinder<AAIC_Citizen> Const_AIC(TEXT("/Game/1_Project_Main/1_Blueprints/Actor/Characters/NPC/Citizen/BP_AIC_Citizen.BP_AIC_Citizen_C"));
	if (Const_AIC.Succeeded()) AIControllerClass = Const_AIC.Class;
}

void ACitizen::PossessedBy(AController * NewController)
{
	Super::PossessedBy(NewController);

}

void ACitizen::PostInitializeComponents()
{
	Super::PostInitializeComponents();

}

void ACitizen::BeginPlay()
{
	Super::BeginPlay();

	m_pAnimInstance = Cast<UAnimInst_Citizen>(GetMesh()->GetAnimInstance());
	if (m_pAnimInstance == nullptr)
	{
		ULOG(TEXT("AnimInstance is Nullptr"));
		return;
	}

	m_pAIController = Cast<AAIC_Citizen>(GetController());
	if (m_pAIController != nullptr)
	{
		m_pAIController->InitAI();
	}
	else
	{

		ULOG(TEXT("AIController is nullptr"));
		return;
	}
}

void ACitizen::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	Super::EndPlay(EndPlayReason);

	m_pPlayer = nullptr;
}

void ACitizen::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	AnimInst_Tick();

	if (m_bActive == false) return;
	if (m_bFreeMotionEnd == false) return;

	AActor* pTarget = m_pAIController->DetectInPerception();
	if (pTarget != nullptr)
	{
		if (m_bHappyMotion == false)
		{
			float fDist = FVector::Distance(GetActorLocation(), pTarget->GetActorLocation());
			if (fDist <= m_fHappyRadius)
			{
				FRotator pLookRotation = UKismetMathLibrary::FindLookAtRotation(GetActorLocation(), pTarget->GetActorLocation());
				pLookRotation.Pitch = 0.0f;
				pLookRotation.Roll = 0.0f;
				FRotator pInterp = UKismetMathLibrary::RInterpTo(GetActorRotation(), pLookRotation, DeltaTime, m_fInterpSpeed);
				SetActorRotation(pInterp);


				if (m_pKeyStateMng->GetKeyIsJustRelease(EKeys::F) == true)
				{
					//ULOG(TEXT("Happy"));
					m_bHappyMotion = true;
					m_pAnimationMng->PlayAnimationSequnceBase("Happy", "DefaultSlot");
					return;
				}
			}
		}
	}

}

void ACitizen::AnimInst_Tick()
{
	if (m_pAnimInstance == nullptr) return;

	m_pAnimInstance->SetStat_Acceleration(GetVelocity().Size());
}

float ACitizen::TakeDamage(float DamageAmount, FDamageEvent const & DamageEvent, AController * EventInstigator, AActor * DamageCauser)
{
	float fFinalDamage = Super::TakeDamage(DamageAmount, DamageEvent, EventInstigator, DamageCauser);
	if (m_bLife == false) return 0.0f;

	return fFinalDamage;
}

void ACitizen::CharacterMessage(FString sMessage)
{
	if (sMessage == "MotionEnd")
	{
		m_bHappyMotion = false;
		m_pAnimationMng->StopAnimation_SequnceBaseSlot("Happy", 0.2f);
	}	 
	else if (sMessage == "Happy")
	{
		m_bState_Happy = true;
	}
	else if (sMessage == "FreeEnd")
	{
		m_bFreeMotionEnd = true;
		m_bHappyMotion = true;
		m_pAnimationMng->PlayAnimationSequnceBase("Happy", "DefaultSlot");
		return;
	}
}

void ACitizen::Inter_Notify_Message_Implementation(FName sMessage)
{
	CharacterMessage(sMessage.ToString());
}

void ACitizen::Control_Free()
{	
	m_pAnimationMng->PlayAnimationSequnceBase("Free", "DefaultSlot");
}