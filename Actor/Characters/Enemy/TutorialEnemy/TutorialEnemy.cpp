// Fill out your copyright notice in the Description page of Project Settings.

#include "TutorialEnemy.h"
#include "AnimInst_TutorialEnemy.h"
#include "Actor/Characters/Player/GBox/GBox.h"
#include "State/StateMng_TutorialEnemy.h"

#include "Libraries/Components/SoundMng/Cpt_SoundMng.h"
#include "Libraries/Components/ParticleMng/Cpt_ParticleMng.h"
#include "Libraries/Components/MaterialEffect/Cpt_MaterialEffect.h"
#include "Libraries/Components/CamShake/Cpt_CamShake.h"
#include "Libraries/Components/AnimationMng/Cpt_AnimationMng.h"
#include "Kismet/KismetMathLibrary.h"

ATutorialEnemy::ATutorialEnemy()
{
	PrimaryActorTick.bCanEverTick = true;
	Tags.Add(FName("Enemy"));
	Tags.Add(FName("Tutorial"));
	SetGenericTeamId(FGenericTeamId(1));

	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	GetCharacterMovement()->bOrientRotationToMovement = true;
	GetCharacterMovement()->MaxWalkSpeed = 600.0f;
	GetCharacterMovement()->RotationRate = FRotator(0.0f, 540.0f, 0.0f);

	m_pAnimationMng = CreateDefaultSubobject<UCpt_AnimationMng>(TEXT("AnimMngComponent"));
	m_pAnimationMng->SetAnimList(TEXT("/Game/1_Project_Main/1_Blueprints/Actor/Characters/Enemy/TutorialEnemy/BP_TutoEnemy_AnimList.BP_TutoEnemy_AnimList_C"));

	m_pMaterialEffect = CreateDefaultSubobject<UCpt_MaterialEffect>(TEXT("MaterialEffect"));

	m_pParticleMng = CreateDefaultSubobject<UCpt_ParticleMng>(TEXT("ParticleMng"));
	m_pParticleMng->AddParticleInstance(TEXT("Hit"), TEXT("ParticleSystem'/Game/1_Project_Main/2_Contents/Effects/HitEffect/V_HitImpact.V_HitImpact'"));
	m_pParticleMng->AddParticleInstance(TEXT("EyeLight"), TEXT("ParticleSystem'/Game/1_Project_Main/2_Contents/Effects/EyeLight/V_EyeLight.V_EyeLight'"));
	m_pParticleMng->AddParticleInstance(TEXT("GroundHit"), TEXT("ParticleSystem'/Game/2_Contents/VFX/Mobile_Fantasy_FX/ParticleSystems/P_Thunder_Strike.P_Thunder_Strike'"));
	m_pParticleMng->AddParticleInstance(TEXT("Smoke"), TEXT("ParticleSystem'/Game/0_Assets/MarketPlace/VFXS/VFX_Toolkit_V1/ParticleSystems/356Days/Par_Smoke.Par_Smoke'"));
	m_pParticleMng->AddParticleInstance(TEXT("Disint"), TEXT("ParticleSystem'/Game/1_Project_Main/2_Contents/Effects/V_Disint.V_Disint'"));

	m_pSoundMng = CreateDefaultSubobject<UCpt_SoundMng>(TEXT("SoundMng"));
	m_pSoundMng->Set_SoundList(TEXT("/Game/1_Project_Main/1_Blueprints/Actor/Characters/Enemy/TutorialEnemy/BP_SoundList_TutoEnemy.BP_SoundList_TutoEnemy_C"));

	static ConstructorHelpers::FClassFinder<UAnimInstance> Const_AnimInst(TEXT("/Game/1_Project_Main/2_Contents/Actors/Enemy/TutorialEnemy/BP_AnimInst_TotoEnemy.BP_AnimInst_TotoEnemy_C"));
	if (Const_AnimInst.Succeeded()) GetMesh()->SetAnimInstanceClass(Const_AnimInst.Class);

}

void ATutorialEnemy::PossessedBy(AController* NewController)
{
	Super::PossessedBy(NewController);

}

