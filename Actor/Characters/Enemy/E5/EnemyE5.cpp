// Fill out your copyright notice in the Description page of Project Settings.

#include "EnemyE5.h"
#include "AnimInst_EnemyE5.h"
#include "AIC_EnemyE5.h"
#include "EnemyE5_Missile.h"
#include "State/StateMng_EnemyE5.h"

#include "UI/Enemy/HpSystem/Cpt_EnemyHp.h"

#include "Actor/Props/FootPush/Cpt_FootPushLine.h"
#include "Libraries/Components/MaterialEffect/Cpt_MaterialEffect.h"
#include "Libraries/Components/ParticleMng/Cpt_ParticleMng.h"
#include "Libraries/Components/SoundMng/Cpt_SoundMng.h"
#include "Libraries/Components/CamShake/Cpt_CamShake.h"
#include "Libraries/Components/AnimationMng/Cpt_AnimationMng.h"
#include "Kismet/KismetMathLibrary.h"

AEnemyE5::AEnemyE5()
{
	PrimaryActorTick.bCanEverTick = true;
	Tags.Add(FName("Enemy"));
	SetGenericTeamId(FGenericTeamId(1));

	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	GetCharacterMovement()->bOrientRotationToMovement = true;
	GetCharacterMovement()->MaxWalkSpeed = 600.0f;
	GetCharacterMovement()->RotationRate = FRotator(0.0f, 540.0f, 0.0f);

	m_pAnimationMng = CreateDefaultSubobject<UCpt_AnimationMng>(TEXT("AnimMngComponent"));
	m_pAnimationMng->SetAnimList(TEXT("/Game/1_Project_Main/1_Blueprints/Actor/Characters/Enemy/EnemyE5/BP_AnimList_EnemyE5.BP_AnimList_EnemyE5_C"));

	m_pMaterialEffect = CreateDefaultSubobject<UCpt_MaterialEffect>(TEXT("MaterialEffect"));

	m_pParticleMng = CreateDefaultSubobject<UCpt_ParticleMng>(TEXT("ParticleMng"));
	m_pParticleMng->AddParticleInstance(TEXT("Hit"), TEXT("ParticleSystem'/Game/1_Project_Main/2_Contents/Effects/HitEffect/V_HitImpact.V_HitImpact'"));
	m_pParticleMng->AddParticleInstance(TEXT("EyeLight"), TEXT("ParticleSystem'/Game/1_Project_Main/2_Contents/Effects/EyeLight/V_EyeLight.V_EyeLight'"));
	m_pParticleMng->AddParticleInstance(TEXT("Laser"), TEXT("ParticleSystem'/Game/1_Project_Main/2_Contents/Effects/Laser/V_Laser.V_Laser'"));
	m_pParticleMng->AddParticleInstance(TEXT("Disint"), TEXT("ParticleSystem'/Game/1_Project_Main/2_Contents/Effects/V_Disint.V_Disint'"));

	m_pSoundMng = CreateDefaultSubobject<UCpt_SoundMng>(TEXT("SoundMng"));
	m_pSoundMng->Set_SoundList(TEXT("/Game/1_Project_Main/1_Blueprints/Actor/Characters/Enemy/EnemyE5/BP_SoundList_E5.BP_SoundList_E5_C"));

	m_pFootPushLine = CreateDefaultSubobject<UCpt_FootPushLine>(TEXT("FootPushLine"));
	m_pFootPushLine->SetSKMesh(this);
	m_pFootPushLine->AddBone(TEXT("Bone_Body"));

	m_pHp = CreateDefaultSubobject<UCpt_EnemyHp>(TEXT("EnemyHp"));

	static ConstructorHelpers::FClassFinder<UAnimInstance> Const_AnimInst(TEXT("/Game/1_Project_Main/2_Contents/Actors/Enemy/E5/Animation/BP_Anim_Enemy5.BP_Anim_Enemy5_C"));
	if (Const_AnimInst.Succeeded()) GetMesh()->SetAnimInstanceClass(Const_AnimInst.Class);

	static ConstructorHelpers::FClassFinder<AAIC_EnemyE5> Const_AIC(TEXT("/Game/1_Project_Main/1_Blueprints/Actor/Characters/Enemy/EnemyE5/BP_AIC_EnemyE5.BP_AIC_EnemyE5_C"));
	if (Const_AIC.Succeeded()) AIControllerClass = Const_AIC.Class;

}

