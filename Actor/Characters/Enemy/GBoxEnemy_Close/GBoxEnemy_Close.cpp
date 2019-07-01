// Fill out your copyright notice in the Description page of Project Settings.

#include "GBoxEnemy_Close.h"
#include "AIC_GBoxEnemy_Close.h"
#include "AnimInst_GBoxEnemy_Close.h"
#include "State/StateMng_GBEClose.h"

#include "UI/Enemy/HpSystem/Cpt_EnemyHp.h"
#include "UI/Enemy/HpBossSystem/Cpt_EnemyBossHp.h"

#include "Libraries/Components/AnimationMng/Cpt_AnimationMng.h"
#include "Kismet/KismetMathLibrary.h"

#include "Libraries/Components/MaterialEffect/Cpt_MaterialEffect.h"
#include "Libraries/Components/ParticleMng/Cpt_ParticleMng.h"
#include "Libraries/Components/SoundMng/Cpt_SoundMng.h"
#include "Libraries/Components/CamShake/Cpt_CamShake.h"
#include "Actor/Props/FootPush/Cpt_FootPushLine.h"

#include "Libraries/Components/WarningSpace/Cpt_WarningSpace.h"

#include "Actor/Characters/Enemy/EnemyBarrier.h"
#include "BossEnemySpawnMng.h"
#include "Engine/Public/EngineUtils.h"

AGBoxEnemy_Close::AGBoxEnemy_Close()
{
	PrimaryActorTick.bCanEverTick = true;
	Tags.Add(FName("Enemy"));
	Tags.Add(FName("Boss"));
	SetGenericTeamId(FGenericTeamId(1));

	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	GetCharacterMovement()->bOrientRotationToMovement = true;
	GetCharacterMovement()->MaxWalkSpeed = 900.0f;
	GetCharacterMovement()->RotationRate = FRotator(0.0f, 540.0f, 0.0f);

	m_pAnimationMng = CreateDefaultSubobject<UCpt_AnimationMng>(TEXT("AnimMngComponent"));
	m_pAnimationMng->SetAnimList(TEXT("/Game/1_Project_Main/1_Blueprints/Actor/Characters/Enemy/GBoxEnemy_Close/BP_AnimList_GBoxEnemy_Close.BP_AnimList_GBoxEnemy_Close_C"));

	static ConstructorHelpers::FClassFinder<UAnimInstance> Const_AnimInst(TEXT("/Game/1_Project_Main/2_Contents/Actors/Enemy/EnemyClose/Animation/BP_Anim_EnemyClose.BP_Anim_EnemyClose_C"));
	if (Const_AnimInst.Succeeded()) GetMesh()->SetAnimInstanceClass(Const_AnimInst.Class);

	static ConstructorHelpers::FClassFinder<AAIC_GBoxEnemy_Close> Const_AIC(TEXT("/Game/1_Project_Main/1_Blueprints/Actor/Characters/Enemy/GBoxEnemy_Close/BP_AIC_GBoxEnemy_Close.BP_AIC_GBoxEnemy_Close_C"));
	if (Const_AIC.Succeeded()) AIControllerClass = Const_AIC.Class;

	m_pMaterialEffect = CreateDefaultSubobject<UCpt_MaterialEffect>(TEXT("MaterialEffect"));

	m_pParticleMng = CreateDefaultSubobject<UCpt_ParticleMng>(TEXT("ParticleMng"));
	m_pParticleMng->AddParticleInstance(TEXT("Hit"), TEXT("ParticleSystem'/Game/1_Project_Main/2_Contents/Effects/HitEffect/V_HitImpact.V_HitImpact'"));
	m_pParticleMng->AddParticleInstance(TEXT("Hit_Back"), TEXT("ParticleSystem'/Game/1_Project_Main/2_Contents/Effects/HitEffect/V_HitBackWard_Enemy.V_HitBackWard_Enemy'"));
	m_pParticleMng->AddParticleInstance(TEXT("EyeLight"), TEXT("ParticleSystem'/Game/1_Project_Main/2_Contents/Effects/EyeLight/V_EyeLight.V_EyeLight'"));
	m_pParticleMng->AddParticleInstance(TEXT("GroundBreak"), TEXT("ParticleSystem'/Game/1_Project_Main/2_Contents/Effects/Ex/P_LandHit.P_LandHit'"));


	m_pSoundMng = CreateDefaultSubobject<UCpt_SoundMng>(TEXT("SoundMng"));


	m_pFootPushLine = CreateDefaultSubobject<UCpt_FootPushLine>(TEXT("FootPushLine"));
	m_pFootPushLine->SetSKMesh(this);
	m_pFootPushLine->AddBone(TEXT("Bip001-Pelvis"));

	m_pCamShake = CreateDefaultSubobject <UCpt_CamShake>(TEXT("CamShake"));
	m_pCamShake->AddCameraShakeClass(TEXT("Landing"), TEXT("/Game/1_Project_Main/1_Blueprints/Components/CameraShake/BP_CamShake_Landing.BP_CamShake_Landing_C"));
	m_pCamShake->AddCameraShakeClass(TEXT("JumpAttack"), TEXT("/Game/1_Project_Main/1_Blueprints/Components/CameraShake/BP_CamShake_JumpAttack.BP_CamShake_JumpAttack_C"));


	m_pWarningSpace = CreateDefaultSubobject<UCpt_WarningSpace>(TEXT("WarningSpace"));

	//m_pHp = CreateDefaultSubobject<UCpt_EnemyHp>(TEXT("EnemyHp"));

	m_pBossHp = CreateDefaultSubobject<UCpt_EnemyBossHp>(TEXT("EnemyBossHp"));

	static ConstructorHelpers::FClassFinder<AEnemyBarrier> Const_Barrier(TEXT("/Game/1_Project_Main/1_Blueprints/Actor/Characters/Enemy/BP_EnemyBarrier.BP_EnemyBarrier_C"));
	if (Const_Barrier.Succeeded()) m_pInst_Barrier = Const_Barrier.Class;
}

