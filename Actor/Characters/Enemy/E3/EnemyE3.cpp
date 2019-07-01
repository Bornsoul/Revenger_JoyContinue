// Fill out your copyright notice in the Description page of Project Settings.

#include "EnemyE3.h"
#include "Libraries/Components/AnimationMng/Cpt_AnimationMng.h"
#include "Kismet/KismetMathLibrary.h"
#include "Actor/Characters/Player/GBox/GBox.h"

#include "Libraries/Components/MaterialEffect/Cpt_MaterialEffect.h"
#include "Libraries/Components/ParticleMng/Cpt_ParticleMng.h"
#include "Libraries/Components/SoundMng/Cpt_SoundMng.h"
#include "Libraries/Components/CamShake/Cpt_CamShake.h"
#include "Actor/Props/FootPush/Cpt_FootPushLine.h"

#include "UI/Enemy/HpSystem/Cpt_EnemyHp.h"

#include "AnimInst_EnemyE3.h"
#include "State/StateMng_EnemyE3.h"

#include "AIC_EnemyE3.h"
#include "Libraries/Components/WarningSpace/Cpt_WarningSpace.h"

AEnemyE3::AEnemyE3()
{
	PrimaryActorTick.bCanEverTick = true;
	Tags.Add(FName("Enemy"));
	Tags.Add(FName("Enemy_Close"));
	SetGenericTeamId(FGenericTeamId(1));

	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	GetCharacterMovement()->bOrientRotationToMovement = true;
	GetCharacterMovement()->MaxWalkSpeed = 600.0f;
	GetCharacterMovement()->RotationRate = FRotator(0.0f, 540.0f, 0.0f);

	m_pAnimationMng = CreateDefaultSubobject<UCpt_AnimationMng>(TEXT("AnimMngComponent"));
	m_pAnimationMng->SetAnimList(TEXT("/Game/1_Project_Main/1_Blueprints/Actor/Characters/Enemy/EnemyE3/BP_AnimList_E3.BP_AnimList_E3_C"));

	static ConstructorHelpers::FClassFinder<UAnimInstance> Const_AnimInst(TEXT("/Game/1_Project_Main/2_Contents/Actors/Enemy/E3/Animation/BP_Anim_E3.BP_Anim_E3_C"));
	if (Const_AnimInst.Succeeded()) GetMesh()->SetAnimInstanceClass(Const_AnimInst.Class);

	static ConstructorHelpers::FClassFinder<AAIC_EnemyE3> Const_AIC(TEXT("/Game/1_Project_Main/1_Blueprints/Actor/Characters/Enemy/EnemyE3/BP_AIC_EnemyE3.BP_AIC_EnemyE3_C"));
	if (Const_AIC.Succeeded()) AIControllerClass = Const_AIC.Class;

	m_pMaterialEffect = CreateDefaultSubobject<UCpt_MaterialEffect>(TEXT("MaterialEffect"));
	
	m_pParticleMng = CreateDefaultSubobject<UCpt_ParticleMng>(TEXT("ParticleMng"));
	m_pParticleMng->AddParticleInstance(TEXT("Hit"), TEXT("ParticleSystem'/Game/1_Project_Main/2_Contents/Effects/HitEffect/V_HitImpact.V_HitImpact'"));
	m_pParticleMng->AddParticleInstance(TEXT("EyeLight"), TEXT("ParticleSystem'/Game/1_Project_Main/2_Contents/Effects/EyeLight/V_EyeLight.V_EyeLight'"));
	m_pParticleMng->AddParticleInstance(TEXT("GroundHit"), TEXT("ParticleSystem'/Game/2_Contents/VFX/Mobile_Fantasy_FX/ParticleSystems/P_Thunder_Strike.P_Thunder_Strike'"));
	m_pParticleMng->AddParticleInstance(TEXT("Smoke"), TEXT("ParticleSystem'/Game/0_Assets/MarketPlace/VFXS/VFX_Toolkit_V1/ParticleSystems/356Days/Par_Smoke.Par_Smoke'"));
	m_pParticleMng->AddParticleInstance(TEXT("Disint"), TEXT("ParticleSystem'/Game/1_Project_Main/2_Contents/Effects/V_Disint.V_Disint'"));


	m_pSoundMng = CreateDefaultSubobject<UCpt_SoundMng>(TEXT("SoundMng"));
	m_pSoundMng->Set_SoundList(TEXT("/Game/1_Project_Main/1_Blueprints/Actor/Characters/Enemy/EnemyE3/BP_SoundList_E3.BP_SoundList_E3_C"));
	//m_pHp = CreateDefaultSubobject<USC_WidgetEnemyHp>(TEXT("EnemyHP"));	

	m_pFootPushLine = CreateDefaultSubobject<UCpt_FootPushLine>(TEXT("FootPushLine"));
	m_pFootPushLine->SetSKMesh(this);
	m_pFootPushLine->AddBone(TEXT("Bone_Body"));

	m_pHp = CreateDefaultSubobject<UCpt_EnemyHp>(TEXT("EnemyHp"));

	m_pWarningSpace = CreateDefaultSubobject<UCpt_WarningSpace>(TEXT("WarningSpace"));
}