void AEnemyE5::PossessedBy(AController* NewController)
{
	Super::PossessedBy(NewController);

}

void AEnemyE5::PostInitializeComponents()
{
	Super::PostInitializeComponents();

}

void AEnemyE5::BeginPlay()
{
	Super::BeginPlay();

	GetMesh()->SetAllBodiesBelowSimulatePhysics(TEXT("Bone_L_Ear01"), true);
	GetMesh()->SetAllBodiesBelowSimulatePhysics(TEXT("Bone_R_Ear02"), true);
	GetMesh()->SetAllBodiesBelowSimulatePhysics(TEXT("Bip001-Head"), true);

	GetController()->SetControlRotation(FRotator::ZeroRotator);
	SetStartLoc(GetActorLocation());

	if (m_pHp != nullptr)
	{
		m_pHp->AddHeart(this, static_cast<int32>(m_fCurrentHp));
		m_pHp->SetHeartSize(m_vHpPos, m_vHpSize);
		ULOG(TEXT("HpBar is Online : %d"), (int32)m_fCurrentHp);
	}

	m_pAnimInstance = Cast<UAnimInst_EnemyE5>(GetMesh()->GetAnimInstance());
	if (m_pAnimInstance == nullptr)
	{
		ULOG(TEXT("AnimInstance is Nullptr"));
		return;
	}

	m_pAIController = Cast<AAIC_EnemyE5>(GetController());
	if (m_pAIController != nullptr)
	{
		m_pAIController->InitAI();
	}
	else
	{
		ULOG(TEXT("AIController is nullptr"));
		return;
	}

	m_pStateMng = NewObject<UStateMng_EnemyE5>();
	if (m_pStateMng != nullptr)
	{
		m_pStateMng->Init(this);
		m_pStateMng->ChangeState(static_cast<int32>(E_State_EnemyE5::E_Spawn));
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

void AEnemyE5::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	Super::EndPlay(EndPlayReason);

	if (m_pStateMng != nullptr)
		m_pStateMng->Destroy();

	m_pStateMng = nullptr;

}

void AEnemyE5::Tick(float DeltaTime)
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
					m_pHp->SetDestroy();
					DestroyOsiEnemy();
					m_bHpDestroy = true;
					return;
				}
			}
		}
	}
}
float AEnemyE5::TakeDamage(float DamageAmount, struct FDamageEvent const & DamageEvent, class AController * EventInstigator, AActor * DamageCauser)
{
	float fDamage = Super::TakeDamage(DamageAmount, DamageEvent, EventInstigator, DamageCauser);

	if (GetLife() == false)
		return 0.0f;

	E_DamageEventClass eDamageEventClass = ULib_DamageEvent::GetDamageEventClass(DamageEvent.GetTypeID());
	if (fDamage > 0.0f)
	{
		if (eDamageEventClass == E_DamageEventClass::E_Hit)
		{
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

				UState_EnemyE5_Die* pState = Cast<UState_EnemyE5_Die>(m_pStateMng->GetStateClassRef(static_cast<int32>(E_State_EnemyE5::E_Die)));
				if (pState != nullptr)
				{
					//SetRagdollPhysics(pDamageEvent->m_vHitPoint, 10.0f);
					pState->SetHitDirection(pBloodDamageEvent->m_vAttackerLocaction);
					m_pStateMng->ChangeState(static_cast<int32>(E_State_EnemyE5::E_Die));
					return fDamage;
				}
			}

			UState_EnemyE5_Hit* pState = Cast<UState_EnemyE5_Hit>(m_pStateMng->GetStateClassRef(static_cast<int32>(E_State_EnemyE5::E_Hit)));
			if (pState != nullptr)
			{

				pState->SetHitDirection(pBloodDamageEvent->m_vAttackerLocaction);
				if (m_pStateMng->GetCurrentState() == (int)E_State_EnemyE5::E_Attack)
				{
					pState->SetAttackHit();
				}

				m_pStateMng->ChangeState(static_cast<int32>(E_State_EnemyE5::E_Hit));
				return fDamage;
			}
		}
		else if (eDamageEventClass == E_DamageEventClass::E_Parring)
		{
			FDamageEvent_Parring* pBloodDamageEvent = (FDamageEvent_Parring*)&DamageEvent;
			UState_EnemyE5_Hit* pState = Cast<UState_EnemyE5_Hit>(m_pStateMng->GetStateClassRef(static_cast<int32>(E_State_EnemyE5::E_Hit)));
			if (pState != nullptr)
			{
				pState->SetHitDirection(pBloodDamageEvent->m_vAttackerLocaction);
				m_pStateMng->ChangeState(static_cast<int32>(E_State_EnemyE5::E_Hit));
				return fDamage;
			}
		}
	}

	return fDamage;
}