void AGBoxEnemy_Close::PossessedBy(AController* NewController)
{
	Super::PossessedBy(NewController);

}

void AGBoxEnemy_Close::PostInitializeComponents()
{
	Super::PostInitializeComponents();

}

void AGBoxEnemy_Close::Active_Barrier()
{
	m_pBarrier->Active_Barrier();
}

void AGBoxEnemy_Close::Hit_Barrier()
{

}

void AGBoxEnemy_Close::DeActive_Barrier()
{

}

void AGBoxEnemy_Close::SpawnMonsters()
{
	if (m_pSpawnMng == nullptr) return;
	m_bEnemyCheck = true;
	m_pSpawnMng->SpawnMonsters(UKismetMathLibrary::RandomIntegerInRange(1, 2));
}

void AGBoxEnemy_Close::BeginPlay()
{
	Super::BeginPlay();
	for (TActorIterator<AActor> ActorItr(GetWorld()); ActorItr; ++ActorItr)
	{
		if (*ActorItr != nullptr)
		{
			if (ActorItr->ActorHasTag("EnemySpawnMng") == true)
			{
				m_pSpawnMng = Cast<ABossEnemySpawnMng>(*ActorItr);
				break;
			}
		}
	}

	GetController()->SetControlRotation(FRotator::ZeroRotator);
	SetStartLoc(GetActorLocation());

	/*if (m_pHp != nullptr)
	{
		m_pHp->AddHeart(this, 3);
		m_pHp->SetHeartSize(m_vHpSize);
		ULOG(TEXT("HpBar is Online"));
	}*/

	if (m_pBossHp != nullptr)
	{
		m_pBossHp->AddHeart(static_cast<int32>(m_fCurrentHp));
		m_pBossHp->SetHeartPosition(m_vHpPos, m_fHpSize);

		ULOG(TEXT("Boss Hp is Online"));
	}

	m_pAnimInstance = Cast<UAnimInst_GBoxEnemy_Close>(GetMesh()->GetAnimInstance());
	if (m_pAnimInstance == nullptr)
	{
		ULOG(TEXT("AnimInstance is Nullptr"));
		return;
	}

	m_pAIController = Cast<AAIC_GBoxEnemy_Close>(GetController());
	if (m_pAIController != nullptr)
	{
		m_pAIController->InitAI();
	}
	else
	{
		ULOG(TEXT("AIController is nullptr"));
		return;
	}

	m_pStateMng = NewObject<UStateMng_GBEClose>();
	if (m_pStateMng != nullptr)
	{
		m_pStateMng->Init(this);
		m_pStateMng->ChangeState(static_cast<int32>(E_State_GBEClose::E_Spawn));
	}
	else
	{
		ULOG(TEXT("StateMng is nullptr"));
		return;
	}
	m_bLife = true;

	m_pMaterialEffect->Init(GetMesh());
	m_pMaterialEffect->AddEffect(E_MaterialEffect::E_Hit2);

	if (m_pInst_Barrier != nullptr)
	{
		AEnemyBarrier* pSrc = GetWorld()->SpawnActor<AEnemyBarrier>(m_pInst_Barrier, GetActorLocation(), FRotator::ZeroRotator);
		if (pSrc == nullptr) return;
		m_pBarrier = pSrc;
		m_pBarrier->AttachToComponent(GetMesh(), FAttachmentTransformRules::KeepWorldTransform, TEXT("Bip001-Pelvis"));
		m_pBarrier->Init(5);
		m_pBarrier->Active_Barrier();
	}

	AddOisEnemy(this, 1);

}