void AEnemyE3::PossessedBy(AController* NewController)
{
	Super::PossessedBy(NewController);

}

void AEnemyE3::PostInitializeComponents()
{
	Super::PostInitializeComponents();

}

void AEnemyE3::BeginPlay()
{
	Super::BeginPlay();

	GetController()->SetControlRotation(FRotator::ZeroRotator);
	SetStartLoc(GetActorLocation());

	if (m_pHp != nullptr)
	{
		m_pHp->AddHeart(this, static_cast<int32>(m_fCurrentHp));
		m_pHp->SetHeartSize(m_vHpPos, m_vHpSize);
	}
	m_pAnimInstance = Cast<UAnimInst_EnemyE3>(GetMesh()->GetAnimInstance());
	if (m_pAnimInstance == nullptr)
	{
		ULOG(TEXT("AnimInstance is Nullptr"));
		return;
	}
	
	m_pAIController = Cast<AAIC_EnemyE3>(GetController());
	if (m_pAIController != nullptr)
	{
		m_pAIController->InitAI();
	}
	else
	{
		ULOG(TEXT("AIController is nullptr"));
		return;
	}
	

	m_pStateMng = NewObject<UStateMng_EnemyE3>();
	if (m_pStateMng != nullptr)
	{
		m_pStateMng->Init(this);
		m_pStateMng->ChangeState(static_cast<int32>(E_State_EnemyE3::E_Spawn));
	}
	else
	{
		ULOG(TEXT("StateMng is nullptr"));
		return;
	}
	m_bLife = true;

	m_pMaterialEffect->Init(GetMesh());
	m_pMaterialEffect->AddEffect(E_MaterialEffect::E_Hit2);
	m_pMaterialEffect->AddEffect(E_MaterialEffect::E_Disint);

	AddOisEnemy(this, 0);
}

void AEnemyE3::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	Super::EndPlay(EndPlayReason);

	if (m_pStateMng != nullptr)
		m_pStateMng->Destroy();

	m_pStateMng = nullptr;
}

void AEnemyE3::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (m_pStateMng != nullptr)
		m_pStateMng->Update(DeltaTime);

	if (m_pAnimInstance != nullptr)
	{		
		m_pAnimInstance->SetStat_Acceleration(GetVelocity().Size());
		m_pAnimInstance->SetStat_MovementDirection(m_fMovementDir);
	}

	if (m_bHpDestroy == false)
	{
		AActor* pPlayer = m_pAIController->DetectInPerceptionDie();
		if (pPlayer != nullptr)
		{
			AGBox* pTarget = Cast<AGBox>(pPlayer);
			if (pTarget != nullptr)
			{
				if (pTarget->ActorHasTag("PlayerDie"))
				{
					ULOG(TEXT("player is Die"));
					m_pHp->SetDestroy();
					DestroyOsiEnemy();
					m_bHpDestroy = true;
					return;
				}
			}
		}
	}

	/*if (GetLife() == false) return;
	if (m_pHp != nullptr )
		m_pHp->Tick_Transform(GetActorLocation(), DeltaTime);

	AActor* pPlayer = m_pAIController->DetectInPerception();
	if (pPlayer != nullptr)
	{
		AGameCharacter* pTarget = Cast<AGameCharacter>(pPlayer);
		if (pTarget != nullptr)
		{
			if (pTarget->GetLife() == false)
			{
				m_pHp->SetDestroy();
				return;
			}
		}
	}*/
}