void AEnemyE5::CharacterMessage(FString sMessage)
{
	Super::CharacterMessage(sMessage);

	if (m_pStateMng != nullptr)
		m_pStateMng->StateMessage(sMessage);
}

void AEnemyE5::Inter_Notify_Message_Implementation(FName sMessage)
{
	CharacterMessage(sMessage.ToString());

}

bool AEnemyE5::Controll_Attack(class AActor* pActor)
{
	if (m_pStateMng->GetCurrentState() == static_cast<int32>(E_State_EnemyE5::E_Attack)) return false;

	UState_EnemyE5_Attack* pState = Cast<UState_EnemyE5_Attack>(m_pStateMng->GetStateClassRef(static_cast<int32>(E_State_EnemyE5::E_Attack)));
	if (pState != nullptr)
	{
		pState->SetTarget(pActor);
		m_pStateMng->ChangeState(static_cast<int32>(E_State_EnemyE5::E_Attack));
		return true;
	}
	return false;
}

bool AEnemyE5::Controll_Moving()
{
	UState_EnemyE5_Idle* pState = Cast<UState_EnemyE5_Idle>(m_pStateMng->GetStateClassRef(static_cast<int32>(E_State_EnemyE5::E_Idle)));
	if (pState != nullptr)
	{
		m_pStateMng->ChangeState(static_cast<int32>(E_State_EnemyE5::E_Idle));
		return true;
	}
	return false;
}

AEnemyE5_Missile * AEnemyE5::CreateBullet(FVector vShootLoc, FVector vTargetLoc)
{
	if (m_pInstance_Bullet == nullptr) return nullptr;

	AEnemyE5_Missile* pBullet = GetWorld()->SpawnActor<AEnemyE5_Missile>(m_pInstance_Bullet);
	if (pBullet == nullptr) return nullptr;

	pBullet->Shoot(this, vShootLoc, vTargetLoc);

	return pBullet;
}

AEnemyE5_Missile * AEnemyE5::CreateBullet(FVector vShootLoc, AActor * pTarget)
{
	if (m_pInstance_Bullet == nullptr) return nullptr;
	
	AEnemyE5_Missile* pBullet = GetWorld()->SpawnActor<AEnemyE5_Missile>(m_pInstance_Bullet);
	if (pBullet == nullptr) return nullptr;

	pBullet->ShootToTarget(this, vShootLoc, pTarget);

	return pBullet;
}

void AEnemyE5::SetCombatState(bool bCombat)
{
	m_bCombat = bCombat;
	m_pAnimInstance->SetStat_Combat(bCombat);
}