void AGBoxEnemy_Close::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	Super::EndPlay(EndPlayReason);

	if (m_pBarrier != nullptr)
	{
		m_pBarrier->Destroy();
		m_pBarrier = nullptr;
	}

	if (m_pStateMng != nullptr)
		m_pStateMng->Destroy();

	m_pStateMng = nullptr;
}

void AGBoxEnemy_Close::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (m_pStateMng != nullptr)
		m_pStateMng->Update(DeltaTime);

	AnimInst_Tick();
	Tick_EnemyCheck(DeltaTime);

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
					if (m_pBossHp != nullptr)
						m_pBossHp->SetDestroy();
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

void AGBoxEnemy_Close::Tick_EnemyCheck(float fDeltaTime)
{
	if (m_bEnemyCheck == false) return;
	if (m_pSpawnMng == nullptr) return;
	if (GetLife() == false) return;

	m_fEnemyCheckTime += fDeltaTime;
	if (m_fEnemyCheckTime > 0.5f)
	{
		m_fEnemyCheckTime = 0.0f;
		if (m_pSpawnMng->GetIsMonstarLive() == false)
		{
			//ULOG(TEXT("aaaa"));
			m_bEnemyCheck = false;
			UState_GBEC_Panic* pState = Cast<UState_GBEC_Panic>(m_pStateMng->GetStateClassRef(static_cast<int32>(E_State_GBEClose::E_Panic)));
			if (pState != nullptr)
			{
				pState->Set_Break(false);
				m_pStateMng->ChangeState(static_cast<int32>(E_State_GBEClose::E_Panic));
			}
		}
	}
}

