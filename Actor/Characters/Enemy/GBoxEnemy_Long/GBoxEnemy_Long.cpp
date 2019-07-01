// Fill out your copyright notice in the Description page of Project Settings.

#include "GBoxEnemy_Long.h"
#include "GBoxEnemyLong_Bullet.h"
#include "AIC_GBoxEnemy_Long.h"
#include "AnimInst_GBoxEnemy_Long.h"
#include "State/StateMng_GBELong.h"

#include "Libraries/Components/AnimationMng/Cpt_AnimationMng.h"
#include "Libraries/Components/ParticleMng/Cpt_ParticleMng.h"
#include "Libraries/Components/MaterialEffect/Cpt_MaterialEffect.h"
#include "Components/StaticMeshComponent.h"

#include "Kismet/KismetMathLibrary.h"

#include "Actor/Props/FootPush/Cpt_FootPushLine.h"

AGBoxEnemy_Long::AGBoxEnemy_Long()
{
	PrimaryActorTick.bCanEverTick = true;
	Tags.Add(FName("Enemy"));
	SetGenericTeamId(FGenericTeamId(1));

	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	GetCharacterMovement()->bOrientRotationToMovement = true;
	GetCharacterMovement()->MaxWalkSpeed = 300.0f;
	GetCharacterMovement()->RotationRate = FRotator(0.0f, 540.0f, 0.0f);

	m_pAnimationMng = CreateDefaultSubobject<UCpt_AnimationMng>(TEXT("AnimMngComponent"));
	m_pAnimationMng->SetAnimList(TEXT("/Game/1_Project_Main/1_Blueprints/Actor/Characters/Enemy/GBoxEnemy_Long/BP_AnimList_GBoxEnemy_Long.BP_AnimList_GBoxEnemy_Long_C"));

	m_pParticleMng = CreateDefaultSubobject<UCpt_ParticleMng>(TEXT("ParticleMng"));
	m_pParticleMng->AddParticleInstance(TEXT("Laser"), TEXT("ParticleSystem'/Game/1_Project_Main/2_Contents/Effects/Laser/V_Laser.V_Laser'"));
	m_pParticleMng->AddParticleInstance(TEXT("EyeLight"), TEXT("ParticleSystem'/Game/1_Project_Main/2_Contents/Effects/EyeLight/V_EyeLight.V_EyeLight'"));

	static ConstructorHelpers::FClassFinder<UAnimInstance> Const_AnimInst(TEXT("/Game/1_Project_Main/2_Contents/Actors/Enemy/EnemyLong/Animation2/BP_Anim_LongEnemy.BP_Anim_LongEnemy_C"));
	if (Const_AnimInst.Succeeded()) GetMesh()->SetAnimInstanceClass(Const_AnimInst.Class);

	static ConstructorHelpers::FClassFinder<AGBoxEnemyLong_Bullet> Const_Bullet(TEXT("/Game/1_Project_Main/1_Blueprints/Actor/Characters/Enemy/GBoxEnemy_Long/BP_GBoxEnemyLong_Bullet.BP_GBoxEnemyLong_Bullet_C"));
	if (Const_Bullet.Succeeded()) m_pInstance_Bullet = Const_Bullet.Class;

	static ConstructorHelpers::FClassFinder<AAIC_GBoxEnemy_Long> Const_AIC(TEXT("/Game/1_Project_Main/1_Blueprints/Actor/Characters/Enemy/GBoxEnemy_Long/BP_AIC_GBoxEnemy_Long.BP_AIC_GBoxEnemy_Long_C"));
	if (Const_AIC.Succeeded()) AIControllerClass = Const_AIC.Class;

	m_pMaterialEffect = CreateDefaultSubobject<UCpt_MaterialEffect>(TEXT("MaterialEffect"));

	m_pFootPushLine = CreateDefaultSubobject<UCpt_FootPushLine>(TEXT("FootPushLine"));
	m_pFootPushLine->SetSKMesh(this);
	m_pFootPushLine->AddBone(TEXT("Bip001-L-Foot"));
	m_pFootPushLine->AddBone(TEXT("Bip001-R-Foot"));
}

void AGBoxEnemy_Long::PossessedBy(AController* NewController)
{
	Super::PossessedBy(NewController);
	
}

void AGBoxEnemy_Long::PostInitializeComponents()
{
	Super::PostInitializeComponents();

}

void AGBoxEnemy_Long::BeginPlay()
{
	Super::BeginPlay();

	GetController()->SetControlRotation(FRotator::ZeroRotator);
	SetStartLoc(GetActorLocation());

	m_pAnimInstance = Cast<UAnimInst_GBoxEnemy_Long>(GetMesh()->GetAnimInstance());
	if (m_pAnimInstance == nullptr)
	{
		ULOG(TEXT("AnimInstance is Nullptr"));
		return;
	}
	
	m_pAIController = Cast<AAIC_GBoxEnemy_Long>(GetController());
	if (m_pAIController != nullptr)
	{
		m_pAIController->InitAI();
	}
	else
	{
		ULOG(TEXT("AIController is nullptr"));
		return;
	}

	m_pStateMng = NewObject<UStateMng_GBELong>();
	if (m_pStateMng != nullptr)
	{
		m_pStateMng->Init(this);
		m_pStateMng->ChangeState(static_cast<int32>(E_State_GBELong::E_Idle));
	}
	else
	{
		ULOG(TEXT("StateMng is nullptr"));
		return;
	}

	m_pMaterialEffect->Init(GetMesh());
	m_pMaterialEffect->AddEffect(E_MaterialEffect::E_Hit2);

	m_bLife = true;
}