float AEnemyE3::TakeDamage(float DamageAmount, struct FDamageEvent const & DamageEvent, class AController * EventInstigator, AActor * DamageCauser)
{
	float fDamage = Super::TakeDamage(DamageAmount, DamageEvent, EventInstigator, DamageCauser);

	if (GetLife() == false)
		return 0.0f;

	

	E_DamageEventClass eDamageEventClass = ULib_DamageEvent::GetDamageEventClass(DamageEvent.GetTypeID());
	if (fDamage > 0.0f)
	{
		if (eDamageEventClass == E_DamageEventClass::E_Hit)
		{
			//ULOG(TEXT("Hit"));
			FDamageEvent_Hit* pBloodDamageEvent = (FDamageEvent_Hit*)&DamageEvent;

			m_fCurrentHp -= fDamage;

			if (m_pHp != nullptr)
				m_pHp->SetHit();

			bool bIsDead = m_fCurrentHp <= 0 ? true : false;

			if (bIsDead == true)
			{
				SetLife(false);

				if (m_pHp != nullptr)
					m_pHp->SetDestroy();
	
				UState_EnemyE3_Die* pState = Cast<UState_EnemyE3_Die>(m_pStateMng->GetStateClassRef(static_cast<int32>(E_State_EnemyE3::E_Die)));
				if (pState != nullptr)
				{
					//SetRagdollPhysics(pDamageEvent->m_vHitPoint, 10.0f);
					pState->SetHitDirection(pBloodDamageEvent->m_vAttackerLocaction);
					m_pStateMng->ChangeState(static_cast<int32>(E_State_EnemyE3::E_Die));
					return fDamage;
				}
			}

			UState_EnemyE3_Hit* pState = Cast<UState_EnemyE3_Hit>(m_pStateMng->GetStateClassRef(static_cast<int32>(E_State_EnemyE3::E_Hit)));
			if (pState != nullptr)
			{
				pState->SetHitDirection(pBloodDamageEvent->m_vAttackerLocaction);
				m_pStateMng->ChangeState(static_cast<int32>(E_State_EnemyE3::E_Hit));
				return fDamage;
			}
		}
		else if (eDamageEventClass == E_DamageEventClass::E_Parring)
		{
			
			FDamageEvent_Parring* pBloodDamageEvent = (FDamageEvent_Parring*)&DamageEvent;
			UState_EnemyE3_Hit* pState = Cast<UState_EnemyE3_Hit>(m_pStateMng->GetStateClassRef(static_cast<int32>(E_State_EnemyE3::E_Hit)));
			if (pState != nullptr)
			{
				pState->SetHitDirection(pBloodDamageEvent->m_vAttackerLocaction);
				m_pStateMng->ChangeState(static_cast<int32>(E_State_EnemyE3::E_Hit));
				return fDamage;
			}
		}
	}

	return fDamage;
}


void AEnemyE3::CharacterMessage(FString sMessage)
{
	Super::CharacterMessage(sMessage);

	if (m_pStateMng != nullptr)
		m_pStateMng->StateMessage(sMessage);
}

void AEnemyE3::Inter_Notify_Message_Implementation(FName sMessage)
{
	CharacterMessage(sMessage.ToString());
}


bool AEnemyE3::Controll_Attack(class AActor* pActor)
{
	UState_EnemyE3_Attack* pState = Cast<UState_EnemyE3_Attack>(m_pStateMng->GetStateClassRef(static_cast<int32>(E_State_EnemyE3::E_Attack)));
	if (pState != nullptr)
	{
		pState->SetTarget(pActor);
		m_pStateMng->ChangeState(static_cast<int32>(E_State_EnemyE3::E_Attack));
		return true;
	}
	return false;
}