float AGBoxEnemy_Close::TakeDamage(float DamageAmount, struct FDamageEvent const & DamageEvent, class AController * EventInstigator, AActor * DamageCauser)
{
	float fDamage = Super::TakeDamage(DamageAmount, DamageEvent, EventInstigator, DamageCauser);

	if (GetLife() == false)
		return 0.0f;

	E_DamageEventClass eDamageEventClass = ULib_DamageEvent::GetDamageEventClass(DamageEvent.GetTypeID());
	if (fDamage > 0.0f)
	{
		if (eDamageEventClass == E_DamageEventClass::E_Hit)
		{
			//	ULOG(TEXT("Hit"));



			FDamageEvent_Hit* pBloodDamageEvent = (FDamageEvent_Hit*)&DamageEvent;
			if (m_pBarrier->GetActiveState() == true)// && m_pStateMng->GetCurrentState() != static_cast<int32>(E_State_GBEClose::E_Panic))
			{
				m_pBarrier->Hit_Barrier(1);
				if (m_pBarrier->GetActiveState() == true)
				{
					return 999.0f;
				}
				else
				{

					//if (m_pStateMng->GetCurrentState() != static_cast<int32>(E_State_GBEClose::E_Panic))
					//{
					UState_GBEC_Panic* pState = Cast<UState_GBEC_Panic>(m_pStateMng->GetStateClassRef(static_cast<int32>(E_State_GBEClose::E_Panic)));
					if (pState != nullptr)
					{
						pState->Set_Break(true);
						m_pStateMng->ChangeState(static_cast<int32>(E_State_GBEClose::E_Panic));
					}
					//	}

					return fDamage;
				}
			}


			m_fCurrentHp -= fDamage;

			if (m_pBossHp != nullptr)
				m_pBossHp->SetHit();

			/*if (m_pHp != nullptr)
				m_pHp->SetHit();*/

			bool bIsDead = m_fCurrentHp <= 0 ? true : false;

			if (bIsDead == true)
			{
				SetLife(false);
				if (m_pBossHp != nullptr)
					m_pBossHp->SetDestroy();
				/*if (m_pHp != nullptr)
					m_pHp->SetDestroy();*/

				UState_GBEC_Die* pState = Cast<UState_GBEC_Die>(m_pStateMng->GetStateClassRef(static_cast<int32>(E_State_GBEClose::E_Die)));
				if (pState != nullptr)
				{
					//SetRagdollPhysics(pDamageEvent->m_vHitPoint, 10.0f);
					pState->SetHitDirection(pBloodDamageEvent->m_vAttackerLocaction);
					m_pStateMng->ChangeState(static_cast<int32>(E_State_GBEClose::E_Die));
					GetBarrier()->Hit_Barrier(100);
					if (m_pSpawnMng != nullptr)
					{
						m_pSpawnMng->KillAllMonsters();
					}

					return fDamage;
				}
			}

			if (m_pStateMng->GetCurrentState() == static_cast<int32>(E_State_GBEClose::E_Panic))
			{
				UState_GBEC_Panic* pState = Cast<UState_GBEC_Panic>(m_pStateMng->GetStateClassRef(static_cast<int32>(E_State_GBEClose::E_Panic)));
				if (pState != nullptr)
				{
					pState->PanicHit();
					//m_pStateMng->ChangeState(static_cast<int32>(E_State_GBEClose::E_Panic));
				}
			}



			/*UState_GBEC_Hit* pState = Cast<UState_GBEC_Hit>(m_pStateMng->GetStateClassRef(static_cast<int32>(E_State_GBEClose::E_Hit)));
			if (pState != nullptr)
			{

				pState->SetHitDirection(pBloodDamageEvent->m_vAttackerLocaction);
				m_pStateMng->ChangeState(static_cast<int32>(E_State_GBEClose::E_Hit));
				return fDamage;
			}*/
		}
		/*else if (eDamageEventClass == E_DamageEventClass::E_Parring)
		{
			ULOG(TEXT("Parring"));
			FDamageEvent_Parring* pBloodDamageEvent = (FDamageEvent_Parring*)&DamageEvent;
			UState_GBEC_Hit* pState = Cast<UState_GBEC_Hit>(m_pStateMng->GetStateClassRef(static_cast<int32>(E_State_GBEClose::E_Hit)));
			if (pState != nullptr)
			{
				pState->SetHitDirection(pBloodDamageEvent->m_vAttackerLocaction);
				m_pStateMng->ChangeState(static_cast<int32>(E_State_GBEClose::E_Hit));
				return fDamage;
			}
		}*/
	}

	return fDamage;
}

void AGBoxEnemy_Close::CharacterMessage(FString sMessage)
{
	Super::CharacterMessage(sMessage);

	if (m_pStateMng != nullptr)
		m_pStateMng->StateMessage(sMessage);
}

void AGBoxEnemy_Close::Inter_Notify_Message_Implementation(FName sMessage)
{
	CharacterMessage(sMessage.ToString());
}

void AGBoxEnemy_Close::AnimInst_Tick()
{
	if (m_pAnimInstance == nullptr) return;

	m_pAnimInstance->SetStat_Acceleration(GetVelocity().Size());
	m_pAnimInstance->SetStat_MovementDirection(m_fMovementDir);
}