void AGBoxEnemy_Long::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	Super::EndPlay(EndPlayReason);

	if (m_pStateMng != nullptr)
		m_pStateMng->Destroy();

	m_pStateMng = nullptr;
}

void AGBoxEnemy_Long::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (m_pStateMng != nullptr)
		m_pStateMng->Update(DeltaTime);

	AnimInst_Tick();
	HeadRotator_Tick(DeltaTime);
}

void AGBoxEnemy_Long::HeadRotator_Tick(float fDeltaTime)
{
	if (m_bUseHeadRotator == false)
	{
		FRotator pControlRotation = FRotator::ZeroRotator;
		FRotator pInterpRotator = UKismetMathLibrary::RInterpTo(m_rHeadRotator, pControlRotation, fDeltaTime, 3.0f);

		m_rHeadRotator = pInterpRotator;
	}
	else
	{
		m_fHeadRotatorNoneTime += fDeltaTime;
		if (m_fHeadRotatorNoneTime > m_fHeadRotatorNoneTime_Ago)
		{
			m_fHeadRotatorNoneTime = 0.0f;
			m_bUseHeadRotator = false;
		}
	}
	m_pAnimInstance->SetStat_HeadRotator(m_rHeadRotator);
}

void AGBoxEnemy_Long::HeadRotator_Use(FRotator rLookRotator, float fDeltaTime)
{
	m_fHeadRotatorNoneTime = 0.0f;
	m_bUseHeadRotator = true;

	FRotator pControlRotation = rLookRotator;
//	pControlRotation += GetActorRotation();
	pControlRotation.Yaw -= GetActorRotation().Yaw;
	FRotator pInterpRotator = UKismetMathLibrary::RInterpTo(m_rHeadRotator, pControlRotation, fDeltaTime, 18.0f);

	m_rHeadRotator = pInterpRotator;
	//m_pAnimInstance->SetStat_HeadRotator(m_rHeadRotator);

	//UKismetSystemLibrary::PrintString(GetWorld(), m_rHeadRotator.ToString(), true, false, FLinearColor::Blue, 0.0f);
}

float AGBoxEnemy_Long::TakeDamage(float DamageAmount, struct FDamageEvent const & DamageEvent, class AController * EventInstigator, AActor * DamageCauser)
{
	float fDamage = Super::TakeDamage(DamageAmount, DamageEvent, EventInstigator, DamageCauser);
	if (GetLife() == false)
		return 0.0f;

	E_DamageEventClass eDamageEventClass = ULib_DamageEvent::GetDamageEventClass(DamageEvent.GetTypeID());
	if (fDamage > 0.0f)
	{
		FDamageEvent_Hit* pBloodDamageEvent = (FDamageEvent_Hit*)&DamageEvent;
		m_fCurrentHp -= fDamage;
		bool bIsDead = m_fCurrentHp <= 0 ? true : false;

		if (bIsDead == true)
		{
			SetLife(false);

			UState_GBEL_Die* pState = Cast<UState_GBEL_Die>(m_pStateMng->GetStateClassRef(static_cast<int32>(E_State_GBELong::E_Die)));
			if (pState != nullptr)
			{
				//SetRagdollPhysics(pDamageEvent->m_vHitPoint, 10.0f);
				pState->SetHitDirection(pBloodDamageEvent->m_vAttackerLocaction);
				m_pStateMng->ChangeState(static_cast<int32>(E_State_GBELong::E_Die));
				return fDamage;
			}
		}

		if (eDamageEventClass == E_DamageEventClass::E_Hit)
		{
			UState_GBEL_Hit* pState = Cast<UState_GBEL_Hit>(m_pStateMng->GetStateClassRef(static_cast<int32>(E_State_GBELong::E_Hit)));
			if (pState != nullptr)
			{
				pState->SetHitDirection(pBloodDamageEvent->m_vAttackerLocaction);
				m_pStateMng->ChangeState(static_cast<int32>(E_State_GBELong::E_Hit));
				return fDamage;
			}
		}
	}

	return fDamage;
}

void AGBoxEnemy_Long::CharacterMessage(FString sMessage)
{
	Super::CharacterMessage(sMessage);

	if (m_pStateMng != nullptr)
		m_pStateMng->StateMessage(sMessage);
}

void AGBoxEnemy_Long::Inter_Notify_Message_Implementation(FName sMessage)
{
	CharacterMessage(sMessage.ToString());
}

void AGBoxEnemy_Long::AnimInst_Tick()
{
	if (m_pAnimInstance == nullptr) return;

	m_pAnimInstance->SetStat_Acceleration(GetVelocity().Size());
	m_pAnimInstance->SetStat_MovementDirection(m_fMovementDir);
}

AGBoxEnemyLong_Bullet * AGBoxEnemy_Long::CreateBullet(FVector vShootLoc, FVector vTargetLoc)
{
	if (m_pInstance_Bullet == nullptr) return nullptr;

	AGBoxEnemyLong_Bullet* pBullet = GetWorld()->SpawnActor<AGBoxEnemyLong_Bullet>(m_pInstance_Bullet);
	if (pBullet == nullptr) return nullptr;

	pBullet->Shoot(this, vShootLoc, vTargetLoc);

	return pBullet;
}

bool AGBoxEnemy_Long::Controll_Attack(class AActor* vTargetLoc)
{
	UState_GBEL_Attack* pState = Cast<UState_GBEL_Attack>(m_pStateMng->GetStateClassRef(static_cast<int32>(E_State_GBELong::E_Attack)));
	if (pState != nullptr)
	{
		pState->SetTarget(vTargetLoc);
		m_pStateMng->ChangeState(static_cast<int32>(E_State_GBELong::E_Attack));
		return true;
	}
	return false;
}