void ATutorialEnemy::PostInitializeComponents()
{
	Super::PostInitializeComponents();

}

void ATutorialEnemy::BeginPlay()
{
	Super::BeginPlay();

	GetController()->SetControlRotation(FRotator::ZeroRotator);
	SetStartLoc(GetActorLocation());

	m_pMaterialEffect->Init(GetMesh());
	m_pMaterialEffect->AddEffect(E_MaterialEffect::E_Hit2);
	m_pMaterialEffect->AddEffect(E_MaterialEffect::E_Disint);

	m_pAnimInstance = Cast<UAnimInst_TutorialEnemy>(GetMesh()->GetAnimInstance());
	if (m_pAnimInstance == nullptr)
	{
		ULOG(TEXT("AnimInstance is Nullptr"));
		return;
	}

	m_pStateMng = NewObject<UStateMng_TutorialEnemy>();
	if (m_pStateMng != nullptr)
	{
		m_pStateMng->Init(this);
		m_pStateMng->ChangeState(static_cast<int32>(E_State_TutoEnemy::E_Spawn));
	}
	else
	{
		ULOG(TEXT("StateMng is nullptr"));
		return;
	}


	SetLife(true);
}

void ATutorialEnemy::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	Super::EndPlay(EndPlayReason);

	if (m_pStateMng != nullptr)
	{
		if (m_pStateMng->IsValidLowLevel())
		{
			m_pStateMng->Destroy();
			m_pStateMng = nullptr;
		}
	}
}

void ATutorialEnemy::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (m_pStateMng != nullptr)
	{
		m_pStateMng->Update(DeltaTime);
	}

	if (m_pAnimationMng != nullptr)
	{
		m_pAnimInstance->SetStat_Acceleration(GetVelocity().Size());
	}

}

float ATutorialEnemy::TakeDamage(float DamageAmount, struct FDamageEvent const & DamageEvent, class AController * EventInstigator, AActor * DamageCauser)
{
	float fDamage = Super::TakeDamage(DamageAmount, DamageEvent, EventInstigator, DamageCauser);

	if (GetLife() == false)
	{
		return 0.0f;
	}

	E_DamageEventClass eDamageEventClass = ULib_DamageEvent::GetDamageEventClass(DamageEvent.GetTypeID());
	if (fDamage > 0.0f)
	{
		if (eDamageEventClass == E_DamageEventClass::E_Hit)
		{
			FDamageEvent_Hit* pBloodDamageEvent = (FDamageEvent_Hit*)&DamageEvent;

			m_fCurrentHp -= fDamage;
			bool bIsDead = m_fCurrentHp <= 0 ? true : false;
			if (bIsDead == true)
			{
				Tags.Empty();
				Tags.Add("EnemyDie");

				SetLife(false);

				UState_TutoEnemy_Die* pState = Cast<UState_TutoEnemy_Die>(m_pStateMng->GetStateClassRef(static_cast<int32>(E_State_TutoEnemy::E_Die)));
				if (pState != nullptr)
				{
					pState->SetHitDirection(pBloodDamageEvent->m_vAttackerLocaction);
					m_pStateMng->ChangeState(static_cast<int32>(E_State_TutoEnemy::E_Die));
					return fDamage;
				}
			}

			UState_TutoEnemy_Hit* pState = Cast<UState_TutoEnemy_Hit>(m_pStateMng->GetStateClassRef(static_cast<int32>(E_State_TutoEnemy::E_Hit)));
			if (pState != nullptr)
			{
				pState->SetHitDirection(pBloodDamageEvent->m_vAttackerLocaction);
				m_pStateMng->ChangeState(static_cast<int32>(E_State_TutoEnemy::E_Hit));
				return fDamage;
			}
		}
	}

	return fDamage;
}

void ATutorialEnemy::CharacterMessage(FString sMessage)
{
	Super::CharacterMessage(sMessage);

	if (m_pStateMng != nullptr)
	{
		m_pStateMng->StateMessage(sMessage);
	}
}

void ATutorialEnemy::Inter_Notify_Message_Implementation(FName sMessage)
{
	CharacterMessage(sMessage.ToString());
}