bool AGBoxEnemy_Close::Controll_Attack(class AActor* pActor)
{
	if (m_pStateMng->GetCurrentState() == static_cast<int32>(E_State_GBEClose::E_Panic) ||
		m_pStateMng->GetCurrentState() == static_cast<int32>(E_State_GBEClose::E_Die) ||
		m_pStateMng->GetCurrentState() == static_cast<int32>(E_State_GBEClose::E_Hit))
	{
		return false;
	}

	UState_GBEC_Attack* pState = Cast<UState_GBEC_Attack>(m_pStateMng->GetStateClassRef(static_cast<int32>(E_State_GBEClose::E_Attack)));
	if (pState != nullptr)
	{
		pState->SetTarget(pActor);
		m_pStateMng->ChangeState(static_cast<int32>(E_State_GBEClose::E_Attack));
		return true;
	}

	return false;
}

bool AGBoxEnemy_Close::Controll_Attack2(class AActor* pActor)
{
	if (m_pStateMng->GetCurrentState() == static_cast<int32>(E_State_GBEClose::E_Panic) ||
		m_pStateMng->GetCurrentState() == static_cast<int32>(E_State_GBEClose::E_Die) ||
		m_pStateMng->GetCurrentState() == static_cast<int32>(E_State_GBEClose::E_Hit))
	{
		return false;
	}

	UState_GBEC_Attack2* pState = Cast<UState_GBEC_Attack2>(m_pStateMng->GetStateClassRef(static_cast<int32>(E_State_GBEClose::E_Attack2)));
	if (pState != nullptr)
	{
		pState->SetTarget(pActor);
		m_pStateMng->ChangeState(static_cast<int32>(E_State_GBEClose::E_Attack2));
		return true;
	}
	return false;
}


bool AGBoxEnemy_Close::Controll_JumpAttack(class AActor* pActor)
{
	if (m_pStateMng->GetCurrentState() == static_cast<int32>(E_State_GBEClose::E_Panic) ||
		m_pStateMng->GetCurrentState() == static_cast<int32>(E_State_GBEClose::E_Die) ||
		m_pStateMng->GetCurrentState() == static_cast<int32>(E_State_GBEClose::E_Hit))
	{
		return false;
	}

	UState_GBEC_JumpAttack* pState = Cast<UState_GBEC_JumpAttack>(m_pStateMng->GetStateClassRef(static_cast<int32>(E_State_GBEClose::E_JumpAttack)));
	if (pState != nullptr)
	{
		pState->SetTarget(pActor);
		m_pStateMng->ChangeState(static_cast<int32>(E_State_GBEClose::E_JumpAttack));
		return true;
	}


	return false;
}

bool AGBoxEnemy_Close::Controll_Spin(class AActor* pActor)
{

	if (m_pStateMng->GetCurrentState() == static_cast<int32>(E_State_GBEClose::E_Panic) ||
		m_pStateMng->GetCurrentState() == static_cast<int32>(E_State_GBEClose::E_Die) ||
		m_pStateMng->GetCurrentState() == static_cast<int32>(E_State_GBEClose::E_Hit))
	{
		return false;
	}
	UState_GBEC_Spin* pState = Cast<UState_GBEC_Spin>(m_pStateMng->GetStateClassRef(static_cast<int32>(E_State_GBEClose::E_Spin)));
	if (pState != nullptr)
	{
		//pState->SetTarget(pActor);
		m_pStateMng->ChangeState(static_cast<int32>(E_State_GBEClose::E_Spin));
		return true;
	}
	return false;
}

bool AGBoxEnemy_Close::Controll_Dash(class AActor* pActor)
{
	if (m_pStateMng->GetCurrentState() == static_cast<int32>(E_State_GBEClose::E_Panic) ||
		m_pStateMng->GetCurrentState() == static_cast<int32>(E_State_GBEClose::E_Die) ||
		m_pStateMng->GetCurrentState() == static_cast<int32>(E_State_GBEClose::E_Hit))
	{
		return false;
	}

	UState_GBEC_DashAttack* pState = Cast<UState_GBEC_DashAttack>(m_pStateMng->GetStateClassRef(static_cast<int32>(E_State_GBEClose::E_DashAttack)));
	if (pState != nullptr)
	{
		pState->SetTarget(pActor);
		m_pStateMng->ChangeState(static_cast<int32>(E_State_GBEClose::E_DashAttack));
		return true;
	}
	return false;